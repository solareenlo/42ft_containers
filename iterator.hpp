/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 23:22:28 by tayamamo          #+#    #+#             */
/*   Updated: 2021/11/28 00:03:01 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#ifndef ITERATOR_HPP_
#define ITERATOR_HPP_

#include <istream>

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
template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
struct iterator {
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
    typedef Category iterator_category;
};
// Ref: https://www.cplusplus.com/reference/iterator/iterator_traits/
template <class Iterator>
struct iterator_traits {
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
};
template <class T>
struct iterator_traits<T*> {
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef random_access_iterator_tag iterator_category;
};
template <class T>
struct iterator_traits<const T*> {
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef random_access_iterator_tag iterator_category;
};

// reverse_iterator
// Ref: https://www.cplusplus.com/reference/iterator/reverse_iterator/
template <class Iterator>
class reverse_iterator {
 private:
    typedef typename ft::iterator_traits<Iterator> traits;

 public:
    // Member types
    typedef Iterator iterator_type;
    typedef typename traits::iterator_category iterator_category;
    typedef typename traits::value_type value_type;
    typedef typename traits::difference_type difference_type;
    typedef typename traits::pointer pointer;
    typedef typename traits::reference reference;

 protected:
    iterator_type current_;

 public:
    // Member functions
    // (constructor)
    reverse_iterator() : current_() {}
    explicit reverse_iterator(iterator_type it) : current_(it) {}
    template <class Iter>
    reverse_iterator(const reverse_iterator<Iter>& rev_it)
        : current_(rev_it.base()) {}
    template <class Iter>
    reverse_iterator& operator=(const reverse_iterator<Iter>& rev_it) {
        current_ = rev_it.base();
        return *this;
    }
    // base
    iterator_type base() const { return current_; }
    reference operator*() const {
        iterator_type copy;
        return *--copy;
    }
    // operator*
    reverse_iterator operator+(difference_type n) const {
        return reverse_iterator(current_ - n);
    }
    // operator++
    // ++a
    reverse_iterator& operator++() {
        --current_;
        return *this;
    }
    // a++
    reverse_iterator operator++(int) {
        reverse_iterator tmp = *this;
        --current_;
        return tmp;
    }
    // operator+=
    reverse_iterator& operator+=(difference_type n) {
        current_ -= n;
        return *this;
    }
    // operator-
    reverse_iterator operator-(difference_type n) const {
        return reverse_iterator(current_ + n);
    }
    // operator--
    // --a
    reverse_iterator& operator--() {
        ++current_;
        return *this;
    }
    // a--
    reverse_iterator operator--(int) {
        reverse_iterator tmp = *this;
        --current_;
        return tmp;
    }
    // operator-=
    reverse_iterator& operator-=(difference_type n) {
        current_ += n;
        return *this;
    }
    // operator->
    pointer operator->() const { return &(operator*()); }
    // operator[]
    reference operator[](difference_type n) const { return current_[-n - 1]; }
};
// relational operators
template <class Iterator>
bool operator==(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs) {
    return lhs.base() == rhs.base();
}
template <class Iterator>
bool operator!=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs) {
    return lhs.base() != rhs.base();
}
template <class Iterator>
bool operator<(const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs) {
    return lhs.base() > rhs.base();
}
template <class Iterator>
bool operator<=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs) {
    return lhs.base() >= rhs.base();
}
template <class Iterator>
bool operator>(const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs) {
    return lhs.base() < rhs.base();
}
template <class Iterator>
bool operator>=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs) {
    return lhs.base() <= rhs.base();
}
// operator++
template <class Iterator>
reverse_iterator<Iterator> operator+(
    typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& rev_it) {
    return reverse_iterator<Iterator>(rev_it.base() - n);
}
// operator-
template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {
    return rhs.base() - lhs.base();
}

}  // namespace ft

#endif  // ITERATOR_HPP_
