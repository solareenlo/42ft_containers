/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:57:53 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/19 23:42:58 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#ifndef SET_HPP_
#define SET_HPP_

#include <memory>

#include "functional.hpp"
#include "tree.hpp"
#include "type_traits.hpp"

namespace ft {

template <class Key, class Compare = ft::less<Key>,
          class Alloc = std::allocator<Key> >
class set {
 private:
    typedef tree<Key, Compare, Alloc> tree_type;

 public:
    typedef Key                                      key_type;
    typedef key_type                                 value_type;
    typedef Compare                                  key_compare;
    typedef key_compare                              value_compare;
    typedef Alloc                                    allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;

    typedef typename tree_type::iterator             iterator;
    typedef typename tree_type::const_iterator       const_iterator;
    typedef ft::reverse_iterator<iterator>           reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

 private:
    key_compare    m_key_compare_;
    allocator_type m_allocator_;
    tree_type      m_tree_;

 public:
    // Constructor
    explicit set(const key_compare&    comp = key_compare(),
                 const allocator_type& alloc = allocator_type())
        : m_key_compare_(comp), m_allocator_(alloc), m_tree_(comp, alloc) {}
    template <class InputIterator>
    set(InputIterator first, InputIterator last,
        const key_compare&    comp = key_compare(),
        const allocator_type& alloc = allocator_type())
        : m_key_compare_(comp), m_allocator_(alloc), m_tree_(comp, alloc) {
        insert(first, last);
    }
    set(const set& x)
        : m_key_compare_(x.m_key_compare_),
          m_allocator_(x.m_allocator_),
          m_tree_(x.m_key_compare_, x.m_allocator_) {
        insert(x.begin(), x.end());
    }
    // Destructor
    ~set() { clear(); }
    // operator=
    set& operator=(const set& x) {
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
        return reverse_iterator(m_tree_.end());
    }
    reverse_iterator       rend() { return reverse_iterator(m_tree_.begin()); }
    const_reverse_iterator rend() const {
        return reverse_iterator(m_tree_.begin());
    }
    // Capacity
    bool                 empty() const { return m_tree_.size() == 0; }
    size_type            size() const { return m_tree_.size(); }
    size_type            max_size() const { return m_tree_.max_size(); }
    // Modifiers
    pair<iterator, bool> insert(const value_type& val) {
        return m_tree_.insert(val);
    }
    iterator insert(iterator position, const value_type& val) {
        (void)position;
        return m_tree_.insert(val).first;
    }
    template <class InputIterator>
    void insert(InputIterator first, InputIterator last,
                typename enable_if<!ft::is_integral<InputIterator>::value,
                                   InputIterator>::type* = 0) {
        while (first != last) {
            insert(*first);
            ++first;
        }
    }
    void      erase(iterator position) { m_tree_.erase(position); }
    size_type erase(const value_type& val) { return m_tree_.erase(val); }
    void erase(iterator first, iterator last) { m_tree_.erase(first, last); }
    void swap(set& x) { m_tree_.swap(x.m_tree_); }
    void clear() { m_tree_.clear(); }
    // Observers
    key_compare    key_comp() const { return m_key_compare_; }
    value_compare  value_comp() const { return m_key_compare_; }
    // Operations
    iterator       find(const value_type& val) { return m_tree_.find(val); }
    const_iterator find(const value_type& val) const {
        return m_tree_.find(val);
    }
    size_type count(const value_type& val) const { return m_tree_.count(val); }
    iterator  lower_bound(const value_type& val) const {
        return iterator(m_tree_.lower_bound(val));
    }
    iterator upper_bound(const value_type& val) const {
        return iterator(m_tree_.upper_bound(val));
    }
    ft::pair<iterator, iterator> equal_range(const value_type& val) const {
        return ft::make_pair(iterator(m_tree_.lower_bound(val)),
                             iterator(m_tree_.upper_bound(val)));
    }
    // Allocator
    allocator_type get_allocator() const { return m_allocator_; }
};

}  // namespace ft

#endif  // SET_HPP_
