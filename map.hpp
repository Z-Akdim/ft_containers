#ifndef MAP_HPP
#define MAP_HPP
#include "ft_container.hpp"


namespace ft{
        template < class Key, class T, class Compare = less<Key>, class Alloc = allocator<pair<const Key,T> > >
        class map
        {
                typedef Key key_type;
                typedef T mapped_type;
                typedef Compare key_compare;
                typedef std::allocator<ft::pair<const key, T>;
                typedef Alloc allocator_type;
                typedef typename allocator_type::reference reference;
                typedef typename allocator_type::const_reference const_reference;
                typedef typename allocator_type::pointer pointer;
                typedef typename allocator_type::const_pointer const_pointer;
                typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
                typedef size_t size_type;
        };
};

#endif