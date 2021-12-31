
#ifndef VECTOR_HPP
#define VECTOR_HPP

// #include "equal.hpp"
// #include "enable_if.hpp"
#include "is_integral.hpp"
#include "reverse_iterator.hpp"
#include "helps.hpp"
// #include "lexicographical_compare.hpp"

template <typename iterator> class normal_iterator;

namespace ft {

template < typename T, typename Alloc = std::allocator<T> >
class vector {

public:

        typedef T                                                   value_type;
        typedef Alloc                                               allocator_type;
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;
        typedef normal_iterator<pointer>                            iterator;
        typedef normal_iterator<const_pointer>                      const_iterator;
        typedef ReverseIterator<iterator>                           reverse_iterator;
        typedef ReverseIterator<const_iterator>                     const_reverse_iterator;
        typedef ptrdiff_t                                           difference_type;
        typedef size_t                                              size_type;

private:

        pointer             _buff;
        size_type           _capacity;
        size_type           _size;
        allocator_type      _allocator;

        void    reallocate(void)
        {
            size_type       newCapacity = (!_capacity) ? 1 : 2 * _capacity;
            value_type      *ptr = _allocator.allocate(newCapacity);

            for (size_type i = 0; i < _size; i++)
                ptr[i] = _buff[i];
            _allocator.deallocate(_buff, _capacity);
            _buff = ptr;
            _capacity = newCapacity;
        }

public:

    explicit vector(const allocator_type& alloc = allocator_type())
                    : _buff(NULL),_capacity(0),_size(0),_allocator(alloc) {
    }
    explicit vector(size_type n, const value_type& val = value_type(),
                    const allocator_type& alloc = allocator_type())
                    : _capacity(n), _size(0), _allocator(alloc) {
        _buff = _allocator.allocate(_capacity);
        while (_size < _capacity) {
            _buff[_size++] = val;
        }
    }
    template <class InputIterator>
    vector(InputIterator first, InputIterator last,
            typename enable_if<!is_integral<InputIterator>::value, bool>::type = true,
            const allocator_type& alloc = allocator_type())
            : _capacity(static_cast<size_type>(last - first)), _size(0), _allocator(alloc) {
        _buff = _allocator.allocate(_capacity);
        while (first != last)
            _buff[_size++] = *first++;
    }
    vector(const vector& x): _capacity(x.size()), _size(0), _allocator(x._allocator) {
        _buff = _allocator.allocate(_capacity);
        while (_size < _capacity) {
            _buff[_size] = x[_size];
            ++_size;
        }
    }
    ~vector() {
        clear();
        _allocator.deallocate(_buff, _capacity);
    }
    vector& operator=(const vector& x) {
        if (_capacity < x.size()) {
            _allocator.deallocate(_buff, _capacity);
            _capacity = x.size();
            _buff = _allocator.allocate(_capacity);
        }
        _size = 0;
        while (_size < x.size()) {
            _buff[_size] = x[_size];
            ++_size;
        }
        return *this;
    }

