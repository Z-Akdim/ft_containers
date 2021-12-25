#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

template <typename iterator>
class Reverse_Iterator {
protected:
    iterator                                        current;
    typedef iterator_traits<iterator>              traits_type;
public:
    typedef iterator                                iterator_type;
    typedef typename traits_type::difference_type   difference_type;
    typedef typename traits_type::pointer           pointer;
    typedef typename traits_type::reference         reference;

    Reverse_Iterator(): current() {}
    explicit Reverse_Iterator(iterator_type x): current(x) {}
    Reverse_Iterator(const Reverse_Iterator& x): current(x.current) {}
    template<typename Iter>
    Reverse_Iterator(const Reverse_Iterator<Iter>& x): current(x.base()) {}
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
    Reverse_Iterator&   operator++(){
        --current;
        return *this;
    }
    Reverse_Iterator    operator++(int) {
        Reverse_Iterator    tmp = *this;
        --current;
        return tmp;
    }
    Reverse_Iterator&   operator--() {
        ++current;
        return *this;
    }
    Reverse_Iterator    operator--(int) {
        Reverse_Iterator    tmp = *this;
        ++current;
        return tmp;
    }
    Reverse_Iterator    operator+(difference_type n) const {
        return Reverse_Iterator(current - n);
    }
    Reverse_Iterator&   operator+=(difference_type n) {
        current -= n;
        return *this;
    }
    Reverse_Iterator    operator-(difference_type n) const {
        return Reverse_Iterator(current + n);
    }
    Reverse_Iterator&   operator-=(difference_type n) {
        current += n;
        return *this;
    }
    reference   operator[](difference_type n) const {
        return *(*this + n);
    }
};

template<typename iterator>
inline bool operator==(const Reverse_Iterator<iterator>& x, const Reverse_Iterator<iterator>& y) {
    return x.base() == y.base();
}
template<typename iterator>
inline bool operator<(const Reverse_Iterator<iterator>& x, const Reverse_Iterator<iterator>& y) {
    return y.base() < x.base();
}
template<typename _Iterator>
inline bool operator!=(const Reverse_Iterator<_Iterator>& x, const Reverse_Iterator<_Iterator>& y) {
    return !(x == y);
}
template<typename _Iterator>
inline bool operator>(const Reverse_Iterator<_Iterator>& x, const Reverse_Iterator<_Iterator>& y) {
    return y < x;
}
template<typename _Iterator>
inline bool operator<=(const Reverse_Iterator<_Iterator>& x, const Reverse_Iterator<_Iterator>& y) {
    return !(y < x);
}
template<typename _Iterator>
inline bool operator>=(const Reverse_Iterator<_Iterator>& x, const Reverse_Iterator<_Iterator>& y) {
    return !(x < y);
}

// Comparison of Reverse_Iterator to const Reverse_Iterator.
template<typename iteratorL, typename iteratorR>
inline  bool    operator==(const Reverse_Iterator<iteratorL>& x, const Reverse_Iterator<iteratorR>& y) {
    return x.base() == y.base();
}
template<typename iteratorL, typename iteratorR>
inline  bool    operator<(const Reverse_Iterator<iteratorL>& x, const Reverse_Iterator<iteratorR>& y) {
    return y.base() < x.base();
}
template<typename iteratorL, typename iteratorR>
inline  bool    operator!=(const Reverse_Iterator<iteratorL>& x, const Reverse_Iterator<iteratorR>& y) {
    return !(x == y);
}
template<typename iteratorL, typename iteratorR>
inline  bool    operator>(const Reverse_Iterator<iteratorL>& x, const Reverse_Iterator<iteratorR>& y) {
    return y < x;
}
template<typename iteratorL, typename iteratorR>
inline  bool    operator<=(const Reverse_Iterator<iteratorL>& x, const Reverse_Iterator<iteratorR>& y) {
    return !(y < x);
}
template<typename iteratorL, typename iteratorR>
inline  bool    operator>=(const Reverse_Iterator<iteratorL>& x, const Reverse_Iterator<iteratorR>& y) {
    return !(x < y);
}

template<typename iterator>
inline typename Reverse_Iterator<iterator>::difference_type  operator-(const Reverse_Iterator<iterator>& x, const Reverse_Iterator<iterator>& y) {
    return y.base() - x.base();
}
template<typename _IteratorL, typename _IteratorR>
inline typename Reverse_Iterator<_IteratorL>::difference_type    operator-(const Reverse_Iterator<_IteratorL>& x, const Reverse_Iterator<_IteratorR>& y) {
    return y.base() - x.base();
}

template<typename iterator>
inline Reverse_Iterator<iterator> operator+(typename Reverse_Iterator<iterator>::difference_type n, const Reverse_Iterator<iterator>& x) {
    return Reverse_Iterator<iterator>(x.base() - n);
}

#endif // REVERSE_ITERATOR_HPP