#ifndef AVAL_TREE_HPP
#define AVAL_TREE_HPP

#include <iostream>
#include "make_pair.hpp"

template<typename T>
struct Node {
    typedef Node*           NodePtr;
    typedef const Node*     Const_NodePtr;
    typedef size_t          size_type;

    T               data;
    NodePtr         right;
    NodePtr         left;
    NodePtr         parent;
    size_type       height;
    Node(T _data):  data(_data),
                    right(NULL),
                    left(NULL),
                    parent(NULL),
                    height(1) {
    }
};

template<typename NodePtr>
NodePtr  Avl_tree_increment(NodePtr x) {
    if (x->right) {
        x = x->right;
        while (x->left) {
            x = x->left;
        }
    } else {
        NodePtr y = x->parent;
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

template<typename NodePtr>
NodePtr Avl_tree_decrement(NodePtr x) {
    if (x->left) {
        NodePtr y = x->left;
        while (y->right) {
            y = y->right;
        }
        x = y;
    } else {
        NodePtr y = x->parent;
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
    typedef typename Node<value_type>::NodePtr                  AvlNode;
    typedef typename Node<value_type>::size_type                size_type;
    typedef Comp                                                value_compare;
    typedef typename Alloc::template rebind<Node<T> >::other    allocator_type;

private:

    AvlNode                 _root;
    AvlNode                 _end;
    size_type               _size;
    allocator_type          _allocator;
    value_compare           _comp;

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
            node = _allocator.allocate(1);
            _allocator.construct(node, data);
            node->parent = parent;
            _size += 1;
            return node;
        } else if (_comp(data, node->data)) {
            node->left = insertNode(node->left, data, node);
        }
        else if (_comp(node->data, data)) {
            node->right = insertNode(node->right, data, node);
        } else {
            return node;
        }

        // Update the balance factor of each node and
        // balance the tree
        node->height = max(heightOf(node->left), heightOf(node->right)) + 1;
        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor > 1) {
            if (_comp(data, node->left->data)) {
                return rightRotate(node);
            } else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        } else if (balanceFactor < -1) {
            if (_comp(node->right->data, data)) {
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
        } else if (_comp(data, node->data)) {
            node->left = removeNode(node->left, data);
        } else if (_comp(node->data, data)) {
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
                _allocator.deallocate(tmp, 1);
                _size -= 1;
            } else {
                AvlNode tmp = findMin(node->right);
                AvlNode newNode = _allocator.allocate(1);
                _allocator.construct(newNode, tmp->data);
                newNode->parent = node->parent;
                newNode->right = node->right;
                newNode->left = node->left;
                node->right->parent = newNode;
                node->left->parent = newNode;
                _allocator.deallocate(node, 1);
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
            _allocator.deallocate(node, 1);
        }
        return NULL;
    }

    AvlNode searchAvlTree(AvlNode node, const value_type val) const
    {
        if (node == NULL) {
            return NULL;
        } else if (_comp(val, node->data)) {
            return searchAvlTree(node->left, val);
        } else if (_comp(node->data, val)) {
            return searchAvlTree(node->right, val);
        }
        return node;
    }

public:

    Avl_tree(value_compare c): _comp(c) {
        _root = NULL;
        _size = 0;
        _end = _allocator.allocate(1);
        _allocator.construct(_end, value_type());
    }
    ~Avl_tree() {
        _root = makeEmpty(_root);
        _allocator.deallocate(_end,1);
    }

    void    insert(value_type data) {
        _root = insertNode(_root, data);
        _root->parent = _end;
        _end->left = _root;
    }
    void    remove(value_type val) {
        _root = removeNode(_root, val);
        if (_root) {
            _root->parent = _end;
            _end->left = _root;
        }
    }
    bool    isEmpty() const {
        return (_size == 0);
    }
    void    clear() {
        _root = makeEmpty(_root);
        _size = 0;
    }
    size_type   getSize() const {
        return _size;
    }
    size_type   getMaxSize() const {
        return _allocator.max_size();
    }
    AvlNode getEndNode() const {
        return _end;
    }
    AvlNode getMinValNode() const {
        return findMin(_root);
    }
    AvlNode getMaxValNode() const {
        return findMax(_root);
    }
    AvlNode search(value_type val) const {
        AvlNode node = searchAvlTree(_root, val);
        if (node == NULL)
            return _end;
        return node;
    }
    void    swap(Avl_tree& x) {
        AvlNode     x_begin = x._root;
        AvlNode     x_end = x._end;
        size_type   x_size = x._size;

        x._size = _size;
        _size = x_size;
        x._root = _root;
        x._end = _end;
        _root = x_begin;
        _end = x_end;
    }
    AvlNode lower_bound(const value_type val) {
        AvlNode current = findMin(_root);

        while (current && current != _end) {
            if (!_comp(current->data, val))
                return current;
            current = Avl_tree_increment(current);
        }
        return _end;
    }
    AvlNode upper_bound(const value_type val) {
        AvlNode current = findMin(_root);

        while (current && current != _end) {
            if (_comp(val, current->data))
                return current;
            current = Avl_tree_increment(current);
        }
        return _end;
    }
};

#endif // AVL_HPP
