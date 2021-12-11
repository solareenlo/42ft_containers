/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:02:04 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/11 16:09:51 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#ifndef MAP_HPP_
#define MAP_HPP_

#include <iostream>
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
              std::allocator<ft::pair<const Key, T> >  // map::allocator_type
          >
class map {
 private:
    typedef tree<Key, T, Compare, Alloc> tree_type;

 public:
    // types:
    typedef Key                                      key_type;
    typedef T                                        mapped_type;
    typedef ft::pair<const key_type, mapped_type>    value_type;
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

 private:
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

 private:
    key_compare    m_key_compare_;
    allocator_type m_allocator_;
    tree_type      m_tree_;

 public:
    // Constructor
    explicit map(const key_compare&    comp = key_compare(),
                 const allocator_type& alloc = allocator_type())
        : m_allocator_(alloc), m_tree_(comp, alloc) {}
    template <class InputIterator>
    map(InputIterator first, InputIterator last,
        const key_compare&    comp = key_compare(),
        const allocator_type& alloc = allocator_type())
        : m_allocator_(alloc), m_tree_(comp, alloc) {
        insert(first, last);
    }
    map(const map& x)
        : m_allocator_(x.m_allocator_),
          m_tree_(x.m_key_compare_, x.m_allocator_) {
        insert(x.begin(), x.end());
    }
    // Destructor
    ~map() { clear(); }
    // operator=
    map& operator=(const map& x) {
        if (this != &x) {
            this->m_key_compare_ = x.m_key_compare_;
            this->m_allocator_ = x.m_allocator_;
            this->m_tree_ = x.m_tree_;
        }
        return *this;
    }

    // Iterators
    iterator               begin() { return m_tree_.begin(); }
    const_iterator         begin() const { return m_tree_.begin(); }
    iterator               end() { return m_tree_.end(); }
    const_iterator         end() const { return m_tree_.end(); }
    reverse_iterator       rbegin() { return reverse_iterator(m_tree_.end()); }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(m_tree_.end());
    }
    reverse_iterator       rend() { return reverse_iterator(m_tree_.begin()); }
    const_reverse_iterator rend() const {
        return const_reverse_iterator(m_tree_.begin());
    }
    // Capacity
    bool         empty() const { return m_tree_.getSize() == 0; };
    size_type    size() const { return m_tree_.getSize(); }
    size_type    max_size() const;
    // Element access
    mapped_type& operator[](const key_type& k) {
        value_type val = ft::make_pair(k, mapped_type());
        return (*((insert(val)).first)).second;
    }
    // Modifiers
    pair<iterator, bool> insert(const value_type& val) {
        return m_tree_.insert(val);
    }
    iterator insert(iterator position, const value_type& val) {
        (void)position;
        return m_tree_.insert(val).first;
    }
    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        while (first != last) {
            insert(*first);
            ++first;
        }
    }
    void                                 erase(iterator position);
    size_type                            erase(const key_type& k);
    void                                 erase(iterator first, iterator last);
    void                                 swap(map& x);
    void                                 clear() { m_tree_.clear(); }
    // Observers
    key_compare                          key_comp() const;
    value_compare                        value_comp() const;
    // Operations
    iterator                             find(const key_type& k);
    const_iterator                       find(const key_type& k) const;
    size_type                            count(const key_type& k) const;
    iterator                             lower_bound(const key_type& k);
    const_iterator                       lower_bound(const key_type& k) const;
    iterator                             upper_bound(const key_type& k);
    const_iterator                       upper_bound(const key_type& k) const;
    pair<const_iterator, const_iterator> equal_range(const key_type& k) const;
    pair<iterator, iterator>             equal_range(const key_type& k);
    // Allocator
    allocator_type                       get_allocator() const;
};

}  // namespace ft

#endif  // MAP_HPP_
