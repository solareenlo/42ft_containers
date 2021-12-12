/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 23:09:27 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/12 20:20:33 by tayamamo         ###   ########.fr       */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP_
#define ALGORITHM_HPP_

namespace ft {

// Ref: https://www.cplusplus.com/reference/algorithm/copy/
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

// Ref: https://www.cplusplus.com/reference/algorithm/max/
template <class T>
inline const T& max(const T& a, const T& b) {
    return (a < b) ? b : a;
}

// Ref: https://www.cplusplus.com/reference/algorithm/min/
template <class T>
inline const T& min(const T& a, const T& b) {
    return (a > b) ? b : a;
}

// Ref: https://www.cplusplus.com/reference/algorithm/swap/
template <class T>
inline void swap(T& a, T& b) {
    T c(a);
    a = b;
    b = c;
}

// Ref: https://www.cplusplus.com/reference/algorithm/equal/
template <class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1, InputIterator1 last1,
                  InputIterator2 first2) {
    for (; first1 != last1; ++first1, ++first2) {
        if (*first1 != *first2) {
            return false;
        }
    }
    return true;
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
inline bool equal(InputIterator1 first1, InputIterator1 last1,
                  InputIterator2 first2, BinaryPredicate pred) {
    for (; first1 != last1; ++first1, ++first2) {
        if (!pred(*first1, *first2)) {
            return false;
        }
    }
    return true;
}

// Ref:
// https://www.cplusplus.com/reference/algorithm/lexicographical_compare/
template <class InputIterator1, class InputIterator2>
inline bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                    InputIterator2 first2,
                                    InputIterator2 last2) {
    for (; first1 != last1; ++first1, ++first2) {
        if (first2 == last2 || *first2 < *first1) {
            return false;
        }
        if (*first1 < *first2) {
            return true;
        }
    }
    return (first2 != last2);
}

template <class Compare, class InputIterator1, class InputIterator2>
inline bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                    InputIterator2 first2, InputIterator2 last2,
                                    Compare comp) {
    for (; first2 != last2; ++first1, ++first2) {
        if (first1 == last1 || comp(*first1, *first2)) {
            return true;
        }
        if (comp(*first2, *first1)) {
            return false;
        }
    }
    return false;
}

}  // namespace ft

#endif  // ALGORITHM_HPP_
