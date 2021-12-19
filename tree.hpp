/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 16:14:57 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/19 14:56:38 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#ifndef TREE_HPP_
#define TREE_HPP_

#include <memory>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "utility.hpp"

namespace ft {

enum Color { BLACK, RED };

template <typename Key>
struct node {
    typedef Key            key_type;
    typedef node<key_type> node_type;

    node_type*             m_parent_;
    node_type*             m_left_child_;
    node_type*             m_right_child_;
    node_type*             NIL;
    enum Color             m_color_;
    key_type               m_key_;

    node()
        : m_parent_(NULL),
          m_left_child_(NULL),
          m_right_child_(NULL),
          NIL(NULL),
          m_color_(BLACK) {}
    node(node const& src)
        : m_parent_(src.m_parent_),
          m_left_child_(src.m_left_child_),
          m_right_child_(src.m_right_child_),
          NIL(src.NIL),
          m_color_(src.m_color_),
          m_key_(src.m_key_) {}
    ~node() {}
    node& operator=(node const& rhs) {
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

    void       setColor(enum Color color) { m_color_ = color; }
    node_type* getMinNode() {
        node_type* node = this;
        if (node == NULL || node == NIL) {
            return node;
        }
        while (node->m_left_child_ != NIL) {
            node = node->m_left_child_;
        }
        return node;
    }
    node_type* getMaxNode() {
        node_type* node = this;
        if (node == NULL || node == NIL) {
            return node;
        }
        while (node->m_right_child_ != NIL) {
            node = node->m_right_child_;
        }
        return node;
    }
    node_type* getNextNode() {
        node_type* node = this;
        if (node == NULL || (node == NIL && node->m_left_child_ == NULL &&
                             node->m_right_child_ == NULL)) {
            return node;
        }
        if (node->m_right_child_ != NIL) {
            return node->m_right_child_->getMinNode();
        }
        if (node->isLeftChild() == true) {
            return node->m_parent_;
        }
        while (node->m_parent_->isRightChild()) {
            node = node->m_parent_;
        }
        node = node->m_parent_;
        if (node->m_parent_ == NULL) {
            return this->m_right_child_;
        }
        return node->m_parent_;
    }
    bool isLeftChild() {
        node_type* node = this;
        if (node == NULL) {
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
    node_type* getPrevNode() {
        node_type* node = this;
        if (node == NULL || node == NIL) {
            return NIL;
        }
        if (node->m_left_child_ != NIL) {
            return node->m_left_child_->getMaxNode();
        }
        if (node->isRightChild() == true) {
            return node->m_parent_;
        }
        while (node->m_parent_->isLeftChild()) {
            node = m_parent_;
        }
        node = m_parent_;
        if (node->m_parent_ == NULL) {
            return this;
        }
        return node->m_parent_;
    }
    bool isRightChild() {
        node_type* node = this;
        if (node == NULL) {
            return false;
        }
        if (node->m_parent_ == NULL || node->m_parent_ == NIL) {
            return false;
        }
        if (node == node->m_parent_->m_right_child_) {
            return true;
        }
        return false;
    }
};

template <class Key>
class tree_iterator {
 public:
    typedef ft::bidirectional_iterator_tag iterator_category;
    typedef Key                            value_type;
    typedef std::ptrdiff_t                 difference_type;
    typedef value_type&                    reference;
    typedef value_type*                    pointer;

    typedef tree_iterator<value_type>      iterator;
    typedef node<value_type>               node_type;

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
        m_node_ = m_node_->getPrevNode();
        return *this;
    }
    iterator operator--(int) {
        iterator old = *this;
        --*this;
        return old;
    }
    node_type* getnode() const { return m_node_; }
};

template <class Key>
class const_tree_iterator {
 public:
    typedef ft::bidirectional_iterator_tag  iterator_category;
    typedef Key                             value_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef node<value_type>                node_type;
    typedef value_type&                     reference;
    typedef value_type*                     pointer;
    typedef const_tree_iterator<value_type> iterator;

 private:
    node_type* m_node_;

 public:
    const_tree_iterator() : m_node_(NULL) {}
    explicit const_tree_iterator(node_type* ptr) : m_node_(ptr) {}
    ~const_tree_iterator() {}
    const_tree_iterator& operator=(const const_tree_iterator& rhs) {
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
        m_node_ = m_node_->getPrevNode();
        return *this;
    }
    iterator operator--(int) {
        iterator old = *this;
        --*this;
        return old;
    }
    node_type* getnode() const { return m_node_; }
};

template <class Key, class Compare, class Alloc>
class tree {
 public:
    typedef Key                                      key_type;
    typedef Compare                                  key_compare;
    typedef Alloc                                    allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef tree_iterator<key_type>                  iterator;
    typedef const_tree_iterator<key_type>            const_iterator;
    typedef ft::reverse_iterator<iterator>           reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;
    typedef node<key_type>                           node_type;
    typedef
        typename Alloc::template rebind<node_type>::other node_allocator_type;
    typedef typename node_allocator_type::size_type       size_type;

 private:
    key_compare         m_key_compare_;
    allocator_type      m_allocator_;
    node_allocator_type m_node_allocator_;
    node_type*          m_root_;
    node_type*          NIL;
    node_type*          m_begin_;
    node_type*          m_end_;

 private:
    tree() {}
    tree(const tree& src) { *this = src; }
    node_type* getRoot() const { return m_root_; }
    void       setRoot(node_type* node) { m_root_ = node; }
    size_type  getSizeHelper(node_type* node) const;
    node_type* getParent(node_type* node) const;
    node_type* getGrandParent(node_type* node) const;
    enum Color getColor(node_type* node) const;
    void       rotateLeft(node_type* node);
    void       rotateRight(node_type* node);
    void       deleteAllnode();
    void       deleteAllnodeHelper(node_type* node);
    node_type* createNewnode(const key_type& key);
    node_type* insertKey(const key_type& key);
    void       balanceAfterInsert(node_type* newnode);
    void       setBeginnode();
    void       setEndnode();
    void       unSetEndnode();
    node_type* findnode(key_type key);
    void       deleteKey(const key_type& key);
    void       deleteKeyHelper(node_type* node, const key_type& key);
    void       balanceAfterDelete(node_type* node);
    void       transplantnode(node_type* u, node_type* v);

 public:
    // Constructor
    explicit tree(const key_compare&    comp = key_compare(),
                  const allocator_type& alloc = allocator_type());
    // Destructor
    ~tree();
    // operator=
    tree& operator=(const tree& rhs);

 public:
    // Iterators
    iterator       begin() { return iterator(m_begin_); }
    const_iterator begin() const { return const_iterator(m_begin_); }
    iterator       end() {
        if (m_begin_ == NIL) {
            return iterator(m_begin_);
        }
        return iterator(m_end_);
    }
    const_iterator end() const {
        if (m_begin_ == NIL) {
            return const_iterator(m_begin_);
        }
        return const_iterator(m_end_);
    }
    // Capacity
    size_type size() const;
    size_type max_size() const { return m_node_allocator_.max_size(); }
    // Element access
    // Modifiers
    ft::pair<iterator, bool>             insert(const key_type& k);
    void                                 erase(iterator position);
    size_type                            erase(const key_type& k);
    void                                 erase(iterator first, iterator last);
    void                                 swap(tree& x);
    void                                 clear() { deleteAllnode(); }
    // Observers
    // Operations
    iterator                             find(const key_type& k);
    const_iterator                       find(const key_type& k) const;
    size_type                            count(const key_type& k) const;
    iterator                             lower_bound(const key_type& k);
    const_iterator                       lower_bound(const key_type& k) const;
    iterator                             upper_bound(const key_type& k);
    const_iterator                       upper_bound(const key_type& k) const;
    pair<const_iterator, const_iterator> equal_range(const key_type& k) const;
    pair<iterator, iterator>             equal_range(const key_type& k);
    // Allocator
    allocator_type                       get_allocator() const;
};

// Constructor
template <class Key, class Compare, class Alloc>
tree<Key, Compare, Alloc>::tree(const key_compare&    comp,
                                const allocator_type& alloc)
    : m_key_compare_(comp), m_allocator_(alloc), m_node_allocator_() {
    NIL = m_node_allocator_.allocate(1, this);
    NIL->m_parent_ = NULL;
    NIL->m_left_child_ = NULL;
    NIL->m_right_child_ = NULL;
    NIL->NIL = NIL;
    NIL->m_color_ = BLACK;

    m_root_ = NIL;
    m_begin_ = m_root_;

    m_end_ = m_node_allocator_.allocate(1, this);
    m_end_->m_parent_ = m_root_;
    m_end_->m_left_child_ = NIL;
    m_end_->m_right_child_ = NIL;
    m_end_->NIL = NIL;
    m_end_->m_color_ = BLACK;

    m_root_->m_right_child_ = m_end_;
}

// Destructor
template <class Key, class Compare, class Alloc>
tree<Key, Compare, Alloc>::~tree() {
    deleteAllnode();
    m_node_allocator_.deallocate(NIL, 1);
    m_node_allocator_.deallocate(m_end_, 1);
}

// operator=
template <class Key, class Compare, class Alloc>
tree<Key, Compare, Alloc>& tree<Key, Compare, Alloc>::operator=(
    const tree& rhs) {
    if (this != &rhs) {
        clear();
        if (rhs.size() > 0) {
            for (const_iterator it = rhs.begin(); it != rhs.end(); ++it) {
                insert(*it);
            }
        }
    }
    return *this;
}

// size()
template <class Key, class Compare, class Alloc>
typename tree<Key, Compare, Alloc>::size_type tree<Key, Compare, Alloc>::size()
    const {
    size_type size = getSizeHelper(getRoot());
    if (size == 0) {
        return size;
    } else {
        return size - 1;
    }
}

template <class Key, class Compare, class Alloc>
typename tree<Key, Compare, Alloc>::size_type
tree<Key, Compare, Alloc>::getSizeHelper(node_type* node) const {
    if (node == NULL || node == NIL) {
        return (0);
    }
    return (getSizeHelper(node->m_left_child_) +
            getSizeHelper(node->m_right_child_) + 1);
}

// findnode
template <class Key, class Compare, class Alloc>
typename tree<Key, Compare, Alloc>::node_type*
tree<Key, Compare, Alloc>::findnode(key_type k) {
    node_type* node = getRoot();
    while (node != NIL) {
        if (!m_key_compare_(k, node->m_key_) &&
            !m_key_compare_(node->m_key_, k)) {
            return node;
        } else if (m_key_compare_(k, node->m_key_)) {
            node = node->m_left_child_;
        } else {
            node = node->m_right_child_;
        }
    }
    return NIL;
}

// insert()
template <class Key, class Compare, class Alloc>
pair<tree_iterator<Key>, bool> tree<Key, Compare, Alloc>::insert(
    const key_type& k) {
    unSetEndnode();
    node_type* newnode = findnode(k);
    if (newnode != NIL) {
        setEndnode();
        return ft::make_pair(iterator(newnode), false);
    }
    newnode = insertKey(k);
    setBeginnode();
    setEndnode();
    return ft::make_pair(iterator(newnode), true);
}

// getParent
template <class Key, class Compare, class Alloc>
typename tree<Key, Compare, Alloc>::node_type*
tree<Key, Compare, Alloc>::getParent(node_type* node) const {
    if (node == NULL) {
        return NULL;
    }
    return node->m_parent_;
}

// getGrandParent
template <class Key, class Compare, class Alloc>
typename tree<Key, Compare, Alloc>::node_type*
tree<Key, Compare, Alloc>::getGrandParent(node_type* node) const {
    if (node == NULL || node->m_parent_ == NULL) {
        return NULL;
    }
    return node->m_parent_->m_parent_;
}

// getColor
template <class Key, class Compare, class Alloc>
enum Color tree<Key, Compare, Alloc>::getColor(node_type* node) const {
    if (node == NULL) {
        return BLACK;
    }
    return node->m_color_;
}

// rotateLeft
template <class Key, class Compare, class Alloc>
void tree<Key, Compare, Alloc>::rotateLeft(node_type* node) {
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

// rotateRight
template <class Key, class Compare, class Alloc>
void tree<Key, Compare, Alloc>::rotateRight(node_type* node) {
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

// deleteAllnode
template <class Key, class Compare, class Alloc>
void tree<Key, Compare, Alloc>::deleteAllnode() {
    if (getRoot() == NIL) {
        return;
    }
    unSetEndnode();
    deleteAllnodeHelper(getRoot());
    setRoot(NIL);
    setEndnode();
}

template <class Key, class Compare, class Alloc>
void tree<Key, Compare, Alloc>::deleteAllnodeHelper(node_type* node) {
    if (node == NIL) {
        return;
    }
    deleteAllnodeHelper(node->m_left_child_);
    deleteAllnodeHelper(node->m_right_child_);
    m_allocator_.destroy(m_allocator_.address(node->m_key_));
    m_node_allocator_.destroy(node);
    m_node_allocator_.deallocate(node, 1);
}

// createNewnode
template <class Key, class Compare, class Alloc>
typename tree<Key, Compare, Alloc>::node_type*
tree<Key, Compare, Alloc>::createNewnode(const key_type& k) {
    node_type* newnode = m_node_allocator_.allocate(1, this);
    newnode->m_parent_ = NULL;
    newnode->m_left_child_ = NIL;
    newnode->m_right_child_ = NIL;
    newnode->NIL = NIL;
    newnode->m_color_ = RED;
    m_allocator_.construct(m_allocator_.address(newnode->m_key_), k);
    return newnode;
}

// insertKey
template <class Key, class Compare, class Alloc>
typename tree<Key, Compare, Alloc>::node_type*
tree<Key, Compare, Alloc>::insertKey(const key_type& k) {
    node_type* newnode = createNewnode(k);
    node_type* leaf = NULL;
    node_type* root = getRoot();
    while (root != NIL) {
        leaf = root;
        if (m_key_compare_(newnode->m_key_, root->m_key_)) {
            root = root->m_left_child_;
        } else {
            root = root->m_right_child_;
        }
    }
    newnode->m_parent_ = leaf;
    if (leaf == NULL) {
        setRoot(newnode);
    } else if (m_key_compare_(newnode->m_key_, leaf->m_key_)) {
        leaf->m_left_child_ = newnode;
    } else {
        leaf->m_right_child_ = newnode;
    }
    if (getParent(newnode) == NULL) {
        newnode->setColor(BLACK);
        return newnode;
    }
    if (getGrandParent(newnode) == NULL) {
        return newnode;
    }
    balanceAfterInsert(newnode);
    return newnode;
}

template <class Key, class Compare, class Alloc>
void tree<Key, Compare, Alloc>::balanceAfterInsert(node_type* newnode) {
    node_type* parent = NULL;
    node_type* aunt = NULL;
    node_type* grandParent = NULL;
    while (newnode != getRoot() && getColor(getParent(newnode)) == RED) {
        parent = getParent(newnode);
        grandParent = getGrandParent(newnode);
        if (parent->isLeftChild()) {
            aunt = grandParent->m_right_child_;
            if (aunt->m_color_ == RED) {
                aunt->setColor(BLACK);
                newnode->m_parent_->setColor(BLACK);
                newnode->m_parent_->m_parent_->setColor(RED);
                newnode = newnode->m_parent_->m_parent_;
            } else {
                if (newnode->isRightChild()) {
                    newnode = newnode->m_parent_;
                    rotateLeft(newnode);
                }
                newnode->m_parent_->setColor(BLACK);
                newnode->m_parent_->m_parent_->setColor(RED);
                rotateRight(newnode->m_parent_->m_parent_);
            }
        } else {
            aunt = newnode->m_parent_->m_parent_->m_left_child_;
            if (aunt->m_color_ == RED) {
                aunt->setColor(BLACK);
                newnode->m_parent_->setColor(BLACK);
                newnode->m_parent_->m_parent_->setColor(RED);
                newnode = newnode->m_parent_->m_parent_;
            } else {
                if (newnode->isLeftChild()) {
                    newnode = newnode->m_parent_;
                    rotateRight(newnode);
                }
                newnode->m_parent_->setColor(BLACK);
                newnode->m_parent_->m_parent_->setColor(RED);
                rotateLeft(newnode->m_parent_->m_parent_);
            }
        }
    }
    getRoot()->setColor(BLACK);
}

// setBeginnode
template <class Key, class Compare, class Alloc>
void tree<Key, Compare, Alloc>::setBeginnode() {
    m_begin_ = getRoot()->getMinNode();
}

// setEndnode
template <class Key, class Compare, class Alloc>
void tree<Key, Compare, Alloc>::setEndnode() {
    node_type* maxi_node = getRoot()->getMaxNode();
    maxi_node->m_right_child_ = m_end_;
    m_end_->m_parent_ = maxi_node;
}

// unSetEndnode
template <class Key, class Compare, class Alloc>
void tree<Key, Compare, Alloc>::unSetEndnode() {
    node_type* parent = getParent(m_end_);
    parent->m_right_child_ = NIL;
    m_end_->m_parent_ = NULL;
}

// deleteKey
template <class Key, class Compare, class Alloc>
void tree<Key, Compare, Alloc>::deleteKey(const key_type& k) {
    deleteKeyHelper(getRoot(), k);
}

template <class Key, class Compare, class Alloc>
void tree<Key, Compare, Alloc>::deleteKeyHelper(node_type*      node,
                                                const key_type& k) {
    if (node == NULL) {
        return;
    }
    node_type* nodeToBeDeleted = NIL;
    while (node != NIL) {
        if (!m_key_compare_(node->m_key_, k) &&
            !m_key_compare_(k, node->m_key_)) {
            nodeToBeDeleted = node;
        }
        if (!m_key_compare_(k, node->m_key_)) {
            node = node->m_right_child_;
        } else {
            node = node->m_left_child_;
        }
    }
    if (nodeToBeDeleted == NIL) {
        return;
    }
    node_type* y = nodeToBeDeleted;
    node_type* x;
    int        original_color = y->m_color_;
    if (nodeToBeDeleted->m_left_child_ == NIL) {
        x = nodeToBeDeleted->m_right_child_;
        transplantnode(nodeToBeDeleted, x);
    } else if (nodeToBeDeleted->m_right_child_ == NIL) {
        x = nodeToBeDeleted->m_left_child_;
        transplantnode(nodeToBeDeleted, x);
    } else {
        y = nodeToBeDeleted->m_right_child_->getMinNode();
        original_color = y->m_color_;
        x = y->m_right_child_;
        if (y->m_parent_ == nodeToBeDeleted) {
            x->m_parent_ = y;
        } else {
            transplantnode(y, y->m_right_child_);
            y->m_right_child_ = nodeToBeDeleted->m_right_child_;
            y->m_right_child_->m_parent_ = y;
        }
        transplantnode(nodeToBeDeleted, y);
        y->m_left_child_ = nodeToBeDeleted->m_left_child_;
        y->m_left_child_->m_parent_ = y;
        y->m_color_ = nodeToBeDeleted->m_color_;
    }
    m_allocator_.destroy(m_allocator_.address(nodeToBeDeleted->m_key_));
    m_node_allocator_.destroy(nodeToBeDeleted);
    m_node_allocator_.deallocate(nodeToBeDeleted, 1);
    if (original_color == BLACK) {
        balanceAfterDelete(x);
    }
}

template <class Key, class Compare, class Alloc>
void tree<Key, Compare, Alloc>::balanceAfterDelete(node_type* x) {
    if (x == NULL) {
        return;
    }
    while (x != getRoot() && x->m_color_ == BLACK) {
        if (x->isLeftChild()) {
            node_type* aunt = x->m_parent_->m_right_child_;
            if (aunt->m_color_ == RED) {
                aunt->setColor(BLACK);
                x->m_parent_->setColor(RED);
                rotateLeft(x->m_parent_);
                aunt = x->m_parent_->m_right_child_;
            }
            if (aunt->m_left_child_->m_color_ == BLACK &&
                aunt->m_right_child_->m_color_ == BLACK) {
                aunt->setColor(RED);
                x = x->m_parent_;
            } else {
                if (aunt->m_right_child_->m_color_ == BLACK) {
                    aunt->m_left_child_->setColor(BLACK);
                    aunt->setColor(RED);
                    rotateRight(aunt);
                    aunt = x->m_parent_->m_right_child_;
                }
                aunt->setColor(x->m_parent_->m_color_);
                x->m_parent_->setColor(BLACK);
                aunt->m_right_child_->setColor(BLACK);
                rotateLeft(x->m_parent_);
                x = getRoot();
            }
        } else {
            node_type* aunt = x->m_parent_->m_left_child_;
            if (aunt->m_color_ == RED) {
                aunt->setColor(BLACK);
                x->m_parent_->setColor(RED);
                rotateRight(x->m_parent_);
                aunt = x->m_parent_->m_left_child_;
            }
            if (aunt->m_right_child_->m_color_ == BLACK &&
                aunt->m_left_child_->m_color_ == BLACK) {
                aunt->setColor(RED);
                x = x->m_parent_;
            } else {
                if (aunt->m_left_child_->m_color_ == BLACK) {
                    aunt->m_right_child_->setColor(BLACK);
                    aunt->setColor(RED);
                    rotateLeft(aunt);
                    aunt = x->m_parent_->m_left_child_;
                }
                aunt->setColor(x->m_parent_->m_color_);
                x->m_parent_->setColor(BLACK);
                aunt->m_left_child_->setColor(BLACK);
                rotateRight(x->m_parent_);
                x = getRoot();
            }
        }
    }
    x->setColor(BLACK);
}

template <class Key, class Compare, class Alloc>
void tree<Key, Compare, Alloc>::transplantnode(node_type* u, node_type* v) {
    if (u == NULL || v == NULL) {
        return;
    }
    if (u->m_parent_ == NULL) {
        setRoot(v);
    } else if (u == u->m_parent_->m_left_child_) {
        u->m_parent_->m_left_child_ = v;
    } else {
        u->m_parent_->m_right_child_ = v;
    }
    v->m_parent_ = u->m_parent_;
}

// erase
template <class Key, class Compare, class Alloc>
void tree<Key, Compare, Alloc>::erase(iterator position) {
    unSetEndnode();
    deleteKey(*position);
    setBeginnode();
    setEndnode();
}

template <class Key, class Compare, class Alloc>
typename tree<Key, Compare, Alloc>::size_type tree<Key, Compare, Alloc>::erase(
    const key_type& k) {
    if (find(k).getnode() == NIL) {
        return 0;
    }
    unSetEndnode();
    deleteKey(k);
    setBeginnode();
    setEndnode();
    return 1;
}

template <class Key, class Compare, class Alloc>
void tree<Key, Compare, Alloc>::erase(iterator first, iterator last) {
    while (first != last) {
        erase(first++);
    }
}

// swap
template <class Key, class Compare, class Alloc>
void tree<Key, Compare, Alloc>::swap(tree& x) {
    if (this != &x) {
        ft::swap(m_key_compare_, x.m_key_compare_);
        ft::swap(m_allocator_, x.m_allocator_);
        ft::swap(m_node_allocator_, x.m_node_allocator_);
        ft::swap(m_root_, x.m_root_);
        ft::swap(NIL, x.NIL);
        ft::swap(m_begin_, x.m_begin_);
        ft::swap(m_end_, x.m_end_);
    }
}

// find
template <class Key, class Compare, class Alloc>
typename tree<Key, Compare, Alloc>::iterator tree<Key, Compare, Alloc>::find(
    const key_type& k) {
    node_type* node = getRoot();
    while (node != NIL && node != m_end_) {
        if (!m_key_compare_(k, node->m_key_) &&
            !m_key_compare_(node->m_key_, k)) {
            return iterator(node);
        } else if (m_key_compare_(k, node->m_key_)) {
            node = node->m_left_child_;
        } else {
            node = node->m_right_child_;
        }
    }
    return iterator(NIL);
}

template <class Key, class Compare, class Alloc>
typename tree<Key, Compare, Alloc>::const_iterator
tree<Key, Compare, Alloc>::find(const key_type& k) const {
    node_type* node = getRoot();
    while (node != NIL && node != m_end_) {
        if (!m_key_compare_(k, node->m_key_) &&
            !m_key_compare_(node->m_key_, k)) {
            return const_iterator(node);
        } else if (m_key_compare_(k, node->m_key_)) {
            node = node->m_left_child_;
        } else {
            node = node->m_right_child_;
        }
    }
    return const_iterator(NIL);
}

// count
template <class Key, class Compare, class Alloc>
typename tree<Key, Compare, Alloc>::size_type tree<Key, Compare, Alloc>::count(
    const key_type& k) const {
    if (find(k).getnode() == NIL) {
        return 0;
    }
    return 1;
}

// lower_bound
template <class Key, class Compare, class Alloc>
typename tree<Key, Compare, Alloc>::iterator
tree<Key, Compare, Alloc>::lower_bound(const key_type& k) {
    iterator it = begin();
    while (it != end()) {
        if (!m_key_compare_(*it, k)) {
            return it;
        }
        ++it;
    }
    return it;
}

template <class Key, class Compare, class Alloc>
typename tree<Key, Compare, Alloc>::const_iterator
tree<Key, Compare, Alloc>::lower_bound(const key_type& k) const {
    const_iterator it = begin();
    while (it != end()) {
        if (!m_key_compare_(*it, k)) {
            return it;
        }
        ++it;
    }
    return it;
}

// upper_bound
template <class Key, class Compare, class Alloc>
typename tree<Key, Compare, Alloc>::iterator
tree<Key, Compare, Alloc>::upper_bound(const key_type& k) {
    iterator it = begin();
    while (it != end()) {
        if (m_key_compare_(k, *it)) {
            return it;
        }
        ++it;
    }
    return it;
}

template <class Key, class Compare, class Alloc>
typename tree<Key, Compare, Alloc>::const_iterator
tree<Key, Compare, Alloc>::upper_bound(const key_type& k) const {
    const_iterator it = begin();
    while (it != end()) {
        if (m_key_compare_(k, *it)) {
            return it;
        }
        ++it;
    }
    return it;
}

// equal_range
template <class Key, class Compare, class Alloc>
ft::pair<typename tree<Key, Compare, Alloc>::const_iterator,
         typename tree<Key, Compare, Alloc>::const_iterator>
tree<Key, Compare, Alloc>::equal_range(const key_type& k) const {
    return ft::make_pair(lower_bound(k), upper_bound(k));
}

template <class Key, class Compare, class Alloc>
ft::pair<typename tree<Key, Compare, Alloc>::iterator,
         typename tree<Key, Compare, Alloc>::iterator>
tree<Key, Compare, Alloc>::equal_range(const key_type& k) {
    return ft::make_pair(lower_bound(k), upper_bound(k));
}

}  // namespace ft

#endif  // TREE_HPP_
