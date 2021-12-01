/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 22:35:06 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/01 17:39:08 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <iostream>
#include <memory>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft {

// Ref: https://www.cplusplus.com/reference/vector/vector/
// Ref: https://www.cplusplus.com/reference/memory/allocator/
template <class T, class Alloc = std::allocator<T> >
class vector {
 public:
    typedef T                                    value_type;
    typedef Alloc                                allocator_type;
    typedef typename Alloc::reference            reference;
    typedef typename Alloc::const_reference      const_reference;
    typedef typename Alloc::pointer              pointer;
    typedef typename Alloc::const_pointer        const_pointer;
    typedef ft::random_access_iterator<T>        iterator;
    typedef ft::random_access_iterator<const T>  const_iterator;
    typedef ft::reverse_iterator<iterator>       reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef typename Alloc::difference_type      difference_type;
    typedef typename Alloc::size_type            size_type;

 private:
    allocator_type m_allocator_;
    pointer        m_begin_;
    pointer        m_end_;
    pointer        m_capacity_;

 public:
    // empty container constructor
    explicit vector(const allocator_type& alloc = allocator_type());
    // fill constructor
    explicit vector(size_type n, const value_type& val = value_type(),
                    const allocator_type& alloc = allocator_type());
    // range constructor
    template <class InputIterator>
    vector(InputIterator first, InputIterator last,
           const allocator_type& alloc = allocator_type(),
           typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                  InputIterator>::type* = 0);
    // copy constructor
    vector(const vector& x);
    // destructor
    ~vector();
    // operator=
    vector& operator=(const vector& x);

    // Iterators
 public:
    // begin: Return iterator to beginning
    iterator               begin() { return iterator(m_begin_); }
    const_iterator         begin() const { return const_iterator(m_begin_); }
    // end: Return iterator to end
    iterator               end() { return iterator(m_end_); }
    const_iterator         end() const { return const_iterator(m_end_); }
    // rbegin: Return reverse iterator to reverse beginning
    reverse_iterator       rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }
    // rend: Return reverse iterator to reverse end
    reverse_iterator       rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    // Capacity
 public:
    // size: Return size
    size_type size() const { return static_cast<size_type>(m_end_ - m_begin_); }
    // max_size: Return maximum size
    size_type max_size() const { return m_allocator_.max_size(); }
    // resize: Change size
    void      resize(size_type n, value_type val = value_type()) {
        size_type size = ft::vector<T>::size();
        if (n < size) {
            erase(begin() + n, end());
        } else if (n > size) {
            if (n > capacity()) {
                reserve(n);
            }
            insert(end(), n - size, val);
        }
    }
    // capacity: Return size of allocated storage capacity
    size_type capacity() const {
        return static_cast<size_type>(m_capacity_ - m_begin_);
    }
    // empty: Test whether vector is empty
    bool empty() const { return m_begin_ == m_end_; }
    // reserve: Request a change in capacit
    void reserve(size_type n) {
        if (n < capacity()) {
            return;
        }
        reAllocation(recommendSize(n));
    }

 private:
    void reAllocation(size_type n) {
        pointer   new_array = m_allocator_.allocate(n, &m_begin_);
        size_type size = ft::vector<T>::size();
        for (size_type i = 0; i < size; i++) {
            m_allocator_.construct(new_array + i, *(m_begin_ + i));
            m_allocator_.destroy(m_begin_ + i);
        }
        m_allocator_.deallocate(m_begin_, capacity());
        m_begin_ = new_array;
        m_end_ = m_begin_ + size;
        m_capacity_ = m_begin_ + n;
    }

    // Element access
 public:
    // operator[]: Access element
    reference       operator[](size_type n) { return *(m_begin_ + n); }
    const_reference operator[](size_type n) const { return *(m_begin_ + n); }
    // at:Access element
    reference       at(size_type n) {
        if (n >= size()) {
            throw std::out_of_range("vector::at");
        }
        return *(m_begin_ + n);
    }
    const_reference at(size_type n) const {
        if (n >= size()) {
            throw std::out_of_range("vector::at");
        }
        return *(m_begin_ + n);
    }
    // front: Access first element
    reference       front() { return *m_begin_; }
    const_reference front() const { return *m_begin_; }
    // back: Access last element
    reference       back() { return *(m_end_ - 1); }
    const_reference back() const { return *(m_end_ - 1); }

    // Modifiers
 public:
    // assign: Assign vector content
    template <class InputIterator>
    void assign(InputIterator first, InputIterator last,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                       int>::type* = 0) {
        clear();
        insert(begin(), first, last);
    }
    void assign(size_type n, const value_type& val) {
        clear();
        insert(begin(), n, val);
    }
    // push_back: Add element at the end
    void push_back(const value_type& val) { insert(end(), val); }
    // pop_back: Delete last element
    void pop_back() {
        if (!empty()) {
            m_end_--;
            m_allocator_.destroy(m_end_);
        }
    }
    // insert: Insert elements
    iterator insert(iterator position, const value_type& val) {
        size_type offset = position - begin();
        insert(position, 1, val);
        return iterator(begin() + offset);
    }
    void insert(iterator position, size_type n, const value_type& val) {
        if (n == 0) {
            return;
        }
        size_type pos = position - ft::vector<T>::begin();
        size_type end = ft::vector<T>::end() - ft::vector<T>::begin();
        size_type cap = capacity();
        if (n > cap - end) {
            reAllocation(cap + n);
        }
        for (size_type i = end; i > pos; i--) {
            m_allocator_.construct(m_begin_ + i - 1 + n, *(m_begin_ + i - 1));
        }
        for (size_type i = 0; i < n; i++) {
            m_allocator_.construct(m_begin_ + pos + i, val);
        }
        m_end_ += n;
    }
    template <class InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last,
                typename ft::enable_if<!is_integral<InputIterator>::value,
                                       InputIterator>::type* = 0) {
        if (first == last) {
            return;
        }
        size_type pos = position - ft::vector<T>::begin();
        size_type end = ft::vector<T>::end() - ft::vector<T>::begin();
        size_type cap = capacity();
        size_type n = static_cast<size_type>(last - first);
        if (n > cap - end) {
            reAllocation(cap + n);
        }
        for (size_type i = end; i > pos; i--) {
            m_allocator_.construct(m_begin_ + i - 1 + n, *(m_begin_ + i - 1));
        }
        for (size_type i = 0; i < n; i++) {
            m_allocator_.construct(m_begin_ + pos + i, *(first + i));
        }
        m_end_ += n;
    }
    // erase: Erase elements
    iterator erase(iterator position) { return erase(position, position + 1); }
    iterator erase(iterator first, iterator last) {
        if (first == last) {
            return first;
        }
        size_type n = last - first;
        ft::copy(last, end(), first);
        for (size_type i = 0; i < n; i++) {
            (m_end_ + i)->~T();
        }
        m_end_ -= n;
        return first;
    }
    // swap: Swap content
    void swap(vector& x) {
        if (this != &x) {
            ft::swap(m_begin_, x.m_begin_);
            ft::swap(m_end_, x.m_end_);
            ft::swap(m_capacity_, x.m_capacity_);
        }
    }
    // clear: Clear content
    void clear() {
        m_allocator_.destroy(m_begin_);
        m_end_ = m_begin_;
    }

 private:
    size_type recommendSize(size_type new_size) const {
        const size_type max_size = ft::vector<T>::max_size();
        if (new_size > max_size) {
            throw std::length_error("vector::length_error");
        }
        const size_type cap = capacity();
        if (cap >= max_size / 2) {
            return max_size;
        }
        return ft::max<size_type>(2 * cap, new_size);
    }

    // Allocator
 public:
    // get_allocator: Get allocator
    allocator_type get_allocator() const { return m_allocator_; }
};

