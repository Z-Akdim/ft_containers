#ifndef MY_ITERATOR_HPP
#define MY_ITERATOR_HPP
#include "vector.hpp"
#include <vector>
#include <iostream>
#include <string.h>

namespace ft
{
    template <typename T> 
    class MyIterator : public std::iterator<std::input_iterator_tag, T>
    {
        private:
            T *p;
        public:
            MyIterator(T* x) :p(x) {};
            MyIterator() :p(nullptr) {};
            MyIterator(const MyIterator& mit) : p(mit.p) {};
            int& operator*() {return *p;}
            T base() const{return (*p);}
            MyIterator &operator++()
            { 
                ++p;
                return (*this);
            }

            MyIterator operator++(int)
            {
                MyIterator cop(*this); 
                operator++(); 
                return (cop);
            }

            MyIterator &operator--()
            {
                --p; 
                return (*this);
            }

            MyIterator &operator--(int)
            {
                MyIterator cop(*this); 
                operator--(); 
                return (cop);
            }

            MyIterator &operator+(ptrdiff_t nbr)
            {
                p += nbr; 
                return (*this);
            }

            MyIterator &operator-(ptrdiff_t nbr)
            { 
                p -= nbr;
                return (*this);
            }

            MyIterator &operator+=(ptrdiff_t nbr)
            {
                p += nbr;
                return (*this);
            }

            MyIterator &operator-=(ptrdiff_t nbr)
            { 
                p -= nbr;
                return (*this);
            }

            bool operator==(MyIterator const &tmp) const
            { 
                return (p == tmp.p);
            }

            bool operator!=(MyIterator const &tmp) const
            { 
                return (p != tmp.p);
            }

            T &operator[](ptrdiff_t nbr) 
            {
                return (p[nbr]);
            }
    };
};

#endif