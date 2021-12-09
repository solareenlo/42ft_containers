/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 08:24:04 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/09 12:38:24 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#ifndef TREE_HPP_
#define TREE_HPP_

#include <iostream>
#include <memory>

#include "iterator.hpp"
#include "utility.hpp"

namespace ft {

enum Color { BLACK, RED };

template <typename Key>
struct rbtNode {
    rbtNode*   m_parent_;
    rbtNode*   m_left_;
    rbtNode*   m_right_;
    enum Color m_color_;
    Key        m_key_;

    rbtNode()
        : m_parent_(NULL), m_left_(NULL), m_right_(NULL), m_color_(BLACK) {}
    rbtNode(rbtNode const& src)
        : m_parent_(src.m_parent_),
          m_left_(src.m_left_),
          m_right_(src.m_right_),
          m_color_(src.m_color_),
          m_key_(src.m_key_) {}
    ~rbtNode() {}
    rbtNode& operator=(rbtNode const& rhs) {
        if (this != &rhs) {
            m_parent_ = rhs.palent;
            m_right_ = rhs.m_right_;
            m_left_ = rhs.m_left_;
            m_color_ = rhs.m_color_;
            m_key_ = rhs.m_key_;
        }
        return *this;
    }
};

template <class Key, class T, class Compare, class Alloc>
class tree;

template <class ValueType>
class tree_iterator {
 public:
    typedef ft::bidirectional_iterator_tag iterator_category;
    typedef ValueType                      value_type;
    typedef std::ptrdiff_t                 difference_type;
    typedef rbtNode<value_type>            node_type;
    typedef value_type&                    reference;
    typedef value_type*                    pointer;
    typedef tree_iterator<value_type>      iterator;

 private:
    node_type* m_node_;

 public:
    tree_iterator() : m_node_(NULL) {}
    explicit tree_iterator(node_type* ptr) : m_node_(ptr) {}
    ~tree_iterator() {}
    tree_iterator& operator=(const tree_iterator& rhs) {
        if (this != &rhs) {
            m_node_ = rhs.m_node_;
        }
        return *this;
    }

 public:
    bool      operator==(iterator rhs) const { return m_node_ == rhs.m_node_; }
    bool      operator!=(iterator rhs) const { return m_node_ != rhs.m_node_; }
    reference operator*() const { return m_node_->m_key_; }
    pointer   operator->() const { return &(m_node_->m_key_); }
    iterator& operator++() {
        m_node_ = m_node_->next();
        return *this;
    }
    iterator& operator++(int) {
        iterator old = *this;
        m_node_ = m_node_->next();
        return old;
    }
    iterator& operator--() {
        m_node_ = m_node_->prev();
        return *this;
    }
    iterator& operator--(int) {
        iterator old = *this;
        m_node_ = m_node_->prev();
        return old;
    }
};

template <class ValueType>
class const_tree_iterator {
 public:
    typedef ft::bidirectional_iterator_tag iterator_category;
    typedef ValueType                      value_type;
    typedef std::ptrdiff_t                 difference_type;
    typedef rbtNode<value_type>            node_type;
    typedef value_type&                    reference;
    typedef value_type*                    pointer;
    typedef tree_iterator<value_type>      iterator;

 private:
    node_type* m_node_;

 public:
    const_tree_iterator() : m_node_(NULL) {}
    explicit const_tree_iterator(const iterator& src) : m_node_(src.m_node_) {}
    explicit const_tree_iterator(pointer ptr) : m_node_(ptr) {}
    ~const_tree_iterator() {}
    const_tree_iterator& operator=(const const_tree_iterator& rhs) {
        if (this != &rhs) {
            this->m_node_ = rhs.m_node_;
        }
        return *this;
    }

 public:
    bool      operator==(iterator rhs) const { return m_node_ == rhs.m_node_; }
    bool      operator!=(iterator rhs) const { return m_node_ != rhs.m_node_; }
    reference operator*() const { return m_node_->m_key_; }
    pointer   operator->() const { return &(m_node_->m_key_); }
    iterator& operator++() {
        m_node_ = m_node_->next();
        return *this;
    }
    iterator& operator++(int) {
        iterator old = *this;
        m_node_ = m_node_->next();
        return old;
    }
    iterator& operator--() {
        m_node_ = m_node_->prev();
        return *this;
    }
    iterator& operator--(int) {
        iterator old = *this;
        m_node_ = m_node_->prev();
        return old;
    }
};

template <class Key, class T, class Compare, class Alloc>
class tree {
 public:
    typedef Key                                      key_type;
    typedef T                                        mapped_type;
    typedef ft::pair<key_type, mapped_type>          value_type;
    typedef Compare                                  key_compare;
    typedef Alloc                                    allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef tree_iterator<value_type>                iterator;
    typedef const_tree_iterator<value_type>          const_iterator;
    typedef ft::reverse_iterator<iterator>           reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;
    typedef rbtNode<value_type>                      node_type;
    typedef
        typename Alloc::template rebind<node_type>::other node_allocator_type;

