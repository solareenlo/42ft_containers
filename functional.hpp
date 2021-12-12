/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functional.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:09:55 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/12 20:20:37 by tayamamo         ###   ########.fr       */
/* ************************************************************************** */

#ifndef FUNCTIONAL_HPP_
#define FUNCTIONAL_HPP_

namespace ft {

// https://www.cplusplus.com/reference/functional/binary_function/
template <class Arg1, class Arg2, class Result>
struct binary_function {
    typedef Arg1   first_argument_type;
    typedef Arg2   second_argument_type;
    typedef Result result_type;
};

// Ref: https://www.cplusplus.com/reference/functional/less/
template <class T>
struct less : binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x < y; }
};

}  // namespace ft

#endif  // FUNCTIONAL_HPP_
