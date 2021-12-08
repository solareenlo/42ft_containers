/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 08:24:04 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/08 18:07:12 by tayamamo         ###   ########.fr       */
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
    rbtNode*   parent;
    rbtNode*   left;
    rbtNode*   right;
    enum Color color;
    Key        key;

    rbtNode() : parent(NULL), left(NULL), right(NULL), color(BLACK) {}
    rbtNode(rbtNode const& src)
        : parent(src.parent),
          left(src.left),
          right(src.right),
          color(src.color),
          key(src.key) {}
    ~rbtNode() {}
    rbtNode& operator=(rbtNode const& rhs) {
        if (this != &rhs) {
            parent = rhs.palent;
            right = rhs.right;
            left = rhs.left;
            color = rhs.color;
            key = rhs.key;
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
    node_type* m_ptr_;

 public:
    tree_iterator() : m_ptr_(NULL) {}
    explicit tree_iterator(node_type* ptr) : m_ptr_(ptr) {}
    ~tree_iterator() {}
    tree_iterator& operator=(const tree_iterator& rhs) {
        if (this != &rhs) {
            m_ptr_ = rhs.m_ptr_;
        }
        return *this;
    }

 public:
    bool      operator==(iterator rhs) const { return m_ptr_ == rhs.m_ptr_; }
    bool      operator!=(iterator rhs) const { return m_ptr_ != rhs.m_ptr_; }
    reference operator*() const { return m_ptr_->key; }
    pointer   operator->() const { return &(m_ptr_->key); }
    iterator& operator++() {
        m_ptr_ = m_ptr_->next();
        return *this;
    }
    iterator& operator++(int) {
        iterator old = *this;
        m_ptr_ = m_ptr_->next();
        return old;
    }
    iterator& operator--() {
        m_ptr_ = m_ptr_->prev();
        return *this;
    }
    iterator& operator--(int) {
        iterator old = *this;
        m_ptr_ = m_ptr_->prev();
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
    node_type* m_ptr_;

 public:
    const_tree_iterator() : m_ptr_(NULL) {}
    explicit const_tree_iterator(const iterator& src) : m_ptr_(src.m_ptr_) {}
    explicit const_tree_iterator(pointer ptr) : m_ptr_(ptr) {}
    ~const_tree_iterator() {}
    const_tree_iterator& operator=(const const_tree_iterator& rhs) {
        if (this != &rhs) {
            this->m_ptr_ = rhs.m_ptr_;
        }
        return *this;
    }

 public:
    bool      operator==(iterator rhs) const { return m_ptr_ == rhs.m_ptr_; }
    bool      operator!=(iterator rhs) const { return m_ptr_ != rhs.m_ptr_; }
    reference operator*() const { return m_ptr_->key; }
    pointer   operator->() const { return &(m_ptr_->key); }
    iterator& operator++() {
        m_ptr_ = m_ptr_->next();
        return *this;
    }
    iterator& operator++(int) {
        iterator old = *this;
        m_ptr_ = m_ptr_->next();
        return old;
    }
    iterator& operator--() {
        m_ptr_ = m_ptr_->prev();
        return *this;
    }
    iterator& operator--(int) {
        iterator old = *this;
        m_ptr_ = m_ptr_->prev();
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

 private:
    key_compare    m_key_compare_;
    allocator_type m_allocator_;
    node_type*     m_root_;
    node_type*     NIL;
    node_type*     m_begin_;
    node_type*     m_end_;

 private:
    tree();
    tree(const tree& src);
    node_type* getRoot() const { return m_root_; }
    void       setRoot(node_type* node) { m_root_ = node; }
    node_type* getParent(node_type* node) const {
        if (node == NULL) {
            return NULL;
        }
        return node->parent;
    }
    node_type* getGrandParent(node_type* node) const {
        if (node == NULL || node->parent == NULL) {
            return NULL;
        }
        return node->parent->parent;
    }
    enum Color getColor(node_type* node) const {
        if (node == NULL) {
            return BLACK;
        }
        return node->color;
    }
    void setColor(node_type* node, enum Color color) {
        if (node == NULL) {
            return;
        }
        node->color = color;
    }
    void rotateLeft(node_type* node);
    void rotateRight(node_type* node);
    void deleteAllNode() {
        if (getRoot() == NIL) {
            return;
        }
        deleteAllNodeHelper(getRoot());
        setRoot(NIL);
    }
    void deleteAllNodeHelper(node_type* node) {
        if (node == NIL) {
            return;
        }
        deleteAllNodeHelper(node->left);
        deleteAllNodeHelper(node->right);
        delete node;
    }
    node_type* createNewNode(value_type key) {
        node_type* newNode = new node_type;
        newNode->parent = NULL;
        newNode->left = NIL;
        newNode->right = NIL;
        newNode->color = RED;
        newNode->key = key;
        return newNode;
    }
    node_type* insertKey(value_type key);
    void       balanceAfterInsert(node_type* newNode);
    node_type* minKeyNode(node_type* node);
    node_type* maxKeyNode(node_type* node);

 public:
    // Constructor
    explicit tree(const key_compare&    comp = key_compare(),
                  const allocator_type& alloc = allocator_type())
        : m_key_compare_(comp), m_allocator_(alloc) {
        NIL = new node_type;
        NIL->parent = NULL;
        NIL->color = BLACK;
        NIL->left = NULL;
        NIL->right = NULL;
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
        m_begin_ = minKeyNode(getRoot());
        m_end_ = maxKeyNode(getRoot());
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
void tree<Key, T, Compare, Alloc>::rotateLeft(node_type* node) {
    if (node == NULL) {
        return;
    }
    node_type* right = node->right;
    node->right = right->left;
    if (node->right != NIL) {
        node->right->parent = node;
    }
    right->parent = node->parent;
    if (node->parent == NULL) {
        setRoot(right);
    } else if (node == node->parent->left) {
        node->parent->left = right;
    } else {
        node->parent->right = right;
    }
    right->left = node;
    node->parent = right;
}

template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::rotateRight(node_type* node) {
    if (node == NULL) {
        return;
    }
    node_type* left = node->left;
    node->left = left->right;
    if (node->left != NIL) {
        node->left->parent = node;
    }
    left->parent = node->parent;
    if (node->parent == NULL) {
        setRoot(left);
    } else if (node == node->parent->right) {
        node->parent->right = left;
    } else {
        node->parent->left = left;
    }
    left->right = node;
    node->parent = left;
}

template <class Key, class T, class Compare, class Alloc>
rbtNode<ft::pair<Key, T> >* tree<Key, T, Compare, Alloc>::insertKey(
    value_type key) {
    node_type* newNode = createNewNode(key);
    node_type* leaf = NULL;
    node_type* root = getRoot();
    while (root != NIL) {
        leaf = root;
        if (newNode->key.first < root->key.first) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    newNode->parent = leaf;
    if (leaf == NULL) {
        setRoot(newNode);
    } else if (newNode->key.first < leaf->key.first) {
        leaf->left = newNode;
    } else {
        leaf->right = newNode;
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
        if (parent == grandParent->left) {
            aunt = grandParent->right;
            if (aunt->color == RED) {
                aunt->color = BLACK;
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            } else {
                if (newNode == newNode->parent->right) {
                    newNode = newNode->parent;
                    rotateLeft(newNode);
                }
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                rotateRight(newNode->parent->parent);
            }
        } else if (parent == grandParent->right) {
            aunt = newNode->parent->parent->left;
            if (aunt->color == RED) {
                aunt->color = BLACK;
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            } else {
                if (newNode == newNode->parent->left) {
                    newNode = newNode->parent;
                    rotateRight(newNode);
                }
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                rotateLeft(newNode->parent->parent);
            }
        }
    }
    setColor(getRoot(), BLACK);
}

template <class Key, class T, class Compare, class Alloc>
rbtNode<ft::pair<Key, T> >* tree<Key, T, Compare, Alloc>::minKeyNode(
    node_type* node) {
    while (node->left != NIL) {
        node = node->left;
    }
    return node;
}

template <class Key, class T, class Compare, class Alloc>
rbtNode<ft::pair<Key, T> >* tree<Key, T, Compare, Alloc>::maxKeyNode(
    node_type* node) {
    while (node->right != NIL) {
        node = node->right;
    }
    return node;
}

}  // namespace ft

#endif  // TREE_HPP_