 private:
    key_compare         m_key_compare_;
    node_allocator_type m_allocator_;
    node_type*          m_root_;
    node_type*          NIL;
    node_type*          m_begin_;
    node_type*          m_end_;

 private:
    tree();
    tree(const tree& src);
    node_type* getRoot() const { return m_root_; }
    void       setRoot(node_type* node) { m_root_ = node; }
    node_type* getParent(node_type* node) const;
    node_type* getGrandParent(node_type* node) const;
    enum Color getColor(node_type* node) const;
    void       setColor(node_type* node, enum Color color);
    void       rotateLeft(node_type* node);
    void       rotateRight(node_type* node);
    void       deleteAllNode();
    void       deleteAllNodeHelper(node_type* node);
    node_type* createNewNode(value_type key);
    node_type* insertKey(value_type key);
    void       balanceAfterInsert(node_type* newNode);
    node_type* getMinKeyNode(node_type* node);
    node_type* getMaxKeyNode(node_type* node);

 public:
    // Constructor
    explicit tree(const key_compare&    comp = key_compare(),
                  const allocator_type& alloc = allocator_type())
        : m_key_compare_(comp), m_allocator_(alloc) {
        NIL = new node_type;
        NIL->m_parent_ = NULL;
        NIL->m_color_ = BLACK;
        NIL->m_left_ = NULL;
        NIL->m_right_ = NULL;
        m_root_ = NIL;
        m_begin_ = m_root_;
        m_end_ = m_root_;
    }
    // Destructor
    ~tree() {
        deleteAllNode();
        delete NIL;
    }
    // operator=
    tree& operator=(const tree& x) {
        if (this != &x) {
            clear();
            insert(x.begin(), x.end());
        }
        return *this;
    }

