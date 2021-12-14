/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 12:05:12 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/14 15:25:06 by tayamamo         ###   ########.fr       */
/* ************************************************************************** */

#ifndef DEQUE_HPP_
#define DEQUE_HPP_

#include <deque>
#include <exception>
#include <memory>

#include "algorithm.hpp"
#include "iterator.hpp"

#ifndef DEQUE_BUF_SIZE
#define DEQUE_BUF_SIZE 512
#endif

inline size_t deque_buf_size(size_t size) {
    if (size < DEQUE_BUF_SIZE) {
        return size_t(DEQUE_BUF_SIZE / size);
    }
    return size_t(1);
}

namespace ft {

// Ref:
// https://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/a00641_source.html
template <class T>
class deque_iterator {
 public:
    typedef ft::random_access_iterator_tag iterator_category;
    typedef T                              value_type;
    typedef std::ptrdiff_t                 difference_type;
    typedef value_type&                    reference;
    typedef value_type*                    pointer;

 private:
    typedef value_type**               map_pointer;
    typedef deque_iterator<value_type> iterator;

 private:
    pointer     m_cur_;
    pointer     m_first_;
    pointer     m_last_;
    map_pointer m_node_;

 private:
    static size_t node_size() { return deque_buf_size(sizeof(T)); }
    void          set_node(map_pointer new_node) {
        m_node_ = new_node;
        m_first_ = *new_node;
        m_last_ = m_first_ + difference_type(node_size());
    }
    deque_iterator(pointer x, map_pointer y)
        : m_cur_(x), m_first_(*y), m_last_(*y + node_size()), m_node_(y) {}

 public:
    // construct/copy/destroy:
    deque_iterator() : m_cur_(), m_first_(), m_last_(), m_node_() {}
    explicit deque_iterator(const iterator& src)
        : m_cur_(src.m_cur_),
          m_first_(src.m_first_),
          m_last_(src.m_last_),
          m_node_(src.m_node_) {}
    ~deque_iterator() {}
    iterator& operator=(const iterator& rhs) {
        if (this != &rhs) {
            m_cur_ = rhs.m_cur_;
            m_first_ = rhs.m_first_;
            m_last_ = rhs.m_last_;
            m_node_ = rhs.m_node_;
        }
        return *this;
    }
    // a == b
    bool      operator==(iterator rhs) const { return m_cur_ == rhs.m_cur_; }
    // a != b
    bool      operator!=(iterator rhs) const { return m_cur_ != rhs.m_cur_; }
    // *a
    reference operator*() const { return *m_cur_; }
    // a->
    pointer   operator->() const { return m_cur_; }
    // a++
    iterator& operator++() {
        ++m_cur_;
        if (m_cur_ == m_last_) {
            _set_node(m_node_ + 1);
            m_cur_ = m_first_;
        }
        return *this;
    }
    // ++a
    iterator operator++(int) {
        iterator old = *this;
        ++*this;
        return old;
    }
    // a--
    iterator& operator--() {
        if (m_cur_ == m_first_) {
            set_node(m_node_ - 1);
            m_cur_ = m_last_;
        }
        --m_cur_;
        return *this;
    }
    // --a
    iterator operator--(int) {
        iterator old = *this;
        --*this;
        return old;
    }
    // a += n
    iterator& operator+=(difference_type n) {
        const difference_type offset = n + (m_cur_ - m_first_);
        if (offset >= 0 && offset < difference_type(node_size())) {
            m_cur_ += n;
        } else {
            difference_type node_offset;
            if (offset > 0) {
                node_offset = offset / difference_type(node_size());
            } else {
                node_offset = -difference_type((-offset - 1) / node_size()) - 1;
            }
            set_node(m_node_ + node_offset);
            m_cur_ = m_first_ +
                     (offset - node_offset * difference_type(node_size()));
        }
        return *this;
    }
    // a + n
    iterator operator+(difference_type n) const {
        iterator tmp = *this;
        return tmp += n;
    }
    // a -= n
    iterator& operator-=(difference_type n) { return *this += -n; }
    // a - n
    iterator  operator-(difference_type n) const {
        iterator tmp = *this;
        return tmp -= n;
    }
    // a - b
    difference_type operator-(const iterator& rhs) const {
        return difference_type(node_size() * (m_node_ - rhs.m_node_ - 1) +
                               (m_cur_ - m_first_) +
                               (rhs.m_last_ - rhs.m_cur_));
    }
    // a < b
    bool operator<(const iterator& rhs) const {
        if (m_node_ == rhs.m_node_) {
            return m_cur_ < rhs.m_cur_;
        }
        return m_node_ < rhs.m_node_;
    }
    // a > b
    bool operator>(const iterator& rhs) const { return rhs.m_node_ < m_node_; }
    // a <= b
    bool operator<=(const iterator& rhs) const {
        return !(rhs.m_node_ < m_node_);
    }
    // a >= b
    bool operator>=(const iterator& rhs) const {
        return !(m_node_ < rhs.m_node_);
    }
    // a[n]
    reference operator[](difference_type n) const { return *(*this + n); }
};
// n + a
template <typename T>
bool operator+(typename deque_iterator<T>::difference_type& n,
               const deque_iterator<T>&                     rhs) {
    return rhs + n;
}

// Ref: https://www.cplusplus.com/reference/deque/deque/
// Ref:
// https://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/a00641_source.html
template <class T, class Alloc = std::allocator<T> >
class deque {
 public:
    // types:
    typedef T                                        value_type;
    typedef Alloc                                    allocator_type;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef deque_iterator<value_type>               iterator;
    typedef deque_iterator<const value_type>         const_iterator;
    typedef ft::reverse_iterator<iterator>           reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;
    typedef deque<value_type>                        dq;
    typedef
        typename allocator_type::template rebind<pointer>::other map_alloc_type;

