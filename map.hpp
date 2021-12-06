/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:02:04 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/06 12:09:48 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#ifndef MAP_HPP_
#define MAP_HPP_

#include <memory>

#include "functional.hpp"
#include "iterator.hpp"
#include "tree.hpp"
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
 private:
    typedef tree<Key, T, Compare, Alloc> tree_type;
    tree_type                            m_tree_;

 public:
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
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::size_type       size_type;
    typedef typename tree_type::iterator             iterator;
    typedef typename tree_type::const_iterator       const_iterator;
    typedef ft::reverse_iterator<iterator>           reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

    class value_compare
        : public ft::binary_function<value_type, value_type, bool> {
        friend class map;

     protected:
        key_compare comp;
        explicit value_compare(key_compare c) : comp(c) {}

     public:
        bool operator()(const value_type& x, const value_type& y) const {
            return comp(x.first, y.first);
        }
    };

 public:
    explicit map(const key_compare&    comp = key_compare(),
                 const allocator_type& alloc = allocator_type());
    template <class InputIterator>
    map(InputIterator first, InputIterator last,
        const key_compare&    comp = key_compare(),
        const allocator_type& alloc = allocator_type());
    map(const map& x);
    ~map();
    map&                   operator=(const map& x);

    // Iterators
    iterator               begin();
    const_iterator         begin() const;
    iterator               end();
    const_iterator         end() const;
    reverse_iterator       rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator       rend();
    const_reverse_iterator rend() const;
    // Capacity
    bool                   empty() const;
    size_type              size() const;
    size_type              max_size() const;
    // Element access
    mapped_type&           operator[](const key_type& k);
    // Modifiers
    pair<iterator, bool>   insert(const value_type& val);
    iterator               insert(iterator position, const value_type& val);
    template <class InputIterator>
    void           insert(InputIterator first, InputIterator last);
    void           erase(iterator position);
    size_type      erase(const key_type& k);
    void           erase(iterator first, iterator last);
    void           swap(map& x);
    void           clear();
    // Observers
    key_compare    key_comp() const;
    value_compare  value_comp() const;
    // Operations
    iterator       find(const key_type& k);
    const_iterator find(const key_type& k) const;
    size_type      count(const key_type& k) const;
    iterator       lower_bound(const key_type& k);
    const_iterator lower_bound(const key_type& k) const;
    iterator       upper_bound(const key_type& k);
    const_iterator upper_bound(const key_type& k) const;
    pair<const_iterator, const_iterator> equal_range(const key_type& k) const;
    pair<iterator, iterator>             equal_range(const key_type& k);
    // Allocator
    allocator_type                       get_allocator() const;
};

}  // namespace ft

#endif  // MAP_HPP_
