#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "ft_container.hpp"

namespace ft
{
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

    template <class T, class Alloc>
    bool operator==(const vector<T, Alloc> &lhs,
                    const vector<T, Alloc> &rhs)
    {
        if (lhs.size() != rhs.size())
            return (false);
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc> &lhs,
                    const vector<T, Alloc> &rhs)
    {
        return (!(lhs == rhs));
    }

    template <class T, class Alloc>
    bool operator<(const vector<T, Alloc> &lhs,
                   const vector<T, Alloc> &rhs)
    {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool operator<=(const vector<T, Alloc> &lhs,
                    const vector<T, Alloc> &rhs)
    {
        return (!(rhs < lhs));
    }

    template <class T, class Alloc>
    bool operator>(const vector<T, Alloc> &lhs,
                   const vector<T, Alloc> &rhs)
    {
        return (!(lhs < rhs));
    }

    template <class T, class Alloc>
    bool operator>=(const vector<T, Alloc> &lhs,
                    const vector<T, Alloc> &rhs)
    {
        return (!(lhs <= rhs));
    }
};
#endif 