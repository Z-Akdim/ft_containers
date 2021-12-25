#ifndef MAP_HPP
#define MAP_HPP
#include "ft_container.hpp"

template<typename T> struct Iterator;
template<typename T> struct ConstIterator;

namespace ft{
    template < typename Key, typename T,
    typename Compare = std::less<Key>,
    typename Alloc = std::allocator<pair<const Key,T> > >
  class map
  {
    public:
      typedef Key                                             key_type;
      typedef T                                               mapped_type;
      typedef pair<const key_type,mapped_type>                value_type;
      typedef Compare                                         key_compare;
      typedef Alloc                                           allocator_type;
      typedef typename allocator_type::reference              reference;
      typedef typename allocator_type::const_reference        const_refernce;
      typedef typename allocator_type::pointer                pointer;
      typedef typename allocator_type::const_pointer          const_pointer;
      typedef typename allocator_type::difference_type        difference_type;
      typedef typename allocator_type::size_type              size_type;
      typedef Iterator<value_type>                            iterator;
      typedef ConstIterator<value_type>                       const_iterator;
      typedef Reverse_Iterator<iterator>                      reverse_iterator;
      typedef Reverse_Iterator<const_iterator>                const_reverse_iterator;

      class value_compare : public std::binary_function<value_type, value_type, bool> {
        friend class map;
        protected:
          key_compare   comp;
        value_compare(key_compare c) : comp(c) {}
        public:
        bool operator()(const value_type& x, const value_type& y) const {
        return comp(x.first, y.first);
        }
      };

    private:
      value_compare                                                 _comp;
      allocator_type                                                _allocator;
      Avl_tree<value_type,value_compare>                            _Avl_tree;
      typedef typename Avl_tree<value_type,value_compare>::AvlNode  AvlNode;

    public:
      //empty
      explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()): _allocator(alloc), _comp(comp),
                  _Avl_tree(value_compare(_comp)) {};
      //range
      template <class InputIterator>
      map (InputIterator first, InputIterator last,
              const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()): _comp(comp), _allocator(alloc), 
                  _Avl_tree(value_compare(comp)){
          insert(first, last);
      };
      //copy
      map (const map& x): _comp(x._comp), _allocator(x._allocator),
                  _Avl_tree(value_compare(_comp)) {
              insert(x.begin(), x.end());
          }
      ~map() {}
      map& operator=(const map& x) {
        if (this != &x) {
          clear();
          insert(x.begin(), x.end());
          }
        return *this;
      }
      iterator begin()
      {
        if (!_Avl_tree.getMinValNode())
          return iterator(_Avl_tree.getLastNode());
        return iterator(_Avl_tree.getMinValNode());
      }
      const_iterator begin() const
      {
        if (!_Avl_tree.getMinValNode())
          return const_iterator(_Avl_tree.getLastNode());
        return const_iterator(_Avl_tree.getMinValNode());
      }
      iterator end() {
        return iterator(_Avl_tree.getLastNode());
      }
      const_iterator end() const {
        return const_iterator(_Avl_tree.getLastNode());
      }
      reverse_iterator rbegin() {
        return reverse_iterator(end());
      }
      const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
      }
      reverse_iterator rend() {
        return reverse_iterator(begin());
      }
      const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
      }
      bool empty() const {
        return _Avl_tree.isEmpty();
      }
      size_type size() const {
        return _Avl_tree.getSize();
      }
      size_type max_size() const {
        return _Avl_tree.getMaxSize();
      }
      mapped_type& operator[](const key_type& k) {
        return (*((insert(ft::make_pair(k,mapped_type()))).first)).second;
      }
      pair<iterator,bool> insert(const value_type& val) {
        AvlNode node = _Avl_tree.search(val);
        if (node == _Avl_tree.getLastNode()) {
          _Avl_tree.insert(val);
          return ft::make_pair(iterator(_Avl_tree.search(val)), true);
        }
        return ft::make_pair(iterator(node), false);
      }
      iterator insert(iterator position, const value_type& val) {
        AvlNode node = _Avl_tree.search(val);
        if (node == _Avl_tree.getLastNode()) {
          insert(val);
          return iterator(_Avl_tree.search(val));
        }
        return iterator(node);
        position++;
      }
      template <class InputIterator>
      void insert(InputIterator first, InputIterator last) {
        while (first != last) {
          insert(ft::make_pair(first->first,first->second));
          first++;
        }
      }
      void erase(iterator position) {
        if (position != iterator(NULL)) {
          _Avl_tree.remove(ft::make_pair(position->first,position->second));
        }
      }
      size_type erase(const key_type& k) {
        if (_Avl_tree.search(ft::make_pair(k,mapped_type())) == _Avl_tree.getEndNode()) {
          return 0;
        }
        _Avl_tree.remove(ft::make_pair(k,mapped_type()));
        return 1;
      }
      void erase(iterator first, iterator last) {
        while (first != last) {
          erase(first++);
        }
      }
      void swap(map& x) {
        _Avl_tree.swap(x._Avl_tree);
      }
      void clear() {
        _Avl_tree.clear();
      }
      key_compare key_comp() const {
        return key_compare();
      }
      value_compare value_comp() const {
        return value_compare(_comp);
      }
      iterator find(const key_type& k) {
        return iterator(_Avl_tree.search(ft::make_pair(k,mapped_type())));
      }
      const_iterator find(const key_type& k) const {
        return const_iterator(_Avl_tree.search(ft::make_pair(k,mapped_type())));
      }
      size_type count(const key_type& k) const {
        return (_Avl_tree.search(ft::make_pair(k,mapped_type())) == _Avl_tree.getEndNode()) ? 0 : 1;
      }
      iterator lower_bound(const key_type& k) {
        return iterator(_Avl_tree.lower_bound(ft::make_pair(k,mapped_type())));
      }
      const_iterator lower_bound(const key_type& k) const {
        return const_iterator(_Avl_tree.lower_bound(ft::make_pair(k,mapped_type())));
      }
      iterator upper_bound(const key_type& k) {
        return iterator(_Avl_tree.upper_bound(ft::make_pair(k,mapped_type())));
      }
      const_iterator upper_bound(const key_type& k) const {
        return const_iterator(_Avl_tree.upper_bound(ft::make_pair(k,mapped_type())));
      }
      ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const {
        return ft::make_pair(lower_bound(k), upper_bound(k));
      }
      ft::pair<iterator,iterator> equal_range(const key_type& k) {
        return ft::make_pair(lower_bound(k), upper_bound(k));
      }
      allocator_type get_allocator() const {
        return allocator_type();
      }
  }; 
}

