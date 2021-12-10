/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 08:24:04 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/10 09:56:39 by tayamamo         ###   ########.fr       */
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
    typedef Key                 value_type;
    typedef rbtNode<value_type> node_type;

    node_type*                  m_parent_;
    node_type*                  m_left_child_;
    node_type*                  m_right_child_;
    node_type*                  NIL;
    enum Color                  m_color_;
    Key                         m_key_;

    rbtNode()
        : m_parent_(NULL),
          m_left_child_(NULL),
          m_right_child_(NULL),
          NIL(NULL),
          m_color_(BLACK) {}
    rbtNode(rbtNode const& src)
        : m_parent_(src.m_parent_),
          m_left_child_(src.m_left_child_),
          m_right_child_(src.m_right_child_),
          NIL(src.NIL),
          m_color_(src.m_color_),
          m_key_(src.m_key_) {}
    ~rbtNode() {}
    rbtNode& operator=(rbtNode const& rhs) {
        if (this != &rhs) {
            m_parent_ = rhs.palent;
            m_right_child_ = rhs.m_right_child_;
            m_left_child_ = rhs.m_left_child_;
            NIL = rhs.NIL;
            m_color_ = rhs.m_color_;
            m_key_ = rhs.m_key_;
        }
        return *this;
    }

    node_type* getMinNode() {
        node_type* node = this;
        if (node == NULL) {
            return node;
        }
        while (node->m_left_child_ != NIL) {
            node = node->m_left_child_;
        }
        return node;
    }
    node_type* getMaxNode() {
        node_type* node = this;
        if (node == NULL) {
            return node;
        }
        while (node->m_right_child_ != NIL) {
            node = node->m_right_child_;
        }
        return node;
    }
    node_type* getNextNode() {
        node_type* node = this;
        if (node == NULL || node == NIL) {
            return NIL;
        }
        if (node->isLeftChild() == true) {
            if (node->m_right_child_ != NIL) {
                return node->m_right_child_->getMinNode();
            } else {
                return node->m_parent_;
            }
        }
        if (node->m_right_child_ != NIL) {
            return node->m_right_child_->getMinNode();
        } else {
            while (node->m_parent_->isLeftChild() == false) {
                node = node->m_parent_;
            }
            node = node->m_parent_;
            if (node == NULL) {
                return this->m_right_child_;
            }
            return node->m_parent_->m_right_child_->getMinNode();
        }
    }
    bool isLeftChild() {
        node_type* node = this;
        if (node == NULL || node == NIL) {
            return false;
        }
        if (node->m_parent_ == NULL || node->m_parent_ == NIL) {
            return false;
        }
        if (node == node->m_parent_->m_left_child_) {
            return true;
        }
        return false;
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
        m_node_ = m_node_->getNextNode();
        return *this;
    }
    iterator operator++(int) {
        iterator old = *this;
        ++*this;
        return old;
    }
    iterator& operator--() {
        m_node_ = m_node_->prev();
        return *this;
    }
    iterator operator--(int) {
        iterator old = *this;
        --*this;
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
    node_allocator_type m_node_allocator_;
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
    void       setBeginNode();
    void       setEndNode();
    void       unSetEndNode();
    node_type* findNode(value_type key);

 public:
    // Constructor
    explicit tree(const key_compare&    comp = key_compare(),
                  const allocator_type& alloc = allocator_type())
        : m_key_compare_(comp), m_node_allocator_(alloc) {
        NIL = m_node_allocator_.allocate(1);
        NIL->m_parent_ = NULL;
        NIL->m_left_child_ = NULL;
        NIL->m_right_child_ = NULL;
        NIL->NIL = NIL;
        NIL->m_color_ = BLACK;

        m_root_ = NIL;
        m_begin_ = m_root_;

        m_end_ = m_node_allocator_.allocate(1);
        m_end_->m_parent_ = m_root_;
        m_end_->m_left_child_ = NIL;
        m_end_->m_right_child_ = NIL;
        m_end_->NIL = NIL;
        m_end_->m_color_ = BLACK;

        m_root_->m_right_child_ = m_end_;
    }
    // Destructor
    ~tree() {
        deleteAllNode();
        m_node_allocator_.destroy(NIL);
        m_node_allocator_.deallocate(NIL, 1);
        m_node_allocator_.destroy(m_end_);
        m_node_allocator_.deallocate(m_end_, 1);
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
    pair<iterator, bool> insert(const value_type& val);
    // Observers
    // Operations
    // Allocator
    void                 clear() { deleteAllNode(); }
};

template <class Key, class T, class Compare, class Alloc>
rbtNode<ft::pair<Key, T> >* tree<Key, T, Compare, Alloc>::findNode(
    value_type key) {
    node_type* node = getRoot();
    while (node != NIL) {
        if (key.first == node->m_key_.first) {
            return node;
        } else if (key.first < node->m_key_.first) {
            node = node->m_left_child_;
        } else {
            node = node->m_right_child_;
        }
    }
    return NIL;
}

template <class Key, class T, class Compare, class Alloc>
pair<tree_iterator<ft::pair<Key, T> >, bool>
tree<Key, T, Compare, Alloc>::insert(const value_type& val) {
    unSetEndNode();
    node_type* newNode = findNode(val);
    if (newNode != NIL) {
        setEndNode();
        return ft::make_pair(iterator(newNode), false);
    }
    newNode = insertKey(val);
    setBeginNode();
    setEndNode();
    return ft::make_pair(iterator(newNode), true);
}

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
    node_type* right = node->m_right_child_;
    node->m_right_child_ = right->m_left_child_;
    if (node->m_right_child_ != NIL) {
        node->m_right_child_->m_parent_ = node;
    }
    right->m_parent_ = node->m_parent_;
    if (node->m_parent_ == NULL) {
        setRoot(right);
    } else if (node == node->m_parent_->m_left_child_) {
        node->m_parent_->m_left_child_ = right;
    } else {
        node->m_parent_->m_right_child_ = right;
    }
    right->m_left_child_ = node;
    node->m_parent_ = right;
}