 public:
    // Iterators
    iterator             begin() { return iterator(m_begin_); }
    iterator             end() { return iterator(m_end_); }
    // Capacity
    // Element access
    // Modifiers
    pair<iterator, bool> insert(const value_type& val) {
        node_type* newNode = insertKey(val);
        m_begin_ = getMinKeyNode(getRoot());
        m_end_ = getMaxKeyNode(getRoot());
        return ft::make_pair(iterator(newNode), true);
    }
    iterator insert(iterator position, const value_type& val);
    template <class InputIterator>
    void insert(InputIterator first, InputIterator last);
    // Observers
    // Operations
    // Allocator
    void clear() { deleteAllNode(); }
};

template <class Key, class T, class Compare, class Alloc>
rbtNode<ft::pair<Key, T> >* tree<Key, T, Compare, Alloc>::getParent(
    node_type* node) const {
    if (node == NULL) {
        return NULL;
    }
    return node->m_parent_;
}

template <class Key, class T, class Compare, class Alloc>
rbtNode<ft::pair<Key, T> >* tree<Key, T, Compare, Alloc>::getGrandParent(
    node_type* node) const {
    if (node == NULL || node->m_parent_ == NULL) {
        return NULL;
    }
    return node->m_parent_->m_parent_;
}

template <class Key, class T, class Compare, class Alloc>
enum Color tree<Key, T, Compare, Alloc>::getColor(node_type* node) const {
    if (node == NULL) {
        return BLACK;
    }
    return node->m_color_;
}

template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::setColor(node_type* node, enum Color color) {
    if (node == NULL) {
        return;
    }
    node->m_color_ = color;
}

template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::rotateLeft(node_type* node) {
    if (node == NULL) {
        return;
    }
    node_type* right = node->m_right_;
    node->m_right_ = right->m_left_;
    if (node->m_right_ != NIL) {
        node->m_right_->m_parent_ = node;
    }
    right->m_parent_ = node->m_parent_;
    if (node->m_parent_ == NULL) {
        setRoot(right);
    } else if (node == node->m_parent_->m_left_) {
        node->m_parent_->m_left_ = right;
    } else {
        node->m_parent_->m_right_ = right;
    }
    right->m_left_ = node;
    node->m_parent_ = right;
}

template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::rotateRight(node_type* node) {
    if (node == NULL) {
        return;
    }
    node_type* left = node->m_left_;
    node->m_left_ = left->m_right_;
    if (node->m_left_ != NIL) {
        node->m_left_->m_parent_ = node;
    }
    left->m_parent_ = node->m_parent_;
    if (node->m_parent_ == NULL) {
        setRoot(left);
    } else if (node == node->m_parent_->m_right_) {
        node->m_parent_->m_right_ = left;
    } else {
        node->m_parent_->m_left_ = left;
    }
    left->m_right_ = node;
    node->m_parent_ = left;
}

template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::deleteAllNode() {
    if (getRoot() == NIL) {
        return;
    }
    deleteAllNodeHelper(getRoot());
    setRoot(NIL);
}

template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::deleteAllNodeHelper(node_type* node) {
    if (node == NIL) {
        return;
    }
    deleteAllNodeHelper(node->m_left_);
    deleteAllNodeHelper(node->m_right_);
    m_allocator_.destroy(node);
    m_allocator_.deallocate(node, 1);
}

template <class Key, class T, class Compare, class Alloc>
rbtNode<ft::pair<Key, T> >* tree<Key, T, Compare, Alloc>::createNewNode(
    value_type key) {
    node_type* newNode = m_allocator_.allocate(1);
    newNode->m_parent_ = NULL;
    newNode->m_left_ = NIL;
    newNode->m_right_ = NIL;
    newNode->m_color_ = RED;
    newNode->m_key_ = key;
    return newNode;
}

template <class Key, class T, class Compare, class Alloc>
rbtNode<ft::pair<Key, T> >* tree<Key, T, Compare, Alloc>::insertKey(
    value_type key) {
    node_type* newNode = createNewNode(key);
    node_type* leaf = NULL;
    node_type* root = getRoot();
    while (root != NIL) {
        leaf = root;
        if (newNode->m_key_.first < root->m_key_.first) {
            root = root->m_left_;
        } else {
            root = root->m_right_;
        }
    }
    newNode->m_parent_ = leaf;
    if (leaf == NULL) {
        setRoot(newNode);
    } else if (newNode->m_key_.first < leaf->m_key_.first) {
        leaf->m_left_ = newNode;
    } else {
        leaf->m_right_ = newNode;
    }
    if (getParent(newNode) == NULL) {
        setColor(newNode, BLACK);
        return newNode;
    }
    if (getGrandParent(newNode) == NULL) {
        return newNode;
    }
    balanceAfterInsert(newNode);
    return newNode;
}

template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::balanceAfterInsert(node_type* newNode) {
    node_type* parent = NULL;
    node_type* aunt = NULL;
    node_type* grandParent = NULL;
    while (newNode != getRoot() && getColor(getParent(newNode)) == RED) {
        parent = getParent(newNode);
        grandParent = getGrandParent(newNode);
        if (parent == grandParent->m_left_) {
            aunt = grandParent->m_right_;
            if (aunt->m_color_ == RED) {
                aunt->m_color_ = BLACK;
                newNode->m_parent_->m_color_ = BLACK;
                newNode->m_parent_->m_parent_->m_color_ = RED;
                newNode = newNode->m_parent_->m_parent_;
            } else {
                if (newNode == newNode->m_parent_->m_right_) {
                    newNode = newNode->m_parent_;
                    rotateLeft(newNode);
                }
                newNode->m_parent_->m_color_ = BLACK;
                newNode->m_parent_->m_parent_->m_color_ = RED;
                rotateRight(newNode->m_parent_->m_parent_);
            }
        } else if (parent == grandParent->m_right_) {
            aunt = newNode->m_parent_->m_parent_->m_left_;
            if (aunt->m_color_ == RED) {
                aunt->m_color_ = BLACK;
                newNode->m_parent_->m_color_ = BLACK;
                newNode->m_parent_->m_parent_->m_color_ = RED;
                newNode = newNode->m_parent_->m_parent_;
            } else {
                if (newNode == newNode->m_parent_->m_left_) {
                    newNode = newNode->m_parent_;
                    rotateRight(newNode);
                }
                newNode->m_parent_->m_color_ = BLACK;
                newNode->m_parent_->m_parent_->m_color_ = RED;
                rotateLeft(newNode->m_parent_->m_parent_);
            }
        }
    }
    setColor(getRoot(), BLACK);
}

template <class Key, class T, class Compare, class Alloc>
rbtNode<ft::pair<Key, T> >* tree<Key, T, Compare, Alloc>::getMinKeyNode(
    node_type* node) {
    while (node->m_left_ != NIL) {
        node = node->m_left_;
    }
    return node;
}

template <class Key, class T, class Compare, class Alloc>
rbtNode<ft::pair<Key, T> >* tree<Key, T, Compare, Alloc>::getMaxKeyNode(
    node_type* node) {
    while (node->m_right_ != NIL) {
        node = node->m_right_;
    }
    return node;
}

}  // namespace ft

#endif  // TREE_HPP_
