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
    N_Ptr         Right;
    N_Ptr         Left;
    N_Ptr         parent;
    size_type       height;
    Node(T _data):  data(_data),
                    Right(NULL),
                    Left(NULL),
                    parent(NULL),
                    height(1) {
    }
};

template<typename N_Ptr>
N_Ptr  Avl_tree_inc(N_Ptr x) {
    if (x->Right) {
        x = x->Right;
        while (x->Left) {
            x = x->Left;
        }
    } else {
        N_Ptr y = x->parent;
        while (x == y->Right) {
            x = y;
            y = y->parent;
        }
        if (x->Right != y) {
            x = y;
        }
    }
    return x;
}

template<typename N_Ptr>
N_Ptr Avl_tree_dec(N_Ptr x) {
    if (x->Left) {
        N_Ptr y = x->Left;
        while (y->Right) {
            y = y->Right;
        }
        x = y;
    } else {
        N_Ptr y = x->parent;
        while (x == y->Left) {
            x = y;
            y = y->parent;
        }
        x = y;
    }
    return x;
}

template <  typename T, typename Comp, typename Alloc = std::allocator<T> >
class Avl_tree
{
    public:

        typedef T                                                   value_type;
        typedef typename Node<value_type>::N_Ptr                  AvlNode;
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
            if (node == NULL)
                return 0;
            else 
                return node->height;
        }

        int getBalanceFactor(AvlNode node) {
            if (node == NULL)
                return 0;
            else
                return (heightOf(node->Left) - heightOf(node->Right));
        }

        AvlNode findMin(AvlNode node) const {
            AvlNode current = node;

            if (current != NULL) {
                while (current->Left) {
                    current = current->Left;
                }
            }
            return current;
        }

        AvlNode findMax(AvlNode node) const {
            AvlNode current = node;

            if (current != NULL) {
                while (current->Right) {
                    current = current->Right;
                }
            }
            return current;
        }

        AvlNode R_Rotate(AvlNode y) {
            AvlNode	x = y->Left;

            if(x->Right != NULL)
                x->Right->parent = y;
    		x->parent = y->parent;
    		y->parent = x;
            y->Left = x->Right;
    		x->Right = y;
            y->height = max(heightOf(y->Left), heightOf(y->Right)) + 1;
            x->height = max(heightOf(x->Left), heightOf(x->Right)) + 1;
            return x;
        }

        AvlNode L_Rotate(AvlNode x) {
            AvlNode     y = x->Right;

            if(y->Left != NULL)
                y->Left->parent = x;
            y->parent = x->parent;
    		x->parent = y;
    		x->Right = y->Left;
    		y->Left = x;
            x->height = max(heightOf(x->Left), heightOf(x->Right)) + 1;
            y->height = max(heightOf(y->Left), heightOf(y->Right)) + 1;
            return y;
        }

        AvlNode insertNode(AvlNode node, const value_type data, AvlNode parent = NULL) {
            if (!node) {
                node = _allocator.allocate(1);
                _allocator.construct(node, data);
                node->parent = parent;
                _size += 1;
                return node;
            }
            else if (_comp(data, node->data)) {
                node->Left = insertNode(node->Left, data, node);
            }
            else if (_comp(node->data, data)) {
                node->Right = insertNode(node->Right, data, node);
            }
            else {
                return node;
            }

            // Update the balance factor of each node and
            // balance the tree
            node->height = max(heightOf(node->Left), heightOf(node->Right)) + 1;
            int balanceFactor = getBalanceFactor(node);
            if (balanceFactor > 1) {
                if (_comp(data, node->Left->data)) {
                    return R_Rotate(node);
                } else {
                    node->Left = L_Rotate(node->Left);
                    return R_Rotate(node);
                }
            } else if (balanceFactor < -1) {
                if (_comp(node->Right->data, data)) {
                    return L_Rotate(node);
                } else {
                    node->Right = R_Rotate(node->Right);
                    return L_Rotate(node);
                }
            }
            return node;
        }

        AvlNode removeNode(AvlNode node, value_type data) {
            if (!node) {
                return node;
            } else if (_comp(data, node->data)) {
                node->Left = removeNode(node->Left, data);
            } else if (_comp(node->data, data)) {
                node->Right = removeNode(node->Right, data);
            } else {
                if (!node->Left || !node->Right) {
                    AvlNode tmp = node->Left ? node->Left : node->Right;
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
                    AvlNode tmp = findMin(node->Right);
                    AvlNode newNode = _allocator.allocate(1);
                    _allocator.construct(newNode, tmp->data);
                    newNode->parent = node->parent;
                    newNode->Right = node->Right;
                    newNode->Left = node->Left;
                    node->Right->parent = newNode;
                    node->Left->parent = newNode;
                    _allocator.deallocate(node, 1);
                    node = newNode;
                    node->Right = removeNode(node->Right, tmp->data);
                }
            }
            if (!node) return node;

            // Update the balance factor of each node and
            // balance the tree
            node->height = 1 + max(heightOf(node->Left), heightOf(node->Right));
            int balanceFactor = getBalanceFactor(node);
            if (balanceFactor > 1) {
                if (getBalanceFactor(node->Left) >= 0) {
                    return R_Rotate(node);
                } else {
                    node->Left = L_Rotate(node->Left);
                    return R_Rotate(node);
                }
            } else if (balanceFactor < -1) {
                if (getBalanceFactor(node->Right) <= 0) {
                    return L_Rotate(node);
                } else {
                    node->Right = R_Rotate(node->Right);
                    return L_Rotate(node);
                }
            }
            return node;
        }

        AvlNode makeEmpty(AvlNode node) {
            if (node != NULL) {
                makeEmpty(node->Left);
                makeEmpty(node->Right);
                _allocator.deallocate(node, 1);
            }
            return NULL;
        }

        AvlNode searchAvlTree(AvlNode node, const value_type val) const
        {
            if (node == NULL) {
                return NULL;
            } else if (_comp(val, node->data)) {
                return searchAvlTree(node->Left, val);
            } else if (_comp(node->data, val)) {
                return searchAvlTree(node->Right, val);
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
            _end->Left = _root;
        }
        void    remove(value_type val) {
            _root = removeNode(_root, val);
            if (_root) {
                _root->parent = _end;
                _end->Left = _root;
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
        AvlNode getLastNode() const {
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
                current = Avl_tree_inc(current);
            }
            return _end;
        }
        AvlNode upper_bound(const value_type val) {
            AvlNode current = findMin(_root);

            while (current && current != _end) {
                if (_comp(val, current->data))
                    return current;
                current = Avl_tree_inc(current);
            }
            return _end;
        }

        // void printTree(Node *root, string indent, bool last) {
        //     if (root != nullptr) {
        //     cout << indent;
        //     if (last) {
        //       cout << "R----";
        //       indent += "   ";
        //     } else {
        //       cout << "L----";
        //       indent += "|  ";
        //     }
        //     cout << root->key << endl;
        //     printTree(root->left, indent, false);
        //     printTree(root->right, indent, true);
        //     }
        // }
};

#endif
