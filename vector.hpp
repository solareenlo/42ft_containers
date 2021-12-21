/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 22:35:06 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/21 18:46:43 by tayamamo         ###   ########.fr       */
/* ************************************************************************** */

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <memory>
#include <vector>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "uninitialized.hpp"

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

 private:
    void      M_reallocate_(size_type n);
    size_type M_recommendSize_(size_type new_size) const;

 public:
    // empty container constructor
    explicit vector(const allocator_type& alloc = allocator_type());
    // fill constructor
    explicit vector(size_type n, const value_type& val = value_type(),
                    const allocator_type& alloc = allocator_type());
    // range constructor
    template <class InputIterator>
    vector(InputIterator                               first,
           typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                  InputIterator>::type last,
           const allocator_type& alloc = allocator_type());
    // copy constructor
    vector(const vector& x);
    // destructor
    ~vector();
    // operator=
    vector& operator=(const vector& x);

 public:
    // Iterators
    // begin: Return iterator to beginning
    iterator               begin();
    const_iterator         begin() const;
    // end: Return iterator to end
    iterator               end();
    const_iterator         end() const;
    // rbegin: Return reverse iterator to reverse beginning
    reverse_iterator       rbegin();
    const_reverse_iterator rbegin() const;
    // rend: Return reverse iterator to reverse end
    reverse_iterator       rend();
    const_reverse_iterator rend() const;

    // Capacity
    // size: Return size
    size_type              size() const;
    // max_size: Return maximum size
    size_type              max_size() const;
    // resize: Change size
    void                   resize(size_type n, value_type val = value_type());
    // capacity: Return size of allocated storage capacity
    size_type              capacity() const;
    // empty: Test whether vector is empty
    bool                   empty() const;
    // reserve: Request a change in capacit
    void                   reserve(size_type n);

    // Element access
    // operator[]: Access element
    reference              operator[](size_type n);
    const_reference        operator[](size_type n) const;
    // at:Access element
    reference              at(size_type n);
    const_reference        at(size_type n) const;
    // front: Access first element
    reference              front();
    const_reference        front() const;
    // back: Access last element
    reference              back();
    const_reference        back() const;

    // Modifiers
    // assign: Assign vector content
    template <class InputIterator>
    typename enable_if<!ft::is_integral<InputIterator>::value, void>::type
             assign(InputIterator first, InputIterator last);
    void     assign(size_type n, const value_type& val);
    // push_back: Add element at the end
    void     push_back(const value_type& val);
    // pop_back: Delete last element
    void     pop_back();
    // insert: Insert elements
    iterator insert(iterator position, const value_type& val);
    void     insert(iterator position, size_type n, const value_type& val);
    template <class InputIterator>
    typename enable_if<!ft::is_integral<InputIterator>::value, void>::type
             insert(iterator position, InputIterator first, InputIterator last);
    // erase: Erase elements
    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);
    // swap: Swap content
    void     swap(vector& x);
    // clear: Clear content
    void     clear();

    // Allocator
    // get_allocator: Get allocator
    allocator_type get_allocator() const;
};

