#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <string>
#include <iostream>

template <class Category, // iterator::iterator_category
            class T,      // iterator::value_type
            class Distance = ptrdiff_t, // iterator::difference_type
            class Pointer = T*, // iterator::pointer
            class Reference = T&> // iterator::reference
struct iterator
{
  typedef T         value_type;
  typedef Distance  difference_type;
  typedef Pointer   pointer;
  typedef Reference reference;
  typedef Category  iterator_category;
};

#endif 