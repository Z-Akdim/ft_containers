#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include "make_pair.hpp"

template<typename T>
struct Node {
    typedef Node*           N_Ptr;
    typedef const Node*     Const_N_Ptr;
    typedef size_t          size_type;

    T               data;
    N_Ptr         right;
    N_Ptr         left;
    N_Ptr         parent;
    size_type       height;
    Node(T _data):  data(_data),
                    right(NULL),
                    left(NULL),
                    parent(NULL),
                    height(1) {
    }
};

template<typename N_Ptr>
N_Ptr  Avl_tree_inc(N_Ptr x) {
    if (x->right) {
        x = x->right;
        while (x->left) {
            x = x->left;
        }
    } else {
        N_Ptr y = x->parent;
        while (x == y->right) {
            x = y;
            y = y->parent;
        }
        if (x->right != y) {
            x = y;
        }
    }
    return x;
}

template<typename N_Ptr>
N_Ptr Avl_tree_dec(N_Ptr x) {
    if (x->left) {
        N_Ptr y = x->left;
        while (y->right) {
            y = y->right;
        }
        x = y;
    } else {
        N_Ptr y = x->parent;
        while (x == y->left) {
            x = y;
            y = y->parent;
        }
        x = y;
    }
    return x;
}

template <  typename T,
            typename Comp,
            typename Alloc = std::allocator<T>
         > class Avl_tree {
public:

    typedef T                                                   value_type;
    typedef typename Node<value_type>::N_Ptr                  AvlNode;
    typedef typename Node<value_type>::size_type                size_type;
    typedef Comp                                                value_compare;
    typedef typename Alloc::template rebind<Node<T> >::other    allocator_type;

private:

    AvlNode                 m_root;
    AvlNode                 m_end;
    size_type               m_size;
    allocator_type          m_allocator;
    value_compare           m_comp;

    size_type   max(size_type a, size_type b) {
        return (a > b) ? a : b;
    }

    size_type   heightOf(AvlNode node) {
        return (node == NULL) ? 0 : node->height;
    }

    int getBalanceFactor(AvlNode node) {
        return (node == NULL) ? 0 : heightOf(node->left) - heightOf(node->right);
    }

    AvlNode findMin(AvlNode node) const {
        AvlNode current = node;

        if (current != NULL) {
            while (current->left) {
                current = current->left;
            }
        }
        return current;
    }

    AvlNode findMax(AvlNode node) const {
        AvlNode current = node;

        if (current != NULL) {
            while (current->right) {
                current = current->right;
            }
        }
        return current;
    }

    AvlNode rightRotate(AvlNode y) {
        AvlNode		x = y->left;

        if(x->right != NULL)
            x->right->parent = y;
		x->parent = y->parent;
		y->parent = x;
        y->left = x->right;
		x->right = y;
        y->height = max(heightOf(y->left), heightOf(y->right)) + 1;
        x->height = max(heightOf(x->left), heightOf(x->right)) + 1;
        return x;
    }

    AvlNode leftRotate(AvlNode x) {
        AvlNode     y = x->right;

        if(y->left != NULL)
            y->left->parent = x;
        y->parent = x->parent;
		x->parent = y;
		x->right = y->left;
		y->left = x;
        x->height = max(heightOf(x->left), heightOf(x->right)) + 1;
        y->height = max(heightOf(y->left), heightOf(y->right)) + 1;
        return y;
    }

    AvlNode insertNode(AvlNode node, const value_type data, AvlNode parent = NULL) {
        if (!node) {
            node = m_allocator.allocate(1);
            m_allocator.construct(node, data);
            node->parent = parent;
            m_size += 1;
            return node;
        } else if (m_comp(data, node->data)) {
            node->left = insertNode(node->left, data, node);
        }
        else if (m_comp(node->data, data)) {
            node->right = insertNode(node->right, data, node);
        } else {
            return node;
        }

        // Update the balance factor of each node and
        // balance the tree
        node->height = max(heightOf(node->left), heightOf(node->right)) + 1;
        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor > 1) {
            if (m_comp(data, node->left->data)) {
                return rightRotate(node);
            } else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        } else if (balanceFactor < -1) {
            if (m_comp(node->right->data, data)) {
                return leftRotate(node);
            } else {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }

    AvlNode removeNode(AvlNode node, value_type data) {
        if (!node) {
            return node;
        } else if (m_comp(data, node->data)) {
            node->left = removeNode(node->left, data);
        } else if (m_comp(node->data, data)) {
            node->right = removeNode(node->right, data);
        } else {
            if (!node->left || !node->right) {
                AvlNode tmp = node->left ? node->left : node->right;
                if (!tmp) {
                    tmp = node;
                    node = NULL;
                } else {
                    AvlNode temp = node;
                    tmp->parent = node->parent;
                    node = tmp;
                    tmp = temp;
                }
                m_allocator.deallocate(tmp, 1);
                m_size -= 1;
            } else {
                AvlNode tmp = findMin(node->right);
                AvlNode newNode = m_allocator.allocate(1);
                m_allocator.construct(newNode, tmp->data);
                newNode->parent = node->parent;
                newNode->right = node->right;
                newNode->left = node->left;
                node->right->parent = newNode;
                node->left->parent = newNode;
                m_allocator.deallocate(node, 1);
                node = newNode;
                node->right = removeNode(node->right, tmp->data);
            }
        }
        if (!node) return node;

        // Update the balance factor of each node and
        // balance the tree
        node->height = 1 + max(heightOf(node->left), heightOf(node->right));
        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor > 1) {
            if (getBalanceFactor(node->left) >= 0) {
                return rightRotate(node);
            } else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        } else if (balanceFactor < -1) {
            if (getBalanceFactor(node->right) <= 0) {
                return leftRotate(node);
            } else {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }

    AvlNode makeEmpty(AvlNode node) {
        if (node != NULL) {
            makeEmpty(node->left);
            makeEmpty(node->right);
            m_allocator.deallocate(node, 1);
        }
        return NULL;
    }

    AvlNode searchAvlTree(AvlNode node, const value_type val) const
    {
        if (node == NULL) {
            return NULL;
        } else if (m_comp(val, node->data)) {
            return searchAvlTree(node->left, val);
        } else if (m_comp(node->data, val)) {
            return searchAvlTree(node->right, val);
        }
        return node;
    }

public:

    Avl_tree(value_compare c): m_comp(c) {
        m_root = NULL;
        m_size = 0;
        m_end = m_allocator.allocate(1);
        m_allocator.construct(m_end, value_type());
    }
    ~Avl_tree() {
        m_root = makeEmpty(m_root);
        m_allocator.deallocate(m_end,1);
    }

    void    insert(value_type data) {
        m_root = insertNode(m_root, data);
        m_root->parent = m_end;
        m_end->left = m_root;
    }
    void    remove(value_type val) {
        m_root = removeNode(m_root, val);
        if (m_root) {
            m_root->parent = m_end;
            m_end->left = m_root;
        }
    }
    bool    isEmpty() const {
        return (m_size == 0);
    }
    void    clear() {
        m_root = makeEmpty(m_root);
        m_size = 0;
    }
    size_type   getSize() const {
        return m_size;
    }
    size_type   getMaxSize() const {
        return m_allocator.max_size();
    }
    AvlNode getEndNode() const {
        return m_end;
    }
    AvlNode getMinValNode() const {
        return findMin(m_root);
    }
    AvlNode getMaxValNode() const {
        return findMax(m_root);
    }
    AvlNode search(value_type val) const {
        AvlNode node = searchAvlTree(m_root, val);
        if (node == NULL)
            return m_end;
        return node;
    }
    void    swap(Avl_tree& x) {
        AvlNode     x_begin = x.m_root;
        AvlNode     x_end = x.m_end;
        size_type   x_size = x.m_size;

        x.m_size = m_size;
        m_size = x_size;
        x.m_root = m_root;
        x.m_end = m_end;
        m_root = x_begin;
        m_end = x_end;
    }
    AvlNode lower_bound(const value_type val) {
        AvlNode current = findMin(m_root);

        while (current && current != m_end) {
            if (!m_comp(current->data, val))
                return current;
            current = Avl_tree_inc(current);
        }
        return m_end;
    }
    AvlNode upper_bound(const value_type val) {
        AvlNode current = findMin(m_root);

        while (current && current != m_end) {
            if (m_comp(val, current->data))
                return current;
            current = Avl_tree_inc(current);
        }
        return m_end;
    }
};

#endif