    iterator begin() {
        return iterator(_buff);
    }
    const_iterator  begin() const {
        return const_iterator(_buff);
    }
    iterator end() {
        return iterator(_buff + _size);
    }
    const_iterator  end() const {
        return const_iterator(_buff + _size);
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

    size_type   size() const {
        return _size;
    }
    size_type   max_size() const {
        return _allocator.max_size();
    }
    void resize(size_type n, value_type val = value_type()) {
        if (n < _size)
            _size = n;
        else if (n > _size) {
            if (n > _capacity) {
                value_type* ptr = _allocator.allocate(n);
                for (size_type i = 0; i < _size; i++)
                    ptr[i] = _buff[i];
                _allocator.deallocate(_buff, _capacity);
                _capacity = n;
                _buff = ptr;
            }
            for (; _size < n; ++_size)
                _buff[_size] = val;
        }
    }
    size_type   capacity() const {
        return _capacity;
    }
    bool        empty() const {
        return (_size == 0);
    }
    void reserve(size_type n) {
        if (n > _capacity)
        {
            value_type      *ptr = _allocator.allocate(n);
            for (size_type i = 0; i < _size; i++)
                ptr[i] = _buff[i];
            _allocator.deallocate(_buff, _capacity);
            _capacity = n;
            _buff = ptr;
        }
    }

    value_type&     operator[](size_type n) {
        return _buff[n];
    }
    const value_type&   operator[](size_type n) const {
        return _buff[n];
    }
    value_type& at(size_type n) {
        if (n < 0 || n >= _size)
            throw std::out_of_range("vector");
        return _buff[n];
    }
    const value_type&   at(size_type n) const {
        if (n < 0 || n >= _size)
            throw std::out_of_range("vector");
        return _buff[n];
    }
    value_type& front() {
        return _buff[0];
    }
    const value_type&   front() const {
        return _buff[0];
    }
    value_type& back() {
        return _buff[_size - 1];
    }
    const value_type&   back() const {
        return _buff[_size - 1];
    }

    template <class InputIterator>
    void assign(InputIterator first, InputIterator last,
                typename enable_if<!is_integral<InputIterator>::value, bool>::type = true) {
        size_type rangeLength = static_cast<size_type>(last - first);
        clear();
        if (rangeLength > _capacity) {
            _allocator.deallocate(_buff, _capacity);
            _buff = _allocator.allocate(rangeLength);
            _capacity = rangeLength;
        }
        while (_size < rangeLength) { 
            _buff[_size++] = *first++;
        }
    }
    void assign(size_type n, const value_type& val) {
        clear();
        if (n > _capacity) {
            _allocator.deallocate(_buff, _capacity);
            _buff = _allocator.allocate(n);
            _capacity = n;
        }
        while (_size < n) {
            _buff[_size++] = val;
        }
    }
    void    push_back(const value_type& val) {
        if (_size + 1 > _capacity)
            reallocate();
        _buff[_size++] = val;
    }
    void pop_back() {
        _allocator.destroy(&_buff[_size - 1]);
        --_size;
    }
    iterator    insert(iterator position, const value_type& val) {
        size_type capacityTodealloc = _capacity;
        _capacity = (_size + 1 > _capacity) ? _size + 1 : _capacity;
        pointer tmp = _allocator.allocate(_capacity);
        iterator it = begin();
        iterator ite = end();
        _size = 0;
        while (it < position)
            tmp[_size++] = *it++;
        iterator ret = iterator(tmp + _size);
        tmp[_size++] = val;
        while (it < ite) {
            tmp[_size++] = *it++;
        }
        _allocator.deallocate(_buff, capacityTodealloc);
        _buff = tmp;
        return ret;
    }
    void insert(iterator position, size_type n, const value_type& val) {
        size_type capacityTodealloc = _capacity;
        _capacity = (_size + n > _capacity) ? _size + n : _capacity;
        pointer tmp = _allocator.allocate(_capacity);
        iterator it = begin();
        iterator ite = end();
        _size = 0;
        while (it < position) {
            tmp[_size++] = *it++;
        }
        for (size_t i = 0; i < n; i++) {
            tmp[_size++] = val;
        }
        while (it < ite) {
            tmp[_size++] = *it++;
        }
        _allocator.deallocate(_buff, capacityTodealloc);
        _buff = tmp;
    }
    template <class InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last,
                typename enable_if<!is_integral<InputIterator>::value, bool>::type = true) {
        size_type capacityTodealloc = _capacity;
        _capacity = (_size + (last - first) > _capacity) ? _size + (last - first)  : _capacity;
        pointer tmp = _allocator.allocate(_capacity);
        iterator it = begin();
        iterator ite = end();
        _size = 0;
        while (it < position) {
            tmp[_size++] = *it++;
        }
        while (first != last) {
            tmp[_size++] = *first++;
        }
        while (it < ite) {
            tmp[_size++] = *it++;
        }
        _allocator.deallocate(_buff, capacityTodealloc);
        _buff = tmp;
    }
    iterator erase (iterator position) {
        iterator it = position;
        iterator ite = end();
        while (it + 1 != ite) {
            *it = *(it + 1);
            it++;
        }
        _size -= 1;
        return position;
    }
    iterator erase (iterator first, iterator last) {
        iterator ite = end();
        _size -= (last -first);
        iterator it = first;
        while (last != ite) {
            *it++ = *last++; 
        }
        return first;
    }
    void swap (vector& x) {
        pointer tmp = x._buff;
        size_type sz = x._size;
        size_type capacity = x._capacity;

        x._capacity = _capacity;
        _capacity = capacity;
        x._size = _size;
        _size = sz;
        x._buff = _buff;
        _buff = tmp;
    }
    void clear() {
        for (size_t i = 0; i < _size; i++) {
            _allocator.destroy(&(_buff[i]));
        }
        _size = 0;
    }
    allocator_type get_allocator() const {
        return allocator_type();
    }

};  // vector class

template <class T, class Alloc>
bool    operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return (lhs.size() != rhs.size()) ? false : equal(lhs.begin(), lhs.end(), rhs.begin());
}
template <class T, class Alloc>
bool    operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return !(lhs == rhs);
}
template <class T, class Alloc>
bool    operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template <class T, class Alloc>
bool    operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return !(lhs > rhs);
}
template <class T, class Alloc>
bool    operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return lexicographical_compare(rhs.begin(), rhs.end(),lhs.begin(), lhs.end());
}
template <class T, class Alloc>
bool    operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return !(lhs < rhs);
}
template<typename T, typename Alloc>
void    swap(vector<T,Alloc>& x, vector<T,Alloc>& y) {
    x.swap(y);
}

}   // namespace ft

