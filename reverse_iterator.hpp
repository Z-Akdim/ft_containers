#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP
#include "ft_container.hpp"
#include "My_iterator.hpp"

namespace ft
{
    template <class Iterator>
    class reverse_iterator
    {
        public:
            typedef Iterator iterator_type;
            typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename ft::iterator_traits<Iterator>::value_type value_type;
            typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
            typedef typename ft::iterator_traits<Iterator>::pointer pointer;
            typedef typename ft::iterator_traits<Iterator>::reference reference;
        private:
            iterator_type *ptr;
        public:
            reverse_iterator(){};
            explicit reverse_iterator (iterator_type it){};
            template <class Iter>
            reverse_iterator (const reverse_iterator<Iter>& rev_it){};

            reference operator*() const
            {
                return ptr;
            }
            reverse_iterator operator+ (ptrdiff_t n) const
            {
                ptr -= n; return (*this);
            }
            reverse_iterator& operator++()
            {
                --ptr;
                return (*this);
            }
            reverse_iterator  operator++(int)
            {
                reverse_iterator tmp(*this);
                operator++();
                return (tmp);
            }
            reverse_iterator& operator+= (ptrdiff_t n)
            {
                ptr -= n;
                return (*this);
            }
            reverse_iterator operator- (ptrdiff_t n) const
            {
                ptr += n;
                return (*this);
            }
            reverse_iterator& operator--()
            {
                ++ptr;
                return *this;
            }
            reverse_iterator  operator--(int)
            {
                reverse_iterator tmp(*this);
                operator--();
                return (tmp);
            }
            reverse_iterator& operator-= (ptrdiff_t n)
            {
                ptr += n;
                return (*this);
            }
            pointer operator->() const
            {
                return &(operator*());
            }
            reference operator[] (ptrdiff_t n) const
            {
                return (ptr[n]);
            }
    };
};
#endif