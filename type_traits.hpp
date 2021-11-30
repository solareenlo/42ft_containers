/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 00:23:01 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/01 04:45:10 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP_
#define TYPE_TRAITS_HPP_

namespace ft {

// Ref: https://www.cplusplus.com/reference/type_traits/enable_if/
template <bool Cond, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
    typedef T type;
};

// Ref: https://www.cplusplus.com/reference/type_traits/integral_constant/
template <class T, T v>
struct integral_constant {
    static const T                  value = v;
    typedef T                       value_type;
    typedef integral_constant<T, v> type;
                                    operator T() { return v; }
};

// Ref: https://www.cplusplus.com/reference/type_traits/true_type/
typedef integral_constant<bool, true>  true_type;
// Ref: https://www.cplusplus.com/reference/type_traits/false_type/
typedef integral_constant<bool, false> false_type;

// Ref: https://www.cplusplus.com/reference/type_traits/is_integral/
template <class T>
struct is_integral : public false_type {};
template <>
struct is_integral<bool> : public true_type {};
template <>
struct is_integral<char> : public true_type {};
template <>
struct is_integral<wchar_t> : public true_type {};
template <>
struct is_integral<signed char> : public true_type {};
template <>
struct is_integral<signed short int> : public true_type {};
template <>
struct is_integral<signed int> : public true_type {};
template <>
struct is_integral<signed long int> : public true_type {};
template <>
struct is_integral<unsigned char> : public true_type {};
template <>
struct is_integral<unsigned short int> : public true_type {};
template <>
struct is_integral<unsigned int> : public true_type {};
template <>
struct is_integral<unsigned long int> : public true_type {};

}  // namespace ft

#endif  // TYPE_TRAITS_HPP_
