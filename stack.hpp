/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 12:01:11 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/18 02:50:54 by tayamamo         ###   ########.fr       */
/* ************************************************************************** */

#ifndef STACK_HPP_
#define STACK_HPP_

#include "deque.hpp"

namespace ft {

template <class T, class Container = ft::deque<T> >
class stack {
 public:
    typedef Container                           container_type;
    typedef typename container_type::value_type value_type;
    typedef typename container_type::size_type  size_type;

 protected:
    container_type m_ctnr_;

 public:
    container_type get_container() const { return m_ctnr_; }

 public:
    explicit stack(const container_type& ctnr = container_type())
        : m_ctnr_(ctnr) {}

    bool              empty() const { return m_ctnr_.empty(); }
    size_type         size() const { return m_ctnr_.size(); }
    value_type&       top() { return m_ctnr_.back(); }
    const value_type& top() const { return m_ctnr_.back(); }
    void              push(const value_type& val) { m_ctnr_.push_back(val); }
    void              pop() { m_ctnr_.pop_back(); }
};

template <class T, class Container>
bool operator==(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
    return lhs.get_container() == rhs.get_container();
}

template <class T, class Container>
bool operator!=(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
    return !(lhs.get_container() == rhs.get_container());
}

template <class T, class Container>
bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return lhs.get_container() < rhs.get_container();
}

template <class T, class Container>
bool operator<=(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
    return !(rhs.get_container() < lhs.get_container());
}

template <class T, class Container>
bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return rhs.get_container() < lhs.get_container();
}

template <class T, class Container>
bool operator>=(const stack<T, Container>& lhs,
                const stack<T, Container>& rhs) {
    return !(lhs.get_container() < rhs.get_container());
}

}  // namespace ft

#endif  // STACK_HPP_
