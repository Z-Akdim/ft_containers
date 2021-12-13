#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
    template <typename T1, typename T2>
    struct pair {
        typedef T1      first_type;
        typedef T2      second_type;

        first_type      first;
        second_type     second;
        pair() : first(), second() {}
        template<typename U, typename V>
        pair(const pair<U,V>& pr): first(pr.first), second(pr.second) {}
        pair (const first_type& i, const second_type& j) : first(i), second(j) {}
        pair&   operator=(const pair& pr) {
            first = pr.first;
            second = pr.second;
            return *this;
        }

        template <class U1, class U2>
        friend bool operator==(const pair<U1,U2>& lhs, const pair<U1,U2>& rhs);
        template <class U1, class U2>
        friend bool operator!=(const pair<U1,U2>& lhs, const pair<U1,U2>& rhs);
        template <class U1, class U2>
        friend bool operator<(const pair<U1,U2>& lhs, const pair<U1,U2>& rhs);
        template <class U1, class U2>
        friend bool operator<=(const pair<U1,U2>& lhs, const pair<U1,U2>& rhs);
        template <class U1, class U2>
        friend bool operator>(const pair<U1,U2>& lhs, const pair<U1,U2>& rhs);
        template <class U1, class U2>
        friend bool operator>=(const pair<U1,U2>& lhs, const pair<U1,U2>& rhs);
    };

    template <class T1, class T2>
    bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
    template <class T1, class T2>
    bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return !(lhs == rhs);
    }
    template <class T1, class T2>
    bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }
    template <class T1, class T2>
    bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return !(rhs < lhs);
    }	
    template <class T1, class T2>
    bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return rhs < lhs;
    }
    template <class T1, class T2>
    bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return !(lhs < rhs);
    }

}

#endif