template<typename T>
struct Iterator{
  typedef T                                 value_type;
  typedef T*                                pointer;
  typedef T&                                reference;
  typedef ptrdiff_t                         difference_type;
  typedef std::bidirectional_iterator_tag   iterator_category;

  typedef Iterator<T>                       Self;
  typedef typename Node<T>::N_Ptr         NodePtr;

  Iterator(): _node() {}
  explicit Iterator(NodePtr x): _node(x) {}

  reference operator*() const {
    return (_node)->data;
  }
  pointer operator->() const {
    return &(_node)->data;
  }
  Self  operator++() {
    _node = Avl_tree_inc<NodePtr>(_node);
    return *this;
  }
  Self operator++(int) {
    Self tmp = *this;
    _node = Avl_tree_inc<NodePtr>(_node);
    return tmp;
  }
  Self  operator--() {
    _node = Avl_tree_dec<NodePtr>(_node);
    return *this;
  }
  Self  operator--(int) {
    Self tmp = *this;
    _node = Avl_tree_dec<NodePtr>(_node);
    return tmp;
  }
  bool  operator==(const Self& x) const {
    return _node == x._node;
  }
  bool  operator!=(const Self& x) const {
    return _node != x._node;
  }

  NodePtr       _node;
};

template<typename T>
struct ConstIterator
{
  typedef T                                 value_type;
  typedef const T*                          pointer;
  typedef const T&                          reference;
  typedef ptrdiff_t                         difference_type;
  typedef std::bidirectional_iterator_tag   iterator_category;
  typedef Iterator<T>                       iterator;
 
  typedef ConstIterator<T>                  Self;
  typedef typename Node<T>::Const_NodePtr   NodePtr;

  ConstIterator(): _node() { }
  explicit ConstIterator(NodePtr x): _node(x) { }
  ConstIterator(const iterator& it): _node(it._node) { }

  reference operator*() const {
    return (_node)->data;
  }
  pointer operator->() const {
    return &(_node)->data;
  }
  Self& operator++() {
    _node = Avl_tree_inc<NodePtr>(_node);
    return *this;
  }
  Self  operator++(int) {
    Self tmp = *this;
    _node = Avl_tree_inc<NodePtr>(_node);
    return tmp;
  }
  Self& operator--() {
    _node = Avl_tree_dec<NodePtr>(_node);
    return *this;
  }
  Self  operator--(int) {
    Self tmp = *this;
    _node = Avl_tree_dec<NodePtr>(_node);
    return tmp;
  }
  bool  operator==(const Self& x) const {
    return _node == x._node;
  }
  bool  operator!=(const Self& x) const {
    return _node != x._node;
  }

  NodePtr   _node;
};

template<typename NodePtr>
bool operator==(const Iterator<NodePtr>& x, const ConstIterator<NodePtr>& y) {
  return x._node == y._node;
}

template<typename NodePtr>
bool operator!=(const Iterator<NodePtr>& x, const ConstIterator<NodePtr>& y) {
  return x._node != y._node;
}

#endif