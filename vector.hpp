/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 22:35:06 by tayamamo          #+#    #+#             */
/*   Updated: 2021/11/30 01:21:01 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <memory>
#include <vector>

#include "algorithm.hpp"
#include "iterator.hpp"

namespace ft {

// Ref: https://www.cplusplus.com/reference/vector/vector/
// Ref: https://www.cplusplus.com/reference/memory/allocator/
template <class T, class Alloc = std::allocator<T> >
class vector {
 public:
    typedef T                                            value_type;
    typedef Alloc                                        allocator_type;
    typedef typename allocator_type::reference           reference;
    typedef typename allocator_type::const_reference     const_reference;
    typedef typename allocator_type::pointer             pointer;
    typedef typename allocator_type::const_pointer       const_pointer;
    typedef ft::random_access_iterator<value_type>       iterator;
    typedef ft::random_access_iterator<const value_type> const_iterator;
    typedef ft::reverse_iterator<iterator>               reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>         const_reverse_iterator;
    typedef typename allocator_type::difference_type     difference_type;
    typedef typename allocator_type::size_type           size_type;

 private:
    allocator_type m_allocator_;
    pointer        m_begin_;
    pointer        m_end_;
    pointer        m_capacity_;

 public:
    // (constructor)
    explicit vector(const allocator_type& alloc = allocator_type())
        : m_allocator_(alloc),
          m_begin_(NULL),
          m_end_(NULL),
          m_capacity_(NULL) {}
    explicit vector(size_type n, const value_type& val = value_type(),
                    const allocator_type& alloc = allocator_type())
        : m_allocator_(alloc),
          m_begin_(NULL),
          m_end_(NULL),
          m_capacity_(NULL) {}
    template <class InputIterator>
    vector(InputIterator first, InputIterator last,
           const allocator_type& alloc = allocator_type());
    vector(const vector& x);
    // (destructor)
    virtual ~vector();
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
        size_type size = size();
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
        size_type size = size();
        for (size_type i = 0; i < size; i++) {
            m_allocator_.construct(new_array + i, *(m_begin_ + i));
            m_allocator_.destroy(m_begin_ + i);
        }
        m_allocator_.deallocate(m_begin_, capacity());
        m_begin_ = new_array;
        m_end_ = m_begin_ + size;
        m_capacity_ = n;
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
    void assign(InputIterator first, InputIterator last) {
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
        size_type pos = position - begin();
        size_type end = end();
        size_type cap = capacity();
        if (n > cap - end) {
            reAllocation(cap + n);
        }
        for (size_type i = m_end_; i >= pos; i--) {
            m_allocator_.construct(m_begin_ + i, *(m_begin_ + i + n));
        }
        for (size_type i = pos; i < n; i++) {
            m_allocator_.construct(m_begin_ + i, val);
        }
        m_end_ += n;
    }
    template <class InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last) {
        if (first == last) {
            return;
        }
        size_type pos = position - begin();
        size_type end = end();
        size_type cap = capacity();
        size_type n = static_cast<size_type>(last - first);
        if (n > cap - end) {
            reAllocation(cap + n);
        }
        for (size_type i = m_end_; i >= pos; i--) {
            m_allocator_.construct(m_begin_ + i, *(m_begin_ + i + n));
        }
        for (size_type i = pos; i < n; i++) {
            m_allocator_.construct(m_begin_ + i, *(first + i));
        }
        m_end_ += n;
    }
    // erase: Erase elements
    iterator erase(iterator position) { return erase(position, position + 1); }
    iterator erase(iterator first, iterator last) {
        size_type n = last - first;
        ft::copy(last, end(), first);
        for (int i = 0; i < n; i++) {
            (m_end_ + i)->~T();
        }
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
        m_allocator_.destroy();
        m_end_ = m_begin_;
    }

 private:
    size_type recommendSize(size_type new_size) const {
        const size_type max_size = max_size();
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
