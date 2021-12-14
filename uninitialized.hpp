/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uninitialized.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 22:20:39 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/15 05:47:08 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNINITIALIZED_HPP_
#define UNINITIALIZED_HPP_

namespace ft {

// Ref:
// https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.3/a02038.html

template <typename ForwardIterator, typename Allocator>
inline void _destroy(ForwardIterator first, ForwardIterator last,
                     Allocator alloc) {
    for (ForwardIterator it = first; it != last; ++it) {
        alloc.destroy(&*it);
    }
}

template <typename InputIterator, typename ForwardIterator, typename Allocator>
inline ForwardIterator uninitialized_copy_a(InputIterator   first,
                                            InputIterator   last,
                                            ForwardIterator result,
                                            Allocator&      alloc) {
    ForwardIterator cur = result;
    try {
        for (; first != last; ++first, (void)++cur) {
            alloc.construct(&*cur, *first);
        }
        return cur;
    } catch (...) {
        ft::_destroy(result, cur, alloc);
        throw;
    }
}

template <typename InputIterator, typename ForwardIterator, typename Allocator>
inline ForwardIterator uninitialized_move_a(InputIterator   first,
                                            InputIterator   last,
                                            ForwardIterator result,
                                            Allocator&      alloc) {
    return ft::uninitialized_copy_a(first, last, result, alloc);
}

template <typename ForwardIterator, typename T, typename Allocator>
inline void uninitialized_fill_a(ForwardIterator first, ForwardIterator last,
                                 const T& val, Allocator& alloc) {
    ForwardIterator cur = first;
    try {
        for (; cur != last; ++cur) {
            alloc.construct(&*cur, val);
        }
    } catch (...) {
        ft::_destroy(first, cur, alloc);
        throw;
    }
}

template <typename ForwardIterator, typename T, typename InputIterator,
          typename Allocator>
inline ForwardIterator uninitialized_fill_move(
    ForwardIterator result, ForwardIterator mid, const T& val,
    InputIterator first, InputIterator last, Allocator& alloc) {
    ft::uninitialized_fill_a(result, mid, val, alloc);
    try {
        return ft::uninitialized_move_a(first, last, mid, alloc);
    } catch (...) {
        ft::_destroy(result, mid, alloc);
        throw;
    }
}

template <typename InputIterator, typename ForwardIterator, typename T,
          typename Allocator>
inline void uninitialized_move_fill(InputIterator first1, InputIterator last1,
                                    ForwardIterator first2,
                                    ForwardIterator last2, const T& val,
                                    Allocator& alloc) {
    ForwardIterator mid2 =
        ft::uninitialized_move_a(first1, last1, first2, alloc);
    try {
        ft::uninitialized_fill_a(mid2, last2, val, alloc);
    } catch (...) {
        ft::_destroy(first2, mid2, alloc);
        throw;
    }
}

}  // namespace ft

#endif  // UNINITIALIZED_HPP_
