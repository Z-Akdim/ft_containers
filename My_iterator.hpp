#ifndef MY_ITERATOR_HPP
#define MY_ITERATOR_HPP
#include "iterator.hpp"

template <typename T> 
class MyIterator : public std::iterator<std::input_iterator_tag, T>
{
    private:
        T *p;
    public:
        MyIterator(int* x) :p(x) {};
        MyIterator(const MyIterator& mit) : p(mit.p) {};
        
        MyIterator &operator++()
        {
            ++p;
            return (*this);  
        }

        MyIterator &operator++(int)
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
            p + nbr;
            return (*this);
        }

        MyIterator &operator-(ptrdiff_t nbr)
        {
            p - nbr;
            return (*this);
        }

        MyIterator &operator+=(ptrdiff_t nbr)
        {
            p + nbr;
            return (*this);
        }

        MyIterator &operator-=(ptrdiff_t nbr)
        {
            p - nbr;
            return (*this);
        }

        bool operator==(MyIterator const &tmp) const
        {
                return (p == tmp.p)
        }

        bool operator!=(MyIterator const &tmp) const
        {
            rteurn (p != tmp.p);
        }
        
        T &opertor[](ptrdiff_t nbr)
        {
            return (p[nbr]);
        }
        
};

#endif