 private:
    typedef pointer*        m_map_pointer_;
    allocator_type          m_node_allocator_;
    std::allocator<pointer> m_map_allocator_;

 private:
    m_map_pointer_ m_map_;
    size_type      m_map_size_;
    iterator       m_start_;
    iterator       m_finish_;
    enum { INITIAL_MAP_SIZE = 8 };
    static size_t node_size() { return deque_buf_size(sizeof(value_type)); }

 private:
    void M_create_nodes_(m_map_pointer_ start, m_map_pointer_ finish) {
        m_map_pointer_ cur;
        try {
            for (cur = start; cur < finish; ++cur) {
                *cur = m_node_allocator_.allocate(node_size());
            }
        } catch (...) {
            for (m_map_pointer_ i = start; i < cur; ++i) {
                m_node_allocator_.deallocate(*i, node_size());
            }
            throw std::exception();
        }
    }
    void M_initialize_map_(size_t num_elements) {
        const size_t num_nodes = (num_elements / node_size() + 1);
        m_map_size_ =
            ft::max(static_cast<size_t>(INITIAL_MAP_SIZE), num_nodes + 2);
        m_map_ = m_map_allocator_.allocate(m_map_size_);
        m_map_pointer_ start = m_map_ + (m_map_size_ - num_nodes) / 2;
        m_map_pointer_ finish = start + num_nodes;
        try {
            M_create_nodes_(start, finish);
        } catch (...) {
            m_map_allocator_.deallocate(m_map_, m_map_size_);
            m_map_ = m_map_pointer_();
            m_map_size_ = 0;
            throw std::exception();
        }
        m_start_.set_node(start);
        m_finish_.set_node(finish - 1);
        m_start_.m_cur_ = m_start_.m_first_;
        m_finish_.m_cur_ = (m_finish_.m_first_ + num_elements % node_size());
    }

 public:
    // construct/copy/destroy:
    explicit deque(const allocator_type& alloc = allocator_type());
    explicit deque(size_type n, const value_type& val = value_type(),
                   const allocator_type& alloc = allocator_type());
    template <class InputIterator>
    deque(InputIterator first, InputIterator last,
          const allocator_type& alloc = allocator_type());
    deque(const deque& x);
    ~deque();
    deque&                 operator=(const deque& x);

    // iterators:
    iterator               begin();
    const_iterator         begin() const;
    iterator               end();
    const_iterator         end() const;

    reverse_iterator       rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator       rend();
    const_reverse_iterator rend() const;

    // capacity:
    size_type              size() const;
    size_type              max_size() const;
    void                   resize(size_type n, value_type val = value_type());
    bool                   empty() const;

    // element access:
    reference              operator[](size_type n);
    const_reference        operator[](size_type n) const;
    reference              at(size_type n);
    const_reference        at(size_type n) const;
    reference              front();
    const_reference        front() const;
    reference              back();
    const_reference        back() const;

    // modifiers:
    template <class InputIterator>
    void     assign(InputIterator first, InputIterator last);
    void     assign(size_type n, const value_type& val);
    void     push_front(const value_type& val);
    void     push_back(const value_type& val);
    void     pop_front();
    void     pop_back();
    iterator insert(iterator position, const value_type& val);
    void     insert(iterator position, size_type n, const value_type& val);
    template <class InputIterator>
    void     insert(iterator position, InputIterator first, InputIterator last);
    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);
    void     swap(deque& x);
    void     clear();

    // Allocator
    allocator_type get_allocator() const;
};

template <class T, class Alloc>
bool operator==(const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs);
template <class T, class Alloc>
bool operator!=(const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs);
template <class T, class Alloc>
bool operator<(const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs);
template <class T, class Alloc>
bool operator<=(const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs);
template <class T, class Alloc>
bool operator>(const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs);
template <class T, class Alloc>
bool operator>=(const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs);

template <class T, class Alloc>
void swap(deque<T, Alloc>& x, deque<T, Alloc>& y);

// construct/copy/destroy:
template <class T, class Alloc>
deque<T, Alloc>::deque(const typename deque<T, Alloc>::allocator_type& alloc) {}

}  // namespace ft
#endif  // DEQUE_HPP_
