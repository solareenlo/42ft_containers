/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:02:04 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/19 23:15:11 by tayamamo         ###   ########.fr       */
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
              std::allocator<ft::pair<const Key, T> >  // map::allocator_type
          >
class map {
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
    typedef tree<value_type, value_compare, Alloc> tree_type;

 public:
    typedef typename tree_type::iterator         iterator;
    typedef typename tree_type::const_iterator   const_iterator;
    typedef ft::reverse_iterator<iterator>       reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

 private:
    key_compare    m_key_compare_;
    allocator_type m_allocator_;
    tree_type      m_tree_;

 public:
    // Constructor
    explicit map(const key_compare&    comp = key_compare(),
                 const allocator_type& alloc = allocator_type())
        : m_key_compare_(comp),
          m_allocator_(alloc),
          m_tree_(value_comp(), alloc) {}
    template <class InputIterator>
    map(InputIterator first, InputIterator last,
        const key_compare&    comp = key_compare(),
        const allocator_type& alloc = allocator_type())
        : m_key_compare_(comp),
          m_allocator_(alloc),
          m_tree_(value_comp(), alloc) {
        insert(first, last);
    }
    map(const map& x)
        : m_key_compare_(x.m_key_compare_),
          m_allocator_(x.m_allocator_),
          m_tree_(x.value_comp(), x.m_allocator_) {
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
    bool         empty() const { return m_tree_.size() == 0; }
    size_type    size() const { return m_tree_.size(); }
    size_type    max_size() const { return m_tree_.max_size(); }
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
    void      erase(iterator position) { m_tree_.erase(position); }
    size_type erase(const key_type& k) {
        return m_tree_.erase(ft::make_pair(k, T()));
    }
    void erase(iterator first, iterator last) { m_tree_.erase(first, last); }
    void swap(map& x) { m_tree_.swap(x.m_tree_); }
    void clear() { m_tree_.clear(); }
    // Observers
    key_compare   key_comp() const { return m_key_compare_; }
    value_compare value_comp() const { return value_compare(m_key_compare_); }
    // Operations
    iterator      find(const key_type& k) {
        return m_tree_.find(ft::make_pair(k, T()));
    }
    const_iterator find(const key_type& k) const {
        return m_tree_.find(ft::make_pair(k, T()));
    }
    size_type count(const key_type& k) const {
        return m_tree_.count(ft::make_pair(k, T()));
    }
    iterator lower_bound(const key_type& k) {
        return iterator(m_tree_.lower_bound(ft::make_pair(k, T())));
    }
    const_iterator lower_bound(const key_type& k) const {
        return const_iterator(m_tree_.lower_bound(ft::make_pair(k, T())));
    }
    iterator upper_bound(const key_type& k) {
        return iterator(m_tree_.upper_bound(ft::make_pair(k, T())));
    }
    const_iterator upper_bound(const key_type& k) const {
        return const_iterator(m_tree_.upper_bound(ft::make_pair(k, T())));
    }
    ft::pair<const_iterator, const_iterator> equal_range(
        const key_type& k) const {
        return m_tree_.equal_range(ft::make_pair(k, T()));
    }
    ft::pair<iterator, iterator> equal_range(const key_type& k) {
        return m_tree_.equal_range(ft::make_pair(k, T()));
    }
    // Allocator
    allocator_type get_allocator() const { return m_allocator_; }
};

}  // namespace ft

#endif  // MAP_HPP_