template <class T, class Alloc>
void vector<T, Alloc>::M_reallocate_(size_type n) {
    n = M_recommendSize_(n);
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

template <class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::M_recommendSize_(
    size_type new_size) const {
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

// empty container constructor
template <class T, class Alloc>
vector<T, Alloc>::vector(const allocator_type& alloc)
    : m_allocator_(alloc), m_begin_(NULL), m_end_(NULL), m_capacity_(NULL) {}

// fill constructor
template <class T, class Alloc>
vector<T, Alloc>::vector(size_type n, const value_type& val,
                         const allocator_type& alloc)
    : m_allocator_(alloc), m_begin_(NULL), m_end_(NULL), m_capacity_(NULL) {
    size_type capacity = M_recommendSize_(n);
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
    InputIterator                               first,
    typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                           InputIterator>::type last,
    const allocator_type&                       alloc)
    : m_allocator_(alloc), m_begin_(NULL), m_end_(NULL), m_capacity_(NULL) {
    size_type n = last - first;
    size_type capacity = M_recommendSize_(n);
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

// begin()
template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() {
    return iterator(m_begin_);
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin() const {
    return const_iterator(m_begin_);
}

// end()
template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::end() {
    return iterator(m_end_);
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const {
    return const_iterator(m_end_);
}

// rbegin()
template <class T, class Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin() {
    return reverse_iterator(end());
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin()
    const {
    return const_reverse_iterator(end());
}

// rend()
template <class T, class Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend() {
    return reverse_iterator(begin());
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend()
    const {
    return const_reverse_iterator(begin());
}

// size()
template <class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const {
    return static_cast<size_type>(m_end_ - m_begin_);
}

// max_size()
template <class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const {
    return m_allocator_.max_size();
}

// resize()
template <class T, class Alloc>
void vector<T, Alloc>::resize(size_type n, value_type val) {
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

// capacity()
template <class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity() const {
    return static_cast<size_type>(m_capacity_ - m_begin_);
}

// empty()
template <class T, class Alloc>
bool vector<T, Alloc>::empty() const {
    return m_begin_ == m_end_;
}

// reserve()
template <class T, class Alloc>
void vector<T, Alloc>::reserve(size_type n) {
    if (n < capacity()) {
        return;
    }
    M_reallocate_(n);
}

// operator[]
template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](size_type n) {
    return *(m_begin_ + n);
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](
    size_type n) const {
    return *(m_begin_ + n);
}

// at()
template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type n) {
    if (n >= size()) {
        throw std::out_of_range("vector::at");
    }
    return *(m_begin_ + n);
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(
    size_type n) const {
    if (n >= size()) {
        throw std::out_of_range("vector::at");
    }
    return *(m_begin_ + n);
}

// front()
template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::front() {
    return *m_begin_;
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const {
    return *m_begin_;
}

// back()
template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::back() {
    return *(m_end_ - 1);
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const {
    return *(m_end_ - 1);
}

// assign()
template <class T, class Alloc>
template <class InputIterator>
typename enable_if<!ft::is_integral<InputIterator>::value, void>::type
vector<T, Alloc>::assign(InputIterator first, InputIterator last) {
    clear();
    insert(begin(), first, last);
}

template <class T, class Alloc>
void vector<T, Alloc>::assign(size_type n, const value_type& val) {
    clear();
    insert(begin(), n, val);
}

// push_back()
template <class T, class Alloc>
void vector<T, Alloc>::push_back(const value_type& val) {
    insert(end(), val);
}

// pop_back()
template <class T, class Alloc>
void vector<T, Alloc>::pop_back() {
    if (!empty()) {
        m_end_--;
        m_allocator_.destroy(m_end_);
    }
}

// insert()
template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
    iterator position, const value_type& val) {
    size_type offset = position - ft::vector<T>::begin();
    insert(position, 1, val);
    return iterator(begin() + offset);
}

template <class T, class Alloc>
void vector<T, Alloc>::insert(iterator position, size_type n,
                              const value_type& val) {
    if (n == 0) {
        return;
    }
    size_type pos = position - ft::vector<T>::begin();
    size_type end = ft::vector<T>::end() - ft::vector<T>::begin();
    size_type cap = capacity();
    if (n > cap - end) {
        M_reallocate_(cap + n);
    }
    for (size_type i = end; i > pos; i--) {
        m_allocator_.construct(m_begin_ + i - 1 + n, *(m_begin_ + i - 1));
    }
    for (size_type i = 0; i < n; i++) {
        m_allocator_.construct(m_begin_ + pos + i, val);
    }
    m_end_ += n;
}

template <class T, class Alloc>
template <class InputIterator>
typename enable_if<!ft::is_integral<InputIterator>::value, void>::type
vector<T, Alloc>::insert(iterator position, InputIterator first,
                         InputIterator last) {
    if (first == last) {
        return;
    }
    size_type pos = position - ft::vector<T>::begin();
    size_type end = ft::vector<T>::end() - ft::vector<T>::begin();
    size_type cap = capacity();
    size_type n = static_cast<size_type>(last - first);
    if (n > cap - end) {
        M_reallocate_(cap + n);
    }
    for (size_type i = end; i > pos; i--) {
        m_allocator_.construct(m_begin_ + i - 1 + n, *(m_begin_ + i - 1));
    }
    for (size_type i = 0; i < n; i++) {
        m_allocator_.construct(m_begin_ + pos + i, *(first + i));
    }
    m_end_ += n;
}

// erase()
template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position) {
    return erase(position, position + 1);
}

template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first,
                                                            iterator last) {
    if (first == last) {
        return first;
    }
    size_type n = last - first;
    ft::copy(last, end(), first);
    ft::_destroy(m_end_ - n, m_end_, m_allocator_);
    m_end_ -= n;
    return first;
}

// swap()
template <class T, class Alloc>
void vector<T, Alloc>::swap(vector& x) {
    if (this != &x) {
        ft::swap(m_begin_, x.m_begin_);
        ft::swap(m_end_, x.m_end_);
        ft::swap(m_capacity_, x.m_capacity_);
    }
}

// clear()
template <class T, class Alloc>
void vector<T, Alloc>::clear() {
    m_allocator_.destroy(m_begin_);
    m_end_ = m_begin_;
}

// get_allocator()
template <class T, class Alloc>
typename vector<T, Alloc>::allocator_type vector<T, Alloc>::get_allocator()
    const {
    return m_allocator_;
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
// swap()
template <class T, class Alloc>
void swap(ft::vector<T, Alloc>& x, ft::vector<T, Alloc>& y) {
    x.swap(y);
}

}  // namespace ft

#endif  // VECTOR_HPP_
