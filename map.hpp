/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:02:04 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/02 10:49:11 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#ifndef MAP_HPP_
#define MAP_HPP_

#include <memory>

#include "functional.hpp"
#include "iterator.hpp"
#include "utility.hpp"

namespace ft {

// Ref: https://www.cplusplus.com/reference/map/map/
template <class Key,                      // map::key_type
          class T,                        // map::mapped_type
          class Compare = ft::less<Key>,  // map::key_compare
          class Alloc =
              std::allocator<pair<const Key, T> >  // map::allocator_type
          >
class map {
    // types:
    typedef Key                                      key_type;
    typedef T                                        mapped_type;
    typedef pair<const key_type, mapped_type>        value_type;
    typedef Compare                                  key_compare;
    typedef Alloc                                    allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;

    typedef implementation - defined                 iterator;
    typedef implementation - defined                 const_iterator;
    typedef ft::reverse_iterator<iterator>           reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;
};

}  // namespace ft

#endif  // MAP_HPP_
