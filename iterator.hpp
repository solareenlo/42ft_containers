/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 23:22:28 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/13 15:02:17 by tayamamo         ###   ########.fr       */
/* ************************************************************************** */

#ifndef ITERATOR_HPP_
#define ITERATOR_HPP_

#include <cstddef>
#include <iterator>

namespace ft {

// Category tags
// Ref: https://www.cplusplus.com/reference/iterator/
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// Classes
// Ref: https://www.cplusplus.com/reference/iterator/iterator/
template <class Category, class T, class Distance = std::ptrdiff_t,
          class Pointer = T*, class Reference = T&>
struct iterator {
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};
// Ref: https://www.cplusplus.com/reference/iterator/iterator_traits/
template <class Iterator>
struct iterator_traits {
    typedef typename Iterator::difference_type   difference_type;
    typedef typename Iterator::value_type        value_type;
    typedef typename Iterator::pointer           pointer;
    typedef typename Iterator::reference         reference;
    typedef typename Iterator::iterator_category iterator_category;
};
template <class T>
struct iterator_traits<T*> {
    typedef std::ptrdiff_t             difference_type;
    typedef T                          value_type;
    typedef T*                         pointer;
    typedef T&                         reference;
    typedef random_access_iterator_tag iterator_category;
};
template <class T>
struct iterator_traits<const T*> {
    typedef std::ptrdiff_t             difference_type;
    typedef T                          value_type;
    typedef const T*                   pointer;
    typedef const T&                   reference;
    typedef random_access_iterator_tag iterator_category;
};

// reverse_iterator
// Ref: https://www.cplusplus.com/reference/iterator/reverse_iterator/
// Ref: https://en.cppreference.com/w/cpp/iterator/reverse_iterator
template <class Iterator>
class reverse_iterator
    : public ft::iterator<
          typename ft::iterator_traits<Iterator>::iterator_category,
          typename ft::iterator_traits<Iterator>::value_type,
          typename ft::iterator_traits<Iterator>::difference_type,
          typename ft::iterator_traits<Iterator>::pointer,
          typename ft::iterator_traits<Iterator>::reference> {
 private:
    typedef typename ft::iterator_traits<Iterator> traits;

    // Member types
 public:
    typedef Iterator                           iterator_type;
    typedef typename traits::iterator_category iterator_category;
    typedef typename traits::value_type        value_type;
    typedef typename traits::difference_type   difference_type;
    typedef typename traits::pointer           pointer;
    typedef typename traits::reference         reference;

 private:
    iterator_type m_current_;

    // Member functions
 public:
    // (constructor)
    reverse_iterator() : m_current_() {}
    explicit reverse_iterator(iterator_type it) : m_current_(it) {}
    template <class Iter>
    reverse_iterator(const reverse_iterator<Iter>& rev_it)
        : m_current_(rev_it.base()) {}
    template <class Iter>
    reverse_iterator& operator=(const reverse_iterator<Iter>& rev_it) {
        m_current_ = rev_it.base();
        return *this;
    }
    // base
    iterator_type base() const { return m_current_; }
    // *a
    reference     operator*() const {
        iterator_type copy = m_current_;
        return *--copy;
    }
    // a + n
    reverse_iterator operator+(difference_type n) const {
        return reverse_iterator(m_current_ - n);
    }
    // ++a
    reverse_iterator& operator++() {
        --m_current_;
        return *this;
    }
    // a++
    reverse_iterator operator++(int) {
        reverse_iterator tmp = *this;
        --m_current_;
        return tmp;
    }
    // a += n
    reverse_iterator& operator+=(difference_type n) {
        m_current_ -= n;
        return *this;
    }
    // a - n
    reverse_iterator operator-(difference_type n) const {
        return reverse_iterator(m_current_ + n);
    }
    // --a
    reverse_iterator& operator--() {
        ++m_current_;
        return *this;
    }
    // a--
    reverse_iterator operator--(int) {
        reverse_iterator tmp = *this;
        --m_current_;
        return tmp;
    }
    // a -= n
    reverse_iterator& operator-=(difference_type n) {
        m_current_ += n;
        return *this;
    }
    // a->m
    pointer   operator->() const { return &(operator*()); }
    // a[n]
    reference operator[](difference_type n) const { return m_current_[-n - 1]; }
};
// a == b
template <class Iterator>
inline bool operator==(const reverse_iterator<Iterator>& lhs,
                       const reverse_iterator<Iterator>& rhs) {
    return lhs.base() == rhs.base();
}
// a != b
template <class Iterator>
inline bool operator!=(const reverse_iterator<Iterator>& lhs,
                       const reverse_iterator<Iterator>& rhs) {
    return lhs.base() != rhs.base();
}
// a < b
template <class Iterator>
inline bool operator<(const reverse_iterator<Iterator>& lhs,
                      const reverse_iterator<Iterator>& rhs) {
    return lhs.base() > rhs.base();
}
// a <= b
template <class Iterator>
inline bool operator<=(const reverse_iterator<Iterator>& lhs,
                       const reverse_iterator<Iterator>& rhs) {
    return lhs.base() >= rhs.base();
}
// a > b
template <class Iterator>
inline bool operator>(const reverse_iterator<Iterator>& lhs,
                      const reverse_iterator<Iterator>& rhs) {
    return lhs.base() < rhs.base();
}
// a >= b
template <class Iterator>
inline bool operator>=(const reverse_iterator<Iterator>& lhs,
                       const reverse_iterator<Iterator>& rhs) {
    return lhs.base() <= rhs.base();
}
// n + a
template <class Iterator>
inline reverse_iterator<Iterator> operator+(
    typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>&                    rev_it) {
    return reverse_iterator<Iterator>(rev_it.base() - n);
}
// a - b
template <class Iterator>
inline typename reverse_iterator<Iterator>::difference_type operator-(
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {
    return rhs.base() - lhs.base();
}

// random access iterator
// Ref: https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
template <typename T>
class random_access_iterator
    : public ft::iterator<ft::random_access_iterator_tag, T> {
 private:
    typedef typename ft::iterator_traits<T*> traits;

 public:
    typedef T                                  iterator_type;
    typedef typename traits::iterator_category iterator_category;
    typedef typename traits::value_type        value_type;
    typedef typename traits::difference_type   difference_type;
    typedef typename traits::pointer           pointer;
    typedef typename traits::reference         reference;

 private:
    pointer m_ptr_;

 public:
    random_access_iterator() : m_ptr_(NULL) {}
    explicit random_access_iterator(pointer ptr) : m_ptr_(ptr) {}
    random_access_iterator(const random_access_iterator& src)
        : m_ptr_(src.m_ptr_) {}
    ~random_access_iterator() {}
    random_access_iterator& operator=(const random_access_iterator& rhs) {
        if (this != &rhs) {
            m_ptr_ = rhs.m_ptr_;
        }
        return *this;
    }

    // a == b
    bool operator==(const random_access_iterator& rhs) const {
        return m_ptr_ == rhs.m_ptr_;
    }
    // a != b
    bool operator!=(const random_access_iterator& rhs) const {
        return m_ptr_ != rhs.m_ptr_;
    }
    // *a
    reference               operator*() const { return *m_ptr_; }
    // a->m
    pointer                 operator->() const { return m_ptr_; }
    // ++a
    random_access_iterator& operator++() {
        ++m_ptr_;
        return *this;
    }
    // a++
    random_access_iterator operator++(int) {
        random_access_iterator tmp = *this;
        ++m_ptr_;
        return tmp;
    }
    // --a
    random_access_iterator& operator--() {
        --m_ptr_;
        return *this;
    }
    // a--
    random_access_iterator operator--(int) {
        random_access_iterator tmp = *this;
        --m_ptr_;
        return tmp;
    }
    // a + n
    random_access_iterator operator+(difference_type n) const {
        return random_access_iterator(m_ptr_ + n);
    }
    // a - n
    random_access_iterator operator-(difference_type n) const {
        return random_access_iterator(m_ptr_ - n);
    }
    // a - b
    difference_type operator-(const random_access_iterator& rhs) const {
        return m_ptr_ - rhs.m_ptr_;
    }
    // a < b
    bool operator<(const random_access_iterator& rhs) const {
        return m_ptr_ < rhs.m_ptr_;
    }
    // a > b
    bool operator>(const random_access_iterator& rhs) const {
        return m_ptr_ > rhs.m_ptr_;
    }
    // a <= b
    bool operator<=(const random_access_iterator& rhs) const {
        return m_ptr_ <= rhs.m_ptr_;
    }
    // a >= b
    bool operator>=(const random_access_iterator& rhs) const {
        return m_ptr_ >= rhs.m_ptr_;
    }
    // a += n
    random_access_iterator& operator+=(difference_type n) {
        m_ptr_ += n;
        return *this;
    }
    // a -= n
    random_access_iterator& operator-=(difference_type n) {
        m_ptr_ -= n;
        return *this;
    }
    // a[n]
    reference operator[](difference_type n) const { return *(m_ptr_ + n); }
};
// n + a
template <class T>
inline random_access_iterator<T> operator+(
    typename random_access_iterator<T>::difference_type n,
    const random_access_iterator<T>&                    rhs) {
    return random_access_iterator<T>(rhs.m_ptr_ + n);
}

}  // namespace ft

#endif  // ITERATOR_HPP_
