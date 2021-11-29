/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 23:09:27 by tayamamo          #+#    #+#             */
/*   Updated: 2021/11/30 00:06:26 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP_
#define ALGORITHM_HPP_

namespace ft {

template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last,
                    OutputIterator result) {
    while (first != last) {
        *result = *first;
        ++result;
        ++first;
    }
    return result;
}

template <class T>
inline const T& max(const T& a, const T& b) {
    return (a < b) ? b : a;
}

template <class T>
inline const T& min(const T& a, const T& b) {
    return (a > b) ? b : a;
}

template <class T>
inline void swap(T& a, T& b) {
    T c(a);
    a = b;
    b = c;
}

template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
    while (first1 != last1) {
        if (*first1 != *first2) {
            return false;
        }
        ++first1;
        ++first2;
        return true;
    }
}

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2) {
    while (first1 != last1) {
        if (first2 == last2 || *first2 < *first1) {
            return false;
        } else if (*first1 < *first2) {
            return true;
        }
        ++first1;
        ++first2;
    }
    return (first2 != last2);
}

}  // namespace ft

#endif  // ALGORITHM_HPP_
