#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

template <typename iterator>
class ReverseIterator {
protected:
    iterator                                        current;
    typedef iterators_traits<iterator>              traits_type;
public:
    typedef iterator                                iterator_type;
    typedef typename traits_type::difference_type   difference_type;
    typedef typename traits_type::pointer           pointer;
    typedef typename traits_type::reference         reference;

    ReverseIterator(): current() {}
    explicit ReverseIterator(iterator_type x): current(x) {}
    ReverseIterator(const ReverseIterator& x): current(x.current) {}
    template<typename Iter>
    ReverseIterator(const ReverseIterator<Iter>& x): current(x.base()) {}
    iterator_type   base() const {
        return current;
    }
    reference    operator*() const {
        iterator tmp = current;
        return *--tmp;
    }
    pointer operator->() const {
        return &(operator*());
    }
    ReverseIterator&   operator++(){
        --current;
        return *this;
    }
    ReverseIterator    operator++(int) {
        ReverseIterator    tmp = *this;
        --current;
        return tmp;
    }
    ReverseIterator&   operator--() {
        ++current;
        return *this;
    }
    ReverseIterator    operator--(int) {
        ReverseIterator    tmp = *this;
        ++current;
        return tmp;
    }
    ReverseIterator    operator+(difference_type n) const {
        return ReverseIterator(current - n);
    }
    ReverseIterator&   operator+=(difference_type n) {
        current -= n;
        return *this;
    }
    ReverseIterator    operator-(difference_type n) const {
        return ReverseIterator(current + n);
    }
    ReverseIterator&   operator-=(difference_type n) {
        current += n;
        return *this;
    }
    reference   operator[](difference_type n) const {
        return *(*this + n);
    }
};

template<typename iterator>
inline bool operator==(const ReverseIterator<iterator>& x, const ReverseIterator<iterator>& y) {
    return x.base() == y.base();
}
template<typename iterator>
inline bool operator<(const ReverseIterator<iterator>& x, const ReverseIterator<iterator>& y) {
    return y.base() < x.base();
}
template<typename _Iterator>
inline bool operator!=(const ReverseIterator<_Iterator>& x, const ReverseIterator<_Iterator>& y) {
    return !(x == y);
}
template<typename _Iterator>
inline bool operator>(const ReverseIterator<_Iterator>& x, const ReverseIterator<_Iterator>& y) {
    return y < x;
}
template<typename _Iterator>
inline bool operator<=(const ReverseIterator<_Iterator>& x, const ReverseIterator<_Iterator>& y) {
    return !(y < x);
}
template<typename _Iterator>
inline bool operator>=(const ReverseIterator<_Iterator>& x, const ReverseIterator<_Iterator>& y) {
    return !(x < y);
}

// Comparison of ReverseIterator to const ReverseIterator.
template<typename iteratorL, typename iteratorR>
inline  bool    operator==(const ReverseIterator<iteratorL>& x, const ReverseIterator<iteratorR>& y) {
    return x.base() == y.base();
}
template<typename iteratorL, typename iteratorR>
inline  bool    operator<(const ReverseIterator<iteratorL>& x, const ReverseIterator<iteratorR>& y) {
    return y.base() < x.base();
}
template<typename iteratorL, typename iteratorR>
inline  bool    operator!=(const ReverseIterator<iteratorL>& x, const ReverseIterator<iteratorR>& y) {
    return !(x == y);
}
template<typename iteratorL, typename iteratorR>
inline  bool    operator>(const ReverseIterator<iteratorL>& x, const ReverseIterator<iteratorR>& y) {
    return y < x;
}
template<typename iteratorL, typename iteratorR>
inline  bool    operator<=(const ReverseIterator<iteratorL>& x, const ReverseIterator<iteratorR>& y) {
    return !(y < x);
}
template<typename iteratorL, typename iteratorR>
inline  bool    operator>=(const ReverseIterator<iteratorL>& x, const ReverseIterator<iteratorR>& y) {
    return !(x < y);
}

template<typename iterator>
inline typename ReverseIterator<iterator>::difference_type  operator-(const ReverseIterator<iterator>& x, const ReverseIterator<iterator>& y) {
    return y.base() - x.base();
}
template<typename _IteratorL, typename _IteratorR>
inline typename ReverseIterator<_IteratorL>::difference_type    operator-(const ReverseIterator<_IteratorL>& x, const ReverseIterator<_IteratorR>& y) {
    return y.base() - x.base();
}

template<typename iterator>
inline ReverseIterator<iterator> operator+(typename ReverseIterator<iterator>::difference_type n, const ReverseIterator<iterator>& x) {
    return ReverseIterator<iterator>(x.base() - n);
}

#endif // REVERSE_ITERATOR_HPP
