/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:06:45 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/01 19:42:50 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#ifndef UTILITY_HPP_
#define UTILITY_HPP_

namespace ft {

// Ref: https://www.cplusplus.com/reference/utility/pair/
template <class T1, class T2>
struct pair {
    // Member types
    typedef T1  first_type;
    typedef T2  second_type;

    // Member variables
    first_type  first;
    second_type second;

    // default constructor
    pair() : first(), second() {}
    // copy / move constructor
    template <class U, class V>
    pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {}
    // initialization constructor
    pair(const first_type& a, const second_type& b) : first(a), second(b) {}

    // operator=
    pair& operator=(const pair& pr);
};

// Ref: https://www.cplusplus.com/reference/utility/pair/operators/
template <class T1, class T2>
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}
template <class T1, class T2>
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(lhs == rhs);
}
template <class T1, class T2>
bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return lhs.first < rhs.first ||
           (lhs.first == rhs.first && lhs.second < rhs.second);
}
template <class T1, class T2>
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(rhs < lhs);
}
template <class T1, class T2>
bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return rhs < lhs;
}
template <class T1, class T2>
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(lhs < rhs);
}

// Ref: https://www.cplusplus.com/reference/utility/make_pair/
template <class T1, class T2>
pair<T1, T2> make_pair(T1 x, T2 y) {
    return (pair<T1, T2>(x, y));
}

}  // namespace ft

#endif  // UTILITY_HPP_
