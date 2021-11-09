#ifndef MY_ITERATOR_HPP
#define MY_ITERATOR_HPP
#include "iterator.hpp"

template <typename T> 
class MyIterator : public std::iterator<std::input_iterator_tag, T>
{
    private:
            int *p;
    public:
           MyIterator(int* x) :p(x) {};
           MyIterator(const MyIterator& mit) : p(mit.p) {};  
};

#endif