template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::rotateRight(node_type* node) {
    if (node == NULL) {
        return;
    }
    node_type* left = node->m_left_child_;
    node->m_left_child_ = left->m_right_child_;
    if (node->m_left_child_ != NIL) {
        node->m_left_child_->m_parent_ = node;
    }
    left->m_parent_ = node->m_parent_;
    if (node->m_parent_ == NULL) {
        setRoot(left);
    } else if (node == node->m_parent_->m_right_child_) {
        node->m_parent_->m_right_child_ = left;
    } else {
        node->m_parent_->m_left_child_ = left;
    }
    left->m_right_child_ = node;
    node->m_parent_ = left;
}

template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::deleteAllNode() {
    if (getRoot() == NIL) {
        return;
    }
    unSetEndNode();
    deleteAllNodeHelper(getRoot());
    setRoot(NIL);
}

template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::deleteAllNodeHelper(node_type* node) {
    if (node == NIL) {
        return;
    }
    deleteAllNodeHelper(node->m_left_child_);
    deleteAllNodeHelper(node->m_right_child_);
    m_node_allocator_.destroy(node);
    m_node_allocator_.deallocate(node, 1);
}

template <class Key, class T, class Compare, class Alloc>
rbtNode<ft::pair<Key, T> >* tree<Key, T, Compare, Alloc>::createNewNode(
    value_type key) {
    node_type* newNode = m_node_allocator_.allocate(1);
    newNode->m_parent_ = NULL;
    newNode->m_left_child_ = NIL;
    newNode->m_right_child_ = NIL;
    newNode->NIL = NIL;
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
            root = root->m_left_child_;
        } else {
            root = root->m_right_child_;
        }
    }
    newNode->m_parent_ = leaf;
    if (leaf == NULL) {
        setRoot(newNode);
    } else if (newNode->m_key_.first < leaf->m_key_.first) {
        leaf->m_left_child_ = newNode;
    } else {
        leaf->m_right_child_ = newNode;
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
        if (parent == grandParent->m_left_child_) {
            aunt = grandParent->m_right_child_;
            if (aunt->m_color_ == RED) {
                aunt->m_color_ = BLACK;
                newNode->m_parent_->m_color_ = BLACK;
                newNode->m_parent_->m_parent_->m_color_ = RED;
                newNode = newNode->m_parent_->m_parent_;
            } else {
                if (newNode == newNode->m_parent_->m_right_child_) {
                    newNode = newNode->m_parent_;
                    rotateLeft(newNode);
                }
                newNode->m_parent_->m_color_ = BLACK;
                newNode->m_parent_->m_parent_->m_color_ = RED;
                rotateRight(newNode->m_parent_->m_parent_);
            }
        } else if (parent == grandParent->m_right_child_) {
            aunt = newNode->m_parent_->m_parent_->m_left_child_;
            if (aunt->m_color_ == RED) {
                aunt->m_color_ = BLACK;
                newNode->m_parent_->m_color_ = BLACK;
                newNode->m_parent_->m_parent_->m_color_ = RED;
                newNode = newNode->m_parent_->m_parent_;
            } else {
                if (newNode == newNode->m_parent_->m_left_child_) {
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
void tree<Key, T, Compare, Alloc>::setBeginNode() {
    m_begin_ = getRoot()->getMinNode();
}

template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::setEndNode() {
    node_type* maxi_node = getRoot()->getMaxNode();
    maxi_node->m_right_child_ = m_end_;
    m_end_->m_parent_ = maxi_node;
}

template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::unSetEndNode() {
    node_type* parent = getParent(m_end_);
    parent->m_right_child_ = NIL;
    m_end_->m_parent_ = NULL;
}

}  // namespace ft

#endif  // TREE_HPP_
