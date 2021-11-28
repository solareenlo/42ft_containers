/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 22:35:06 by tayamamo          #+#    #+#             */
/*   Updated: 2021/11/28 15:41:52 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <memory>

#include "iterator.hpp"

namespace ft {

// Ref: https://www.cplusplus.com/reference/vector/vector/
template <class T, class Alloc = std::allocator<T> >
class vector {
 public:
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef ft::random_access_iterator<value_type> iterator;
    typedef ft::random_access_iterator<const value_type> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::size_type size_type;

 private:
    allocator_type allocator_;
    pointer begin_;
    pointer end_;
    pointer capacity_;

 public:
    // (constructor)
    explicit vector(const allocator_type& alloc = allocator_type())
        : allocator_(alloc), begin_(NULL), end_(NULL), capacity_(NULL) {}
    explicit vector(size_type n, const value_type& val = value_type(),
                    const allocator_type& alloc = allocator_type())
        : allocator_(alloc), begin_(NULL), end_(NULL), capacity_(NULL) {}
    template <class InputIterator>
    vector(InputIterator first, InputIterator last,
           const allocator_type& alloc = allocator_type());
    vector(const vector& x);
    // (destructor)
    virtual ~vector();
    // operator=
    vector& operator=(const vector& x);

 public:
    // Iterators
    // begin
    iterator begin() { return iterator(begin_); }
    const_iterator begin() const { return const_iterator(begin_); }
    // end
    iterator end();
    const_iterator end() const;
    // rbegin
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    // rend
    reverse_iterator rend();
    const_reverse_iterator rend() const;

 public:
    // Capacity
    // size
    size_type size() const;
    // max_size
    size_type max_size() const;
    // resize
    void resize(size_type n, value_type val = value_type());
    // capacity
    size_type capacity() const;
    // empty
    bool empty() const;
    // reserve
    void reserve(size_type n);

 public:
    // Element access
    // operator[]
    reference operator[](size_type n);
    const_reference operator[](size_type n) const;
    // at
    reference at(size_type n);
    const_reference at(size_type n) const;
    // front
    reference front();
    const_reference front() const;
    // back
    reference back();
    const_reference back() const;

 public:
    // Modifiers
    // assign
    template <class InputIterator>
    void assign(InputIterator first, InputIterator last);
    void assign(size_type n, const value_type& val);
    // push_back
    void push_back(const value_type& val);
    // pop_back
    void pop_back();
    // insert
    iterator insert(iterator position, const value_type& val);
    void insert(iterator position, size_type n, const value_type& val);
    template <class InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last);
    // erase
    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);
    // swap
    void swap(vector& x);
    // clear
    void clear();

 public:
    // Allocator
    allocator_type get_allocator() const;
};
// relational operators
template <class T, class Alloc>
bool operator==(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs);
template <class T, class Alloc>
bool operator!=(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs);
template <class T, class Alloc>
bool operator<(const ft::vector<T, Alloc>& lhs,
               const ft::vector<T, Alloc>& rhs);
template <class T, class Alloc>
bool operator<=(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs);
template <class T, class Alloc>
bool operator>(const ft::vector<T, Alloc>& lhs,
               const ft::vector<T, Alloc>& rhs);
template <class T, class Alloc>
bool operator>=(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs);
// swap
template <class T, class Alloc>
void swap(ft::vector<T, Alloc>& x, ft::vector<T, Alloc>& y);

}  // namespace ft

#endif  // VECTOR_HPP_
