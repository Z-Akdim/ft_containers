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

template <class Iterator>
class iterator_traits{

    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
};

template <class T>
class iterator_traits<T*>{

    typedef  ptrdiff_t difference_type;
    typedef  T value_type;
    typedef  T* pointer;
    typedef  T& reference;
    typedef   std::random_access_iterator_tag iterator_category;
};

template <class T>
class iterator_traits<const T*>
{
    typedef  ptrdiff_t difference_type;
    typedef  T value_type;
    typedef  const T* pointer;
    typedef  const T& reference;
    typedef   std::random_access_iterator_tag iterator_category;
};

#endif 