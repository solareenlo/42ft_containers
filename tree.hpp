/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 08:24:04 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/15 16:21:24 by tayamamo         ###   ########.fr       */
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
        return node;
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
        m_node_ = m_node_->getPrevNode();
        return *this;
    }
    iterator operator--(int) {
        iterator old = *this;
        --*this;
        return old;
    }
    node_type* getNode() const { return m_node_; }
};

template <class ValueType>
class const_tree_iterator {
 public:
    typedef ft::bidirectional_iterator_tag  iterator_category;
    typedef ValueType                       value_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef rbtNode<value_type>             node_type;
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
    node_type* getNode() const { return m_node_; }
};

template <class Key, class T, class Compare, class Alloc>
class tree {
 public:
    typedef Key                                      key_type;
    typedef T                                        mapped_type;
    typedef ft::pair<const key_type, mapped_type>    value_type;
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
    tree();
    tree(const tree& src);
    node_type* getRoot() const { return m_root_; }
    void       setRoot(node_type* node) { m_root_ = node; }
    size_type  getSizeHelper(node_type* node) const;
    node_type* getParent(node_type* node) const;
    node_type* getGrandParent(node_type* node) const;
    enum Color getColor(node_type* node) const;
    void       rotateLeft(node_type* node);
    void       rotateRight(node_type* node);
    void       deleteAllNode();
    void       deleteAllNodeHelper(node_type* node);
    node_type* createNewNode(const value_type& key);
    node_type* insertKey(const value_type& key);
    void       balanceAfterInsert(node_type* newNode);
    void       setBeginNode();
    void       setEndNode();
    void       unSetEndNode();
    node_type* findNode(value_type key);
    void       deleteKey(const value_type& key);
    void       deleteKeyHelper(node_type* node, const value_type& key);
    void       balanceAfterDelete(node_type* node);
    void       transplantNode(node_type* u, node_type* v);

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
    iterator       end() { return iterator(m_end_); }
    const_iterator end() const { return const_iterator(m_end_); }
    // Capacity
    size_type      size() const;
    size_type      max_size() const { return m_node_allocator_.max_size(); }
    // Element access
    // Modifiers
    pair<iterator, bool>                 insert(const value_type& val);
    void                                 erase(iterator position);
    size_type                            erase(const key_type& k);
    void                                 erase(iterator first, iterator last);
    void                                 swap(tree& x);
    void                                 clear() { deleteAllNode(); }
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
template <class Key, class T, class Compare, class Alloc>
tree<Key, T, Compare, Alloc>::tree(const key_compare&    comp,
                                   const allocator_type& alloc)
    : m_key_compare_(comp), m_node_allocator_(alloc) {
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
template <class Key, class T, class Compare, class Alloc>
tree<Key, T, Compare, Alloc>::~tree() {
    deleteAllNode();
    m_node_allocator_.deallocate(NIL, 1);
    m_node_allocator_.deallocate(m_end_, 1);
}

// operator=
template <class Key, class T, class Compare, class Alloc>
tree<Key, T, Compare, Alloc>& tree<Key, T, Compare, Alloc>::operator=(
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
template <class Key, class T, class Compare, class Alloc>
typename tree<Key, T, Compare, Alloc>::size_type
tree<Key, T, Compare, Alloc>::size() const {
    size_type size = getSizeHelper(getRoot());
    if (size == 0) {
        return size;
    } else {
        return size - 1;
    }
}

template <class Key, class T, class Compare, class Alloc>
typename tree<Key, T, Compare, Alloc>::size_type
tree<Key, T, Compare, Alloc>::getSizeHelper(node_type* node) const {
    if (node == NULL || node == NIL) {
        return (0);
    }
    return (getSizeHelper(node->m_left_child_) +
            getSizeHelper(node->m_right_child_) + 1);
}

// findNode
template <class Key, class T, class Compare, class Alloc>
typename tree<Key, T, Compare, Alloc>::node_type*
tree<Key, T, Compare, Alloc>::findNode(value_type key) {
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

// insert()
template <class Key, class T, class Compare, class Alloc>
pair<tree_iterator<ft::pair<const Key, T> >, bool>
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

// getParent
template <class Key, class T, class Compare, class Alloc>
typename tree<Key, T, Compare, Alloc>::node_type*
tree<Key, T, Compare, Alloc>::getParent(node_type* node) const {
    if (node == NULL) {
        return NULL;
    }
    return node->m_parent_;
}

// getGrandParent
template <class Key, class T, class Compare, class Alloc>
typename tree<Key, T, Compare, Alloc>::node_type*
tree<Key, T, Compare, Alloc>::getGrandParent(node_type* node) const {
    if (node == NULL || node->m_parent_ == NULL) {
        return NULL;
    }
    return node->m_parent_->m_parent_;
}

// getColor
template <class Key, class T, class Compare, class Alloc>
enum Color tree<Key, T, Compare, Alloc>::getColor(node_type* node) const {
    if (node == NULL) {
        return BLACK;
    }
    return node->m_color_;
}

// rotateLeft
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

// rotateRight
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

// deleteAllNode
template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::deleteAllNode() {
    if (getRoot() == NIL) {
        return;
    }
    unSetEndNode();
    deleteAllNodeHelper(getRoot());
    setRoot(NIL);
    setEndNode();
}

template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::deleteAllNodeHelper(node_type* node) {
    if (node == NIL) {
        return;
    }
    deleteAllNodeHelper(node->m_left_child_);
    deleteAllNodeHelper(node->m_right_child_);
    m_allocator_.destroy(m_allocator_.address(node->m_key_));
    m_node_allocator_.destroy(node);
    m_node_allocator_.deallocate(node, 1);
}

// createNewNode
template <class Key, class T, class Compare, class Alloc>
typename tree<Key, T, Compare, Alloc>::node_type*
tree<Key, T, Compare, Alloc>::createNewNode(const value_type& key) {
    node_type* newNode = m_node_allocator_.allocate(1, this);
    newNode->m_parent_ = NULL;
    newNode->m_left_child_ = NIL;
    newNode->m_right_child_ = NIL;
    newNode->NIL = NIL;
    newNode->m_color_ = RED;
    m_allocator_.construct(m_allocator_.address(newNode->m_key_), key);
    return newNode;
}

// insertKey
template <class Key, class T, class Compare, class Alloc>
typename tree<Key, T, Compare, Alloc>::node_type*
tree<Key, T, Compare, Alloc>::insertKey(const value_type& key) {
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
        newNode->setColor(BLACK);
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
        if (parent->isLeftChild()) {
            aunt = grandParent->m_right_child_;
            if (aunt->m_color_ == RED) {
                aunt->setColor(BLACK);
                newNode->m_parent_->setColor(BLACK);
                newNode->m_parent_->m_parent_->setColor(RED);
                newNode = newNode->m_parent_->m_parent_;
            } else {
                if (newNode->isRightChild()) {
                    newNode = newNode->m_parent_;
                    rotateLeft(newNode);
                }
                newNode->m_parent_->setColor(BLACK);
                newNode->m_parent_->m_parent_->setColor(RED);
                rotateRight(newNode->m_parent_->m_parent_);
            }
        } else {
            aunt = newNode->m_parent_->m_parent_->m_left_child_;
            if (aunt->m_color_ == RED) {
                aunt->setColor(BLACK);
                newNode->m_parent_->setColor(BLACK);
                newNode->m_parent_->m_parent_->setColor(RED);
                newNode = newNode->m_parent_->m_parent_;
            } else {
                if (newNode->isLeftChild()) {
                    newNode = newNode->m_parent_;
                    rotateRight(newNode);
                }
                newNode->m_parent_->setColor(BLACK);
                newNode->m_parent_->m_parent_->setColor(RED);
                rotateLeft(newNode->m_parent_->m_parent_);
            }
        }
    }
    getRoot()->setColor(BLACK);
}

// setBeginNode
template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::setBeginNode() {
    m_begin_ = getRoot()->getMinNode();
}

// setEndNode
template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::setEndNode() {
    node_type* maxi_node = getRoot()->getMaxNode();
    maxi_node->m_right_child_ = m_end_;
    m_end_->m_parent_ = maxi_node;
}

// unSetEndNode
template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::unSetEndNode() {
    node_type* parent = getParent(m_end_);
    parent->m_right_child_ = NIL;
    m_end_->m_parent_ = NULL;
}

// deleteKey
template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::deleteKey(const value_type& key) {
    deleteKeyHelper(getRoot(), key);
}

template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::deleteKeyHelper(node_type*        node,
                                                   const value_type& key) {
    if (node == NULL) {
        return;
    }
    node_type* nodeToBeDeleted = NIL;
    while (node != NIL) {
        if (node->m_key_.first == key.first) {
            nodeToBeDeleted = node;
        }
        if (node->m_key_.first <= key.first) {
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
        transplantNode(nodeToBeDeleted, x);
    } else if (nodeToBeDeleted->m_right_child_ == NIL) {
        x = nodeToBeDeleted->m_left_child_;
        transplantNode(nodeToBeDeleted, x);
    } else {
        y = nodeToBeDeleted->m_right_child_->getMinNode();
        original_color = y->m_color_;
        x = y->m_right_child_;
        if (y->m_parent_ == nodeToBeDeleted) {
            x->m_parent_ = y;
        } else {
            transplantNode(y, y->m_right_child_);
            y->m_right_child_ = nodeToBeDeleted->m_right_child_;
            y->m_right_child_->m_parent_ = y;
        }
        transplantNode(nodeToBeDeleted, y);
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

template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::balanceAfterDelete(node_type* x) {
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

template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::transplantNode(node_type* u, node_type* v) {
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
template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::erase(iterator position) {
    value_type key = *position;
    unSetEndNode();
    deleteKey(key);
    setBeginNode();
    setEndNode();
}

template <class Key, class T, class Compare, class Alloc>
typename tree<Key, T, Compare, Alloc>::size_type
tree<Key, T, Compare, Alloc>::erase(const key_type& k) {
    if (find(k).getNode() == NIL) {
        return 0;
    }
    value_type key = ft::make_pair(k, T());
    unSetEndNode();
    deleteKey(key);
    setBeginNode();
    setEndNode();
    return 1;
}

template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::erase(iterator first, iterator last) {
    while (first != last) {
        erase(first++);
    }
}

// swap
template <class Key, class T, class Compare, class Alloc>
void tree<Key, T, Compare, Alloc>::swap(tree& x) {
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
template <class Key, class T, class Compare, class Alloc>
typename tree<Key, T, Compare, Alloc>::iterator
tree<Key, T, Compare, Alloc>::find(const key_type& k) {
    node_type* node = getRoot();
    while (node != NIL && node != m_end_) {
        if (k == node->m_key_.first) {
            return iterator(node);
        } else if (k < node->m_key_.first) {
            node = node->m_left_child_;
        } else {
            node = node->m_right_child_;
        }
    }
    return iterator(NIL);
}

template <class Key, class T, class Compare, class Alloc>
typename tree<Key, T, Compare, Alloc>::const_iterator
tree<Key, T, Compare, Alloc>::find(const key_type& k) const {
    node_type* node = getRoot();
    while (node != NIL && node != m_end_) {
        if (k == node->m_key_.first) {
            return const_iterator(node);
        } else if (k < node->m_key_.first) {
            node = node->m_left_child_;
        } else {
            node = node->m_right_child_;
        }
    }
    return const_iterator(NIL);
}

// count
template <class Key, class T, class Compare, class Alloc>
typename tree<Key, T, Compare, Alloc>::size_type
tree<Key, T, Compare, Alloc>::count(const key_type& k) const {
    if (find(k).getNode() == NIL) {
        return 0;
    }
    return 1;
}

// lower_bound
template <class Key, class T, class Compare, class Alloc>
typename tree<Key, T, Compare, Alloc>::iterator
tree<Key, T, Compare, Alloc>::lower_bound(const key_type& k) {
    iterator it = begin();
    while (it != end()) {
        if (!m_key_compare_(it->first, k)) {
            return it;
        }
        ++it;
    }
    return it;
}

template <class Key, class T, class Compare, class Alloc>
typename tree<Key, T, Compare, Alloc>::const_iterator
tree<Key, T, Compare, Alloc>::lower_bound(const key_type& k) const {
    const_iterator it = begin();
    while (it != end()) {
        if (!m_key_compare_(it->first, k)) {
            return it;
        }
        ++it;
    }
    return it;
}

// upper_bound
template <class Key, class T, class Compare, class Alloc>
typename tree<Key, T, Compare, Alloc>::iterator
tree<Key, T, Compare, Alloc>::upper_bound(const key_type& k) {
    iterator it = begin();
    while (it != end()) {
        if (m_key_compare_(k, it->first)) {
            return it;
        }
        ++it;
    }
    return it;
}

template <class Key, class T, class Compare, class Alloc>
typename tree<Key, T, Compare, Alloc>::const_iterator
tree<Key, T, Compare, Alloc>::upper_bound(const key_type& k) const {
    const_iterator it = begin();
    while (it != end()) {
        if (m_key_compare_(k, it->first)) {
            return it;
        }
        ++it;
    }
    return it;
}

// equal_range
template <class Key, class T, class Compare, class Alloc>
ft::pair<typename tree<Key, T, Compare, Alloc>::const_iterator,
         typename tree<Key, T, Compare, Alloc>::const_iterator>
tree<Key, T, Compare, Alloc>::equal_range(const key_type& k) const {
    return ft::make_pair(lower_bound(k), upper_bound(k));
}

template <class Key, class T, class Compare, class Alloc>
ft::pair<typename tree<Key, T, Compare, Alloc>::iterator,
         typename tree<Key, T, Compare, Alloc>::iterator>
tree<Key, T, Compare, Alloc>::equal_range(const key_type& k) {
    return ft::make_pair(lower_bound(k), upper_bound(k));
}

}  // namespace ft

#endif  // TREE_HPP_