// empty container constructor
template <class T, class Alloc>
vector<T, Alloc>::vector(const allocator_type& alloc)
    : m_allocator_(alloc), m_begin_(NULL), m_end_(NULL), m_capacity_(NULL) {}

// fill constructor
template <class T, class Alloc>
vector<T, Alloc>::vector(size_type n, const value_type& val,
                         const allocator_type& alloc)
    : m_allocator_(alloc), m_begin_(NULL), m_end_(NULL), m_capacity_(NULL) {
    size_type capacity = recommendSize(n);
    m_begin_ = m_allocator_.allocate(capacity);
    m_end_ = m_begin_ + n;
    m_capacity_ = m_begin_ + capacity;
    for (size_type i = 0; i < n; i++) {
        m_allocator_.construct(m_begin_ + i, val);
    }
}

// range constructor
template <class T, class Alloc>
template <class InputIterator>
vector<T, Alloc>::vector(
    InputIterator first, InputIterator last, const allocator_type& alloc,
    typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                           InputIterator>::type*)
    : m_allocator_(alloc), m_begin_(NULL), m_end_(NULL), m_capacity_(NULL) {
    size_type n = last - first;
    size_type capacity = recommendSize(n);
    m_begin_ = m_allocator_.allocate(capacity, this);
    m_end_ = m_begin_ + n;
    m_capacity_ = m_begin_ + capacity;
    for (size_type i = 0; i < n; i++) {
        m_allocator_.construct(m_begin_ + i, *(first + i));
    }
}

// copy constructor
template <class T, class Alloc>
vector<T, Alloc>::vector(const vector& x) : m_allocator_(x.get_allocator()) {
    m_begin_ = m_allocator_.allocate(x.capacity(), this);
    m_end_ = m_begin_ + x.size();
    m_capacity_ = m_begin_ + x.capacity();
    for (size_type i = 0; i < x.size(); i++) {
        m_allocator_.construct(m_begin_ + i, *(x.m_begin_ + i));
    }
}

// destructor
template <class T, class Alloc>
vector<T, Alloc>::~vector() {
    clear();
    m_allocator_.deallocate(m_begin_, capacity());
    m_begin_ = NULL;
    m_end_ = NULL;
    m_capacity_ = NULL;
}

// operator=
template <class T, class Alloc>
vector<T, Alloc>& ft::vector<T, Alloc>::operator=(const vector& x) {
    if (this != &x) {
        vector copy(x);
        swap(copy);
    }
    return *this;
}

// relational operators: Relational operators for vector
// a == b
template <class T, class Alloc>
bool operator==(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs) {
    return lhs.size() == rhs.size() &&
           ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}
// a != b
template <class T, class Alloc>
bool operator!=(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs) {
    return !(lhs == rhs);
}

// a < b
template <class T, class Alloc>
bool operator<(const ft::vector<T, Alloc>& lhs,
               const ft::vector<T, Alloc>& rhs) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                       rhs.end());
}
// a <= b
template <class T, class Alloc>
bool operator<=(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs) {
    return !(rhs < lhs);
}
// a > b
template <class T, class Alloc>
bool operator>(const ft::vector<T, Alloc>& lhs,
               const ft::vector<T, Alloc>& rhs) {
    return rhs < lhs;
}
// a >= b
template <class T, class Alloc>
bool operator>=(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs) {
    return !(lhs < rhs);
}
// swap: Exchange contents of vectors
template <class T, class Alloc>
void swap(ft::vector<T, Alloc>& x, ft::vector<T, Alloc>& y) {
    x.swap(y);
}

}  // namespace ft

#endif  // VECTOR_HPP_
