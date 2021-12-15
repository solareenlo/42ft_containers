/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 12:05:12 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/15 22:46:06 by tayamamo         ###   ########.fr       */
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
#include "uninitialized.hpp"

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
            set_node(m_node_ + 1);
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
    typedef pointer*                                 map_pointer;
    typedef
        typename allocator_type::template rebind<pointer>::other map_alloc_type;

 private:
    allocator_type          m_node_allocator_;
    std::allocator<pointer> m_map_allocator_;
    map_pointer             m_map_;
    size_type               m_map_size_;
    iterator                m_start_;
    iterator                m_finish_;

    enum { INITIAL_MAP_SIZE = 8 };
    static size_t node_size() { return deque_buf_size(sizeof(value_type)); }

 private:
    void M_create_nodes_(map_pointer start, map_pointer finish) {
        map_pointer cur;
        try {
            for (cur = start; cur < finish; ++cur) {
                *cur = M_allocate_node_();
            }
        } catch (...) {
            for (map_pointer i = start; i < cur; ++i) {
                M_deallocate_node_(*i);
            }
            throw;
        }
    }
    void M_initialize_map_(size_t num_elements) {
        const size_t num_nodes = (num_elements / node_size() + 1);
        m_map_size_ =
            ft::max(static_cast<size_t>(INITIAL_MAP_SIZE), num_nodes + 2);
        m_map_ = M_allocate_map_(m_map_size_);
        map_pointer start = m_map_ + (m_map_size_ - num_nodes) / 2;
        map_pointer finish = start + num_nodes;
        try {
            M_create_nodes_(start, finish);
        } catch (...) {
            M_deallocate_map_(m_map_, m_map_size_);
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
    map_pointer M_allocate_map_(size_type n);
    void        M_deallocate_map_(map_pointer ptr, size_type n);
    pointer     M_allocate_node_();
    void        M_deallocate_node_(pointer ptr);
    void        M_destroy_nodes_(map_pointer start, map_pointer finish);
    void        M_construct_node_(pointer ptr, const value_type& val);
    void        M_reallocate_map_(size_type nodes_to_add, bool add_at_front);
    void        M_reserve_map_at_back_(size_type nodes_to_add = 1);
    void        M_reserve_map_at_front_(size_type nodes_to_add = 1);
    void        M_new_elements_at_front_(size_type new_elems);
    void        M_new_elements_at_back_(size_type new_elems);
    iterator    M_reserve_elements_at_front_(size_type n);
    iterator    M_reserve_elements_at_back_(size_type n);
    void M_insert_(iterator position, size_type n, const value_type& val);
    template <typename ForwardIterator>
    void M_insert_(iterator position, ForwardIterator first,
                   ForwardIterator last, size_type n);
    void M_fill_insert_(iterator position, size_type n, const value_type& val);

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

// M_*
template <typename T, typename Alloc>
typename deque<T, Alloc>::map_pointer deque<T, Alloc>::M_allocate_map_(
    size_type n) {
    return m_map_allocator_.allocate(n);
}

template <typename T, typename Alloc>
void deque<T, Alloc>::M_deallocate_map_(map_pointer ptr, size_type n) {
    m_map_allocator_.deallocate(ptr, n);
}

template <typename T, typename Alloc>
typename deque<T, Alloc>::pointer deque<T, Alloc>::M_allocate_node_() {
    return m_node_allocator_.allocate(node_size());
}

template <typename T, typename Alloc>
void deque<T, Alloc>::M_deallocate_node_(pointer ptr) {
    m_node_allocator_.deallocate(ptr, node_size());
}

template <typename T, typename Alloc>
void deque<T, Alloc>::M_destroy_nodes_(map_pointer start, map_pointer finish) {
    for (map_pointer i = start; i < finish; ++i) {
        M_deallocate_node_(*i);
    }
}

template <typename T, typename Alloc>
void deque<T, Alloc>::M_construct_node_(pointer ptr, const value_type& val) {
    m_node_allocator_.construct(ptr, val);
}

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
    const size_type old_num_nodes = m_finish_.m_node_ - m_start_.m_node_ + 1;
    const size_type new_num_nodes = old_num_nodes + nodes_to_add;
    map_pointer     new_start;
    if (m_map_size_ > 2 * new_num_nodes) {
        new_start = m_map_ + (m_map_size_ - new_num_nodes) / 2 +
                    (add_at_front ? nodes_to_add : 0);
        if (new_start < m_start_.m_node_)
            ft::copy(m_start_.m_node_, m_finish_.m_node_ + 1, new_start);
        else
            ft::copy_backward(m_start_.m_node_, m_finish_.m_node_ + 1,
                              new_start + old_num_nodes);
    } else {
        size_type new_map_size =
            m_map_size_ + std::max(m_map_size_, nodes_to_add) + 2;
        map_pointer new_map = M_allocate_map_(new_map_size);
        new_start = new_map + (new_map_size - new_num_nodes) / 2 +
                    (add_at_front ? nodes_to_add : 0);
        ft::copy(m_start_.m_node_, m_finish_.m_node_ + 1, new_start);
        M_deallocate_map_(m_map_, m_map_size_);
        m_map_ = new_map;
        m_map_size_ = new_map_size;
    }
    m_start_.set_node(new_start);
    m_finish_.set_node(new_start + old_num_nodes - 1);
}

template <class T, class Alloc>
void deque<T, Alloc>::M_reserve_map_at_back_(size_type nodes_to_add) {
    if (nodes_to_add + 1 > m_map_size_ - (m_finish_.m_node_ - m_map_)) {
        M_reallocate_map_(nodes_to_add, false);
    }
}

template <class T, class Alloc>
void deque<T, Alloc>::M_reserve_map_at_front_(size_type nodes_to_add) {
    if (nodes_to_add > size_type(m_start_.m_node_ - m_map_)) {
        M_reallocate_map_(nodes_to_add, true);
    }
}

// push_front()
template <class T, class Alloc>
void deque<T, Alloc>::push_front(const value_type& val) {
    if (m_start_.m_cur_ != m_start_.m_first_) {
        M_construct_node_(m_start_.m_cur_ - 1, val);
        --m_start_.m_cur_;
    } else {
        if (size() == max_size()) {
            std::cerr << "cannot create ft::deque larger than max_size()"
                      << std::endl;
            throw;
        }
        M_reserve_map_at_front_();
        *(m_start_.m_node_ - 1) = M_allocate_node_();
        try {
            m_start_.set_node(m_start_.m_node_ - 1);
            m_start_.m_cur_ = m_start_.m_last_ - 1;
            M_construct_node_(m_start_.m_cur_, val);
        } catch (...) {
            ++m_start_;
            M_deallocate_node_(*(m_start_.m_node_ - 1));
            throw;
        }
    }
}

// push_back()
template <class T, class Alloc>
void deque<T, Alloc>::push_back(const value_type& val) {
    if (m_finish_.m_cur_ != m_finish_.m_last_ - 1) {
        M_construct_node_(m_finish_.m_cur_, val);
        ++m_finish_.m_cur_;
    } else {
        if (size() == max_size()) {
            std::cerr << "cannot create ft::deque larger than max_size()"
                      << std::endl;
            throw;
        }
        M_reserve_map_at_back_();
        *(m_finish_.m_node_ + 1) = M_allocate_node_();
        try {
            M_construct_node_(m_finish_.m_cur_, val);
            m_finish_.set_node(m_finish_.m_node_ + 1);
            m_finish_.m_cur_ = m_finish_.m_first_;
        } catch (...) {
            M_deallocate_node_(*(m_finish_.m_node_ - 1));
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

template <typename T, typename Alloc>
void deque<T, Alloc>::M_new_elements_at_front_(size_type new_elems) {
    if (max_size() - size() < new_elems) {
        std::cerr << "ft::deque::M_new_elements_at_front_" << std::endl;
        throw;
    }
    const size_type new_nodes = ((new_elems + node_size() - 1) / node_size());
    M_reserve_map_at_front_(new_nodes);
    size_type i;
    try {
        for (i = 1; i <= new_nodes; ++i) {
            *(m_start_.m_node_ - i) = M_allocate_node_();
        }
    } catch (...) {
        for (size_type j = 1; j < i; ++j) {
            M_deallocate_node_(*(m_start_.m_node_ - j));
        }
        throw;
    }
}

template <typename T, typename Alloc>
void deque<T, Alloc>::M_new_elements_at_back_(size_type new_elems) {
    if (max_size() - size() < new_elems) {
        std::cerr << "ft::deque::M_new_elements_at_back_" << std::endl;
        throw;
    }
    const size_type new_nodes = ((new_elems + node_size() - 1) / node_size());
    M_reserve_map_at_back_(new_nodes);
    size_type i;
    try {
        for (i = 1; i <= new_nodes; ++i) {
            *(m_finish_.m_node_ + i) = M_allocate_node_();
        }
    } catch (...) {
        for (size_type j = 1; j < i; ++j) {
            M_deallocate_node_(*(m_finish_.m_node_ + j));
        }
        throw;
    }
}

template <typename T, typename Alloc>
typename deque<T, Alloc>::iterator
deque<T, Alloc>::M_reserve_elements_at_front_(size_type n) {
    const size_type vacancies = m_start_.m_cur_ - m_start_.m_first_;
    if (n > vacancies) {
        M_new_elements_at_front_(n - vacancies);
    }
    return m_start_ - static_cast<difference_type>(n);
}

template <typename T, typename Alloc>
typename deque<T, Alloc>::iterator deque<T, Alloc>::M_reserve_elements_at_back_(
    size_type n) {
    const size_type vacancies = (m_finish_.m_last_ - m_finish_.m_cur_) - 1;
    if (n > vacancies) {
        M_new_elements_at_back_(n - vacancies);
    }
    return m_finish_ + static_cast<difference_type>(n);
}

template <typename T, typename Alloc>
void deque<T, Alloc>::M_insert_(iterator position, size_type n,
                                const value_type& val) {
    const difference_type elems_before = position - m_start_;
    const size_type       length = size();
    value_type            val_copy = val;
    if (elems_before < static_cast<difference_type>(length / 2)) {
        iterator new_start = M_reserve_elements_at_front_(n);
        iterator old_start = m_start_;
        position = m_start_ + elems_before;
        try {
            if (elems_before >= static_cast<difference_type>(n)) {
                iterator start_n = m_start_ + static_cast<difference_type>(n);
                ft::uninitialized_copy_a(m_start_, start_n, new_start,
                                         m_node_allocator_);
                m_start_ = new_start;
                ft::copy(start_n, position, old_start);
                ft::fill(position - static_cast<difference_type>(n), position,
                         val_copy);
            } else {
                ft::uninitialized_move_fill(m_start_, position, new_start,
                                            m_start_, val_copy,
                                            m_node_allocator_);
                m_start_ = new_start;
                ft::fill(old_start, position, val_copy);
            }
        } catch (...) {
            M_destroy_nodes_(new_start.m_node_, m_start_.m_node_);
            throw;
        }
    } else {
        iterator              new_finish = M_reserve_elements_at_back_(n);
        iterator              old_finish = m_finish_;
        const difference_type elems_after =
            static_cast<difference_type>(length) - elems_before;
        position = m_finish_ - elems_after;
        try {
            if (elems_after > static_cast<difference_type>(n)) {
                iterator finish_n = m_finish_ - static_cast<difference_type>(n);
                ft::uninitialized_copy_a(finish_n, m_finish_, m_finish_,
                                         m_node_allocator_);
                m_finish_ = new_finish;
                ft::copy(position, finish_n, old_finish);
                ft::fill(position, position + static_cast<difference_type>(n),
                         val_copy);
            } else {
                ft::uninitialized_fill_move(
                    m_finish_, position + static_cast<difference_type>(n),
                    val_copy, position, m_finish_, m_node_allocator_);
                m_finish_ = new_finish;
                ft::fill(position, old_finish, val_copy);
            }
        } catch (...) {
            M_destroy_nodes_(m_finish_.m_node_ + 1, new_finish.m_node_ + 1);
            throw;
        }
    }
}

template <typename T, typename Alloc>
void deque<T, Alloc>::M_fill_insert_(iterator position, size_type n,
                                     const value_type& val) {
    if (position.m_cur_ == m_start_.m_cur_) {
        iterator new_start = M_reserve_elements_at_front_(n);
        try {
            ft::uninitialized_fill_a(new_start, m_start_, val,
                                     m_node_allocator_);
            m_start_ = new_start;
        } catch (...) {
            M_destroy_nodes_(new_start.m_node_, m_start_.m_node_);
            throw;
        }
    } else if (position.m_cur_ == m_finish_.m_cur_) {
        iterator new_finish = M_reserve_elements_at_back_(n);
        try {
            ft::uninitialized_fill_a(m_finish_, new_finish, val,
                                     m_node_allocator_);
            m_finish_ = new_finish;
        } catch (...) {
            M_destroy_nodes_(m_finish_.m_node_ + 1, new_finish.m_node_ + 1);
            throw;
        }
    } else {
        M_insert_(position, n, val);
    }
}

template <class T, class Alloc>
void deque<T, Alloc>::insert(iterator position, size_type n,
                             const value_type& val) {
    M_fill_insert_(position, n, val);
}

template <typename T, typename Alloc>
template <typename ForwardIterator>
void deque<T, Alloc>::M_insert_(iterator position, ForwardIterator first,
                                ForwardIterator last, size_type n) {
    const difference_type elems_before = position - m_start_;
    const size_type       length = size();
    if (static_cast<size_type>(elems_before) < length / 2) {
        iterator new_start = M_reserve_elements_at_front_(n);
        iterator old_start = m_start_;
        position = m_start_ + elems_before;
        try {
            if (elems_before >= static_cast<difference_type>(n)) {
                iterator start_n = (m_start_ + static_cast<difference_type>(n));
                ft::uninitialized_move_a(m_start_, start_n, new_start,
                                         m_node_allocator_);
                m_start_ = new_start;
                ft::copy(start_n, position, old_start);
                ft::copy(first, last,
                         position - static_cast<difference_type>(n));
            } else {
                ForwardIterator mid = first;
                ft::advance(mid,
                            static_cast<difference_type>(n) - elems_before);
                ft::uninitialized_move_copy(m_start_, position, first, mid,
                                            new_start, m_node_allocator_);
                m_start_ = new_start;
                ft::copy(mid, last, old_start);
            }
        } catch (...) {
            M_destroy_nodes_(new_start.m_node_, m_start_.m_node_);
            throw;
        }
    } else {
        iterator              new_finish = _M_reserve_elements_at_back(n);
        iterator              old_finish = m_finish_;
        const difference_type elems_after =
            static_cast<difference_type>(length) - elems_before;
        position = m_finish_ - elems_after;
        try {
            if (elems_after > static_cast<difference_type>(n)) {
                iterator finish_n =
                    (m_finish_ - static_cast<difference_type>(n));
                ft::uninitialized_move_a(finish_n, m_finish_, m_finish_,
                                         m_node_allocator_);
                m_finish_ = new_finish;
                ft::copy(position, finish_n, old_finish);
                ft::copy(first, last, position);
            } else {
                ForwardIterator mid = first;
                ft::advance(mid, elems_after);
                ft::uninitialized_copy_move(mid, last, position, m_finish_,
                                            m_finish_, m_node_allocator_);
                m_finish_ = new_finish;
                ft::copy(first, mid, position);
            }
        } catch (...) {
            M_destroy_nodes_(m_finish_.m_node_ + 1, new_finish.m_node_ + 1);
            throw;
        }
    }
}

template <class T, class Alloc>
template <class InputIterator>
void deque<T, Alloc>::insert(iterator position, InputIterator first,
                             InputIterator last) {
    const size_type n = ft::distance(first, last);
    if (position.m_cur_ == m_start_.m_cur_) {
        iterator new_start = M_reserve_elements_at_front_(n);
        try {
            ft::uninitialized_copy_a(first, last, new_start, m_node_allocator_);
            m_start_ = new_start;
        } catch (...) {
            M_destroy_nodes_(new_start.m_node_, m_start_.m_node_);
            throw;
        }
    } else if (position.m_cur_ == m_finish_.m_cur_) {
        iterator new_finish = M_reserve_elements_at_back_(n);
        try {
            ft::uninitialized_copy_a(first, last, m_finish_, m_node_allocator_);
            m_finish_ = new_finish;
        } catch (...) {
            M_destroy_nodes_(m_finish_.m_node_ + 1, new_finish.m_node_ + 1);
            throw;
        }
    } else {
        M_insert_(position, first, last, n);
    }
}

}  // namespace ft
#endif  // DEQUE_HPP_