template <typename iterator>
class normal_iterator {

public:

        typedef iterator                                                        iterator_type;
        typedef typename iterators_traits<iterator_type>::difference_type       difference_type;
        typedef typename iterators_traits<iterator_type>::value_type            value_type;
        typedef typename iterators_traits<iterator_type>::pointer               pointer;
        typedef typename iterators_traits<iterator_type>::reference             reference;
        typedef typename iterators_traits<iterator_type>::iterator_category     iterator_category;

private:

        iterator_type                                                           _ptr;

public:

        normal_iterator(): _ptr() {}
        explicit normal_iterator(iterator_type x): _ptr(x) {}
        normal_iterator(const normal_iterator& x): _ptr(x._ptr) {}
        template <typename iter>
        normal_iterator(const normal_iterator<iter>& i): _ptr(i.base()) {}
        const iterator_type&    base() const {
            return _ptr;
        }

        reference   operator*() const { 
            return *_ptr;
        }
        pointer     operator->() const {
            return _ptr;
        }
        normal_iterator&  operator++() {
            ++_ptr;
            return *this;
        }
        normal_iterator    operator++(int) {
            return normal_iterator(_ptr++);
        }
        normal_iterator&  operator--() {
            --_ptr;
            return *this;
        }
        normal_iterator   operator--(int) {
            return normal_iterator(_ptr--);
        }
        reference    operator[](difference_type n) const {
            return _ptr[n];
        }
        normal_iterator&    operator+=(difference_type n) {
            _ptr += n;
            return *this;
        }
        normal_iterator     operator+(difference_type n) {
            return normal_iterator(_ptr + n);
        }
        normal_iterator&    operator-=(difference_type n) {
            _ptr -= n;
            return *this;
        }
        normal_iterator   operator-(difference_type n) const {
            return normal_iterator(_ptr - n);
        } 
};

template <typename iterator1, typename iterator2>
bool operator==(const normal_iterator<iterator1>& x, const normal_iterator<iterator2>& y) {
    return (x.base() == y.base());
}
template <typename iterator1, typename iterator2>
bool operator>(const normal_iterator<iterator1>& x, const normal_iterator<iterator2>& y) {
    return x.base() > y.base();
}
template <typename iterator1, typename iterator2>
bool operator<(const normal_iterator<iterator1>& x, const normal_iterator<iterator2>& y) {
    return x.base() < y.base();
}
template <typename iterator1, typename iterator2>
bool operator!=(const normal_iterator<iterator1>& x, const normal_iterator<iterator2>& y) {
    return !(x == y);
}
template <typename iterator1, typename iterator2>
bool operator>=(const normal_iterator<iterator1>& x, const normal_iterator<iterator2>& y) {
    return !(x < y);
}
template <typename iterator1, typename iterator2>
bool operator<=(const normal_iterator<iterator1>& x, const normal_iterator<iterator2>& y) {
    return !(x > y);
}
template <typename iterator1, typename iterator2>
typename normal_iterator<iterator1>::difference_type operator-(const normal_iterator<iterator1>& x, const normal_iterator<iterator2>& y) {
    return x.base() - y.base();
}
template<typename iterator>
normal_iterator<iterator>   operator+(typename normal_iterator<iterator>::difference_type n, const normal_iterator<iterator>& x) {
    return normal_iterator<iterator>(x.base() + n);
}

#endif // VECTOR_HPP
