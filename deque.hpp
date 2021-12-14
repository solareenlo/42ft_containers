/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 12:05:12 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/14 19:20:36 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_HPP_
#define DEQUE_HPP_

#include <deque>
#include <exception>
#include <iostream>
#include <limits>
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
    typedef pointer*                   map_pointer;
    typedef deque_iterator<value_type> iterator;

 private:
    pointer     m_cur_;
    pointer     m_first_;
    pointer     m_last_;
    map_pointer m_pos_node_;

 private:
    static size_t node_size() { return deque_buf_size(sizeof(T)); }
    void          set_node(map_pointer new_node) {
        m_pos_node_ = new_node;
        m_first_ = *new_node;
        m_last_ = m_first_ + difference_type(node_size());
    }
    deque_iterator(pointer x, map_pointer y)
        : m_cur_(x), m_first_(*y), m_last_(*y + node_size()), m_pos_node_(y) {}

 public:
    // construct/copy/destroy:
    deque_iterator() : m_cur_(), m_first_(), m_last_(), m_pos_node_() {}
    explicit deque_iterator(const iterator& src)
        : m_cur_(src.m_cur_),
          m_first_(src.m_first_),
          m_last_(src.m_last_),
          m_pos_node_(src.m_pos_node_) {}
    ~deque_iterator() {}
    iterator& operator=(const iterator& rhs) {
        if (this != &rhs) {
            m_cur_ = rhs.m_cur_;
            m_first_ = rhs.m_first_;
            m_last_ = rhs.m_last_;
            m_pos_node_ = rhs.m_pos_node_;
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
            set_node(m_pos_node_ + 1);
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
            set_node(m_pos_node_ - 1);
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
            set_node(m_pos_node_ + node_offset);
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
        return difference_type(
            node_size() * (m_pos_node_ - rhs.m_pos_node_ - 1) +
            (m_cur_ - m_first_) + (rhs.m_last_ - rhs.m_cur_));
    }
    // a < b
    bool operator<(const iterator& rhs) const {
        if (m_pos_node_ == rhs.m_pos_node_) {
            return m_cur_ < rhs.m_cur_;
        }
        return m_pos_node_ < rhs.m_pos_node_;
    }
    // a > b
    bool operator>(const iterator& rhs) const {
        return rhs.m_pos_node_ < m_pos_node_;
    }
    // a <= b
    bool operator<=(const iterator& rhs) const {
        return !(rhs.m_pos_node_ < m_pos_node_);
    }
    // a >= b
    bool operator>=(const iterator& rhs) const {
        return !(m_pos_node_ < rhs.m_pos_node_);
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
    typedef pointer*        map_pointer;
    allocator_type          m_pos_node_allocator_;
    std::allocator<pointer> m_map_allocator_;

 private:
    map_pointer m_map_;
    size_type   m_map_size_;
    iterator    m_start_;
    iterator    m_finish_;

    enum { INITIAL_MAP_SIZE = 8 };
    static size_t node_size() { return deque_buf_size(sizeof(value_type)); }

 private:
    void M_create_nodes_(map_pointer start, map_pointer finish) {
        map_pointer cur;
        try {
            for (cur = start; cur < finish; ++cur) {
                *cur = m_pos_node_allocator_.allocate(node_size());
            }
        } catch (...) {
            for (map_pointer i = start; i < cur; ++i) {
                m_pos_node_allocator_.deallocate(*i, node_size());
            }
            throw;
        }
    }
    void M_initialize_map_(size_t num_elements) {
        const size_t num_nodes = (num_elements / node_size() + 1);
        m_map_size_ =
            ft::max(static_cast<size_t>(INITIAL_MAP_SIZE), num_nodes + 2);
        m_map_ = m_map_allocator_.allocate(m_map_size_);
        map_pointer start = m_map_ + (m_map_size_ - num_nodes) / 2;
        map_pointer finish = start + num_nodes;
        try {
            M_create_nodes_(start, finish);
        } catch (...) {
            m_map_allocator_.deallocate(m_map_, m_map_size_);
            m_map_ = map_pointer();
            m_map_size_ = 0;
            std::cerr << "cannot create ft::deque)" << std::endl;
            throw;
        }
        m_start_.set_node(start);
        m_finish_.set_node(finish - 1);
        m_start_.m_cur_ = m_start_.m_first_;
        m_finish_.m_cur_ = (m_finish_.m_first_ + num_elements % node_size());
    }

 private:
    void M_reallocate_map_(size_type nodes_to_add, bool add_at_front);
    void M_reserve_map_at_back_(size_type nodes_to_add = 1);
    void M_reserve_map_at_front_(size_type nodes_to_add = 1);

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
deque<T, Alloc>::deque(const typename deque<T, Alloc>::allocator_type& alloc)
    : m_map_(), m_map_size_(), m_start_(), m_finish_() {
    M_initialize_map_(0);
}

template <class T, class Alloc>
deque<T, Alloc>::deque(size_type n, const value_type& val,
                       const typename deque<T, Alloc>::allocator_type& alloc)
    : m_map_(), m_map_size_(), m_start_(), m_finish_() {
    M_initialize_map_(0);
}

// capacity:
// size()
template <class T, class Alloc>
typename deque<T, Alloc>::size_type deque<T, Alloc>::size() const {
    return m_finish_ - m_start_;
}

// max_size()
template <class T, class Alloc>
typename deque<T, Alloc>::size_type deque<T, Alloc>::max_size() const {
    return std::numeric_limits<difference_type>::max() / sizeof(value_type);
}

// modifiers:
template <class T, class Alloc>
void deque<T, Alloc>::M_reallocate_map_(size_type nodes_to_add,
                                        bool      add_at_front) {
    const size_type old_num_nodes =
        m_finish_.m_pos_node_ - m_start_.m_pos_node_ + 1;
    const size_type new_num_nodes = old_num_nodes + nodes_to_add;
    map_pointer     new_nstart;
    if (m_map_size_ > 2 * new_num_nodes) {
        new_nstart = m_map_ + (m_map_size_ - new_num_nodes) / 2 +
                     (add_at_front ? nodes_to_add : 0);
        if (new_nstart < m_start_.m_pos_node_)
            std::copy(m_start_.m_pos_node_, m_finish_.m_pos_node_ + 1,
                      new_nstart);
        else
            std::copy_backward(m_start_.m_pos_node_, m_finish_.m_pos_node_ + 1,
                               new_nstart + old_num_nodes);
    } else {
        size_type new_map_size =
            m_map_size_ + std::max(m_map_size_, nodes_to_add) + 2;
        map_pointer new_map = m_map_allocator_.allocate(new_map_size);
        new_nstart = new_map + (new_map_size - new_num_nodes) / 2 +
                     (add_at_front ? nodes_to_add : 0);
        ft::copy(m_start_.m_pos_node_, m_finish_.m_pos_node_ + 1, new_nstart);
        m_map_allocator_.deallocate(m_map_, m_map_size_);
        m_map_ = new_map;
        m_map_size_ = new_map_size;
    }
    m_start_.set_node(new_nstart);
    m_finish_.set_node(new_nstart + old_num_nodes - 1);
}

template <class T, class Alloc>
void deque<T, Alloc>::M_reserve_map_at_back_(size_type nodes_to_add) {
    if (nodes_to_add + 1 > m_map_size_ - (m_finish_.m_pos_node_ - m_map_)) {
        M_reallocate_map_(nodes_to_add, false);
    }
}

template <class T, class Alloc>
void deque<T, Alloc>::M_reserve_map_at_front_(size_type nodes_to_add) {
    if (nodes_to_add > size_type(m_start_.m_pos_node_ - m_map_)) {
        M_reallocate_map_(nodes_to_add, true);
    }
}

// push_front()
template <class T, class Alloc>
void deque<T, Alloc>::push_front(const value_type& val) {
    if (m_start_.m_cur_ != m_start_.m_first_) {
        m_pos_node_allocator_.construct(m_start_.m_cur_ - 1, val);
        --m_start_.m_cur_;
    } else {
        if (size() == max_size()) {
            std::cerr << "cannot create ft::deque larger than max_size()"
                      << std::endl;
            throw;
        }
        M_reserve_map_at_front_();
        *(m_start_.m_pos_node_ - 1) =
            m_pos_node_allocator_.allocate(node_size());
        try {
            m_start_.set_node(m_start_.m_pos_node_ - 1);
            m_start_.m_cur_ = m_start_.m_last_ - 1;
            m_pos_node_allocator_.construct(m_start_.m_cur_, val);
        } catch (...) {
            ++m_start_;
            m_pos_node_allocator_.deallocate(*(m_start_.m_pos_node_ - 1),
                                             node_size());
            throw;
        }
    }
}

template <class T, class Alloc>
void deque<T, Alloc>::push_back(const value_type& val) {
    if (m_finish_.m_cur_ != m_finish_.m_last_ - 1) {
        m_pos_node_allocator_.construct(m_finish_.m_cur_, val);
        ++m_finish_.m_cur_;
    } else {
        if (size() == max_size()) {
            std::cerr << "cannot create ft::deque larger than max_size()"
                      << std::endl;
            throw;
        }
        M_reserve_map_at_back_();
        *(m_finish_.m_pos_node_ + 1) =
            m_pos_node_allocator_.allocate(node_size());
        try {
            m_pos_node_allocator_.construct(m_finish_.m_cur_, val);
            m_finish_.set_node(m_finish_.m_pos_node_ + 1);
            m_finish_.m_cur_ = m_finish_.m_first_;
        } catch (...) {
            m_pos_node_allocator_.deallocate(*(m_finish_.m_pos_node_ + 1),
                                             node_size());
            throw;
        }
    }
}

// insert()
template <class T, class Alloc>
typename deque<T, Alloc>::iterator deque<T, Alloc>::insert(
    iterator position, const value_type& val) {
    if (position.m_cur_ == m_start_.m_cur_) {
        push_front(val);
        return m_start_;
    } else if (position.m_cur_ == m_finish_.m_cur_) {
        push_back(val);
        iterator tmp = m_finish_;
        --tmp;
        return tmp;
    }
    value_type      copy = val;
    difference_type index = position - m_start_;
    if (static_cast<size_type>(index) < size() / 2) {
        push_front(front());
        iterator front1 = m_start_;
        ++front1;
        iterator front2 = front1;
        ++front2;
        position = m_start_ + index;
        iterator pos1 = position;
        ++pos1;
        ft::copy(front2, pos1, front1);
    } else {
        push_back(back());
        iterator back1 = m_finish_;
        --back1;
        iterator back2 = back1;
        --back2;
        position = m_start_ + index;
        ft::copy_backward(position, back2, back1);
    }
    *position = copy;
    return position;
}

}  // namespace ft
#endif  // DEQUE_HPP_
