/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 05:35:30 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/17 22:01:37 by tayamamo         ###   ########.fr       */
/* ************************************************************************** */

#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>

#ifndef NAMESPACE_FT
#include <deque>
#include <functional>
#include <iterator>
#include <map>
#include <vector>
namespace ft = std;
#else
#include "algorithm.hpp"
#include "deque.hpp"
#include "functional.hpp"
#include "iterator.hpp"
#include "map.hpp"
#include "tree.hpp"
#include "utility.hpp"
#include "vector.hpp"
#endif

template <typename T>
void outputVec(ft::vector<T> v) {
    typedef typename ft::vector<T>::iterator iterator;
    iterator                                 it;
    std::cout << "v contains:";
    for (it = v.begin(); it < v.end(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
}

void testLess() {
    int foo[] = {10, 20, 5, 15, 25};
    int bar[] = {15, 10, 20};
    std::sort(foo, foo + 5, ft::less<int>());
    std::sort(bar, bar + 3, ft::less<int>());
    if (std::includes(foo, foo + 5, bar, bar + 3, ft::less<int>()))
        std::cout << "foo includes bar.\n";
}

struct Compare : public ft::binary_function<int, int, bool> {
    bool operator()(int a, int b) { return (a == b); }
};
void testBinaryFunction() {
    Compare                       Compare_object;
    Compare::first_argument_type  input1 = 1;
    Compare::second_argument_type input2 = 2;
    Compare::result_type          result;

    result = Compare_object(input1, input2);

    std::cout << "Numbers " << input1 << " and " << input2;
    if (result)
        std::cout << " are equal.\n";
    else
        std::cout << " are not equal.\n";
}

void testVectorSwapNonMember() {
    ft::vector<int> foo(3, 100);
    ft::vector<int> bar(5, 200);
    foo.swap(bar);
    std::cout << "foo contains:";
    for (ft::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    std::cout << "bar contains:";
    for (ft::vector<int>::iterator it = bar.begin(); it != bar.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

void testVectorRelationalOperators() {
    ft::vector<int> foo(3, 100);
    ft::vector<int> bar(2, 200);
    if (foo == bar) std::cout << "foo and bar are equal\n";
    if (foo != bar) std::cout << "foo and bar are not equal\n";
    if (foo < bar) std::cout << "foo is less than bar\n";
    if (foo > bar) std::cout << "foo is greater than bar\n";
    if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
    if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
}

void testVectorGetAllocator() {
    ft::vector<int> v;
    int*            p;
    unsigned int    i;
    p = v.get_allocator().allocate(5);
    for (i = 0; i < 5; i++) v.get_allocator().construct(&p[i], i);
    std::cout << "The allocated array contains:";
    for (i = 0; i < 5; i++) std::cout << ' ' << p[i];
    std::cout << '\n';
    for (i = 0; i < 5; i++) v.get_allocator().destroy(&p[i]);
    v.get_allocator().deallocate(p, 5);
}

void testVectorClear() {
    ft::vector<int> v;
    v.push_back(100);
    v.push_back(200);
    v.push_back(300);
    std::cout << "v contains:";
    for (unsigned i = 0; i < v.size(); i++) std::cout << ' ' << v[i];
    std::cout << '\n';
    v.clear();
    v.push_back(1101);
    v.push_back(2202);
    std::cout << "v contains:";
    for (unsigned i = 0; i < v.size(); i++) std::cout << ' ' << v[i];
    std::cout << '\n';
}

void testVectorSwap() {
    ft::vector<int> foo(3, 100);
    ft::vector<int> bar(5, 200);
    foo.swap(bar);
    std::cout << "foo contains:";
    for (unsigned i = 0; i < foo.size(); i++) std::cout << ' ' << foo[i];
    std::cout << '\n';
    std::cout << "bar contains:";
    for (unsigned i = 0; i < bar.size(); i++) std::cout << ' ' << bar[i];
    std::cout << '\n';
}

void testVectorErase() {
    ft::vector<int> v;
    for (int i = 1; i <= 10; i++) v.push_back(i);
    v.erase(v.begin() + 5);
    v.erase(v.begin(), v.begin() + 3);
    std::cout << "v contains:";
    for (unsigned i = 0; i < v.size(); ++i) std::cout << ' ' << v[i];
    std::cout << '\n';
}

void testVectorInsert() {
    ft::vector<int>           v(3, 100);
    ft::vector<int>::iterator it;
    it = v.begin();
    it = v.insert(it, 200);
    v.insert(it, 2, 300);
    it = v.begin();
    ft::vector<int> anothervector(2, 400);
    v.insert(it + 2, anothervector.begin(), anothervector.end());
    int arr[] = {501, 502, 503};
    v.insert(v.begin(), arr, arr + 3);
    outputVec(v);
}

void testVectorPopBack() {
    ft::vector<int> v;
    int             sum(0);
    v.push_back(100);
    v.push_back(200);
    v.push_back(300);
    while (!v.empty()) {
        sum += v.back();
        v.pop_back();
    }
    std::cout << "The elements of v add up to " << sum << '\n';
}

void testVectorPushBack() {
    ft::vector<int> v;
    int             n = 100;
    for (int i = 0; i < n; i++) {
        v.push_back(i);
    }
    std::cout << "v stores " << int(v.size()) << " numbers.\n";
}

void testVectorAssign() {
    ft::vector<int> first;
    ft::vector<int> second;
    ft::vector<int> third;
    first.assign(7, 100);
    ft::vector<int>::iterator it;
    it = first.begin() + 1;
    second.assign(it, first.end() - 1);
    int ints[] = {1776, 7, 4};
    third.assign(ints, ints + 3);
    std::cout << "Size of first: " << int(first.size()) << '\n';
    std::cout << "Size of second: " << int(second.size()) << '\n';
    std::cout << "Size of third: " << int(third.size()) << '\n';
}

void testVectorBack() {
    ft::vector<int> v;
    v.push_back(10);
    while (v.back() != 0) {
        v.push_back(v.back() - 1);
    }
    std::cout << "v contains:";
    for (unsigned i = 0; i < v.size(); i++) std::cout << ' ' << v[i];
    std::cout << '\n';
}

void testVectorFront() {
    ft::vector<int> v;
    v.push_back(78);
    v.push_back(16);
    v.front() -= v.back();
    std::cout << "v.front() is now " << v.front() << '\n';
}

void testVectorAt() {
    ft::vector<int> v(10);
    for (unsigned i = 0; i < v.size(); i++) v.at(i) = i;
    std::cout << "v contains:";
    for (unsigned i = 0; i < v.size(); i++) std::cout << ' ' << v.at(i);
    std::cout << '\n';
}

void testVectorOperatorReference() {
    ft::vector<int>            v(10);
    ft::vector<int>::size_type sz = v.size();
    for (unsigned i = 0; i < sz; i++) v[i] = i;
    for (unsigned i = 0; i < sz / 2; i++) {
        int temp;
        temp = v[sz - 1 - i];
        v[sz - 1 - i] = v[i];
        v[i] = temp;
    }
    std::cout << "v contains:";
    for (unsigned i = 0; i < sz; i++) std::cout << ' ' << v[i];
    std::cout << '\n';
}

void testVectorReserve() {
    ft::vector<int>::size_type sz;
    ft::vector<int>            foo;
    sz = foo.capacity();
    std::cout << "making foo grow:\n";
    for (int i = 0; i < 100; ++i) {
        foo.push_back(i);
        if (sz != foo.capacity()) {
            sz = foo.capacity();
            std::cout << "capacity changed: " << sz << '\n';
        }
    }
    ft::vector<int> bar;
    sz = bar.capacity();
    bar.reserve(100);
    std::cout << "making bar grow:\n";
    for (int i = 0; i < 100; ++i) {
        bar.push_back(i);
        if (sz != bar.capacity()) {
            sz = bar.capacity();
            std::cout << "capacity changed: " << sz << '\n';
        }
    }
}

void testVectorEmpty() {
    ft::vector<int> v;
    int             sum(0);
    for (int i = 1; i <= 10; i++) v.push_back(i);
    while (!v.empty()) {
        sum += v.back();
        v.pop_back();
    }
    std::cout << "total: " << sum << '\n';
}

void testVectorCapacity() {
    ft::vector<int> v;
    for (int i = 0; i < 100; i++) v.push_back(i);
    std::cout << "size: " << static_cast<int>(v.size()) << '\n';
    std::cout << "capacity: " << static_cast<int>(v.capacity()) << '\n';
    std::cout << "max_size: " << static_cast<int>(v.max_size()) << '\n';
}

void testVectorResize() {
    ft::vector<int> v;
    for (int i = 1; i < 10; i++) v.push_back(i);
    v.resize(5);
    v.resize(8, 100);
    v.resize(12);
    std::cout << "v contains:";
    for (int i = 0; i < static_cast<int>(v.size()); i++)
        std::cout << ' ' << v[i];
    std::cout << '\n';
}

void testVectorMaxSize() {
    ft::vector<int> v;
    for (int i = 0; i < 100; i++) v.push_back(i);
    std::cout << "size: " << v.size() << "\n";
    std::cout << "capacity: " << v.capacity() << "\n";
    std::cout << "max_size: " << v.max_size() << "\n";
}

void testVectorSize() {
    ft::vector<int> ints;
    std::cout << "0. size: " << ints.size() << '\n';
    for (int i = 0; i < 10; i++) ints.push_back(i);
    std::cout << "1. size: " << ints.size() << '\n';
    ints.insert(ints.end(), 10, 100);
    std::cout << "2. size: " << ints.size() << '\n';
    ints.pop_back();
    std::cout << "3. size: " << ints.size() << '\n';
}

void testVectorRend() {
    ft::vector<int>                   v(5);
    ft::vector<int>::reverse_iterator rit = v.rbegin();
    int                               i = 0;
    for (rit = v.rbegin(); rit != v.rend(); ++rit) *rit = ++i;
    outputVec(v);
}

void testVectorRbegin() {
    ft::vector<int>                   v(5);
    int                               i = 0;
    ft::vector<int>::reverse_iterator rit = v.rbegin();
    for (; rit != v.rend(); ++rit) *rit = ++i;
    outputVec(v);
}

void testVectorEnd() {
    ft::vector<int> v;
    for (int i = 1; i <= 5; i++) v.push_back(i);
    outputVec(v);
}

void testVectorBegin() {
    ft::vector<int> v;
    for (int i = 1; i <= 5; i++) v.push_back(i);
    outputVec(v);
}

void testVectorOperatorEqual() {
    ft::vector<int> foo(3, 0);
    ft::vector<int> bar(5, 0);
    bar = foo;
    foo = ft::vector<int>();
    std::cout << "Size of foo: " << int(foo.size()) << '\n';
    std::cout << "Size of bar: " << int(bar.size()) << '\n';
}

void testVectorConstructor() {
    ft::vector<int> first;
    ft::vector<int> second(4, 100);
    ft::vector<int> third(second.begin(), second.end());
    ft::vector<int> fourth(third);
    if (ft::equal(third.begin(), third.end(), fourth.begin())) {
        std::cout << "third == fourth" << std::endl;
    } else {
        std::cout << "third != fourth" << std::endl;
    }
    int             ints[] = {16, 2, 77, 29};
    ft::vector<int> fifth(ints, ints + sizeof(ints) / sizeof(int));
    std::cout << "The contents of fifth are:";
    for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

void testMakePair() {
    ft::pair<int, int>                 foo;
    ft::pair<int, int>                 bar;
    ft::pair<std::string, std::string> baz;
    foo = ft::make_pair(10, 20);
    bar = ft::make_pair(10.5, 'A');
    baz = ft::make_pair("hello", "world");
    std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
    std::cout << "bar: " << bar.first << ", " << bar.second << '\n';
    std::cout << "baz: " << baz.first << ", " << baz.second << '\n';
}

void testPairRelationalOperators() {
    ft::pair<int, char> foo(10, 'z');
    ft::pair<int, char> bar(20, 'a');
    if (foo == bar) std::cout << "foo and bar are equal\n";
    if (foo != bar) std::cout << "foo and bar are not equal\n";
    if (foo < bar) std::cout << "foo is less than bar\n";
    if (foo > bar) std::cout << "foo is greater than bar\n";
    if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
    if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
}

void testPairOperatoEqual() {
    ft::pair<std::string, int> planet, homeplanet;
    planet = ft::make_pair("Earth", 6371);
    homeplanet = planet;
    std::cout << "Home planet: " << homeplanet.first << '\n';
    std::cout << "Planet size: " << homeplanet.second << '\n';
}

void testFill() {
    ft::vector<int> v(8);
    ft::fill(v.begin(), v.begin() + 4, 5);
    ft::fill(v.begin() + 3, v.end() - 2, 8);
    std::cout << "v contains:";
    for (ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
}

void testCopyBackward() {
    ft::vector<int> v;
    for (int i = 1; i <= 5; i++) {
        v.push_back(i * 10);
    }
    v.resize(v.size() + 3);
    ft::copy_backward(v.begin(), v.begin() + 5, v.end());
    std::cout << "v contains:";
    for (ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
}

void testCopy() {
    int             ints[] = {10, 20, 30, 40, 50, 60, 70};
    ft::vector<int> v(7);
    ft::copy(ints, ints + 7, v.begin());
    outputVec(v);
}

void testMax() {
    std::cout << "max(1,2)==" << ft::max(1, 2) << '\n';
    std::cout << "max(2,1)==" << ft::max(2, 1) << '\n';
    std::cout << "max('a','z')==" << ft::max('a', 'z') << '\n';
    std::cout << "max(3.14,2.73)==" << ft::max(3.14, 2.73) << '\n';
}

void testMin() {
    std::cout << "min(1,2)==" << ft::min(1, 2) << '\n';
    std::cout << "min(2,1)==" << ft::min(2, 1) << '\n';
    std::cout << "min('a','z')==" << ft::min('a', 'z') << '\n';
    std::cout << "min(3.14,2.72)==" << ft::min(3.14, 2.72) << '\n';
}

void testSwap() {
    int x = 10, y = 20;
    std::cout << "x: " << x << ", y: " << y << std::endl;
    ft::swap(x, y);
    std::cout << "x: " << x << ", y: " << y << std::endl;
    ft::vector<int> foo(4);
    ft::vector<int> bar(4, 10);
    ft::swap(foo, bar);
    outputVec(foo);
    outputVec(bar);
}

bool mypredicate(int i, int j) { return (i == j); }
void testEqual() {
    int             ints[] = {20, 40, 60, 80, 100};
    ft::vector<int> v(ints, ints + 5);
    if (ft::equal(v.begin(), v.end(), ints))
        std::cout << "The contents of both sequences are equal.\n";
    else
        std::cout << "The contents of both sequences differ.\n";
    v[3] = 81;
    if (ft::equal(v.begin(), v.end(), ints, mypredicate))
        std::cout << "The contents of both sequences are equal.\n";
    else
        std::cout << "The contents of both sequences differ.\n";
}

bool mycomp(char c1, char c2) { return std::tolower(c1) < std::tolower(c2); }
void testLexicographicalCompare() {
    char foo[] = "Apple";
    char bar[] = "apartment";
    std::cout << std::boolalpha;
    std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";
    std::cout << "Using default comparison (operator<): ";
    std::cout << ft::lexicographical_compare(foo, foo + 5, bar, bar + 9);
    std::cout << '\n';
    std::cout << "Using mycomp as comparison object: ";
    std::cout << ft::lexicographical_compare(foo, foo + 5, bar, bar + 9,
                                             mycomp);
    std::cout << '\n';
}

void testPairConstructor() {
    ft::pair<std::string, double> product1;
    ft::pair<std::string, double> product2("tomatoes", 2.3);
    ft::pair<std::string, double> product3(product2);
    product1 = ft::make_pair("lightbulbs", 9.9);
    product2.first = "42Tokyo";
    product2.second = 42.42;
    std::cout << "The price of " << product1.first << " is $" << product1.second
              << '\n';
    std::cout << "The price of " << product2.first << " is $" << product2.second
              << '\n';
    std::cout << "The price of " << product3.first << " is $" << product3.second
              << '\n';
}

void testReverseIteratorOperatorMinusNonmember() {
    ft::vector<int> v;
    for (int i = 0; i < 10; i++) v.push_back(i);
    ft::reverse_iterator<ft::vector<int>::iterator> from, until;
    from = v.rbegin();
    until = v.rend();
    std::cout << "v has " << (until - from) << " elements.\n";
}

void testReverseIteratorOperatorPlusNonmember() {
    ft::vector<int> v;
    for (int i = 0; i < 10; i++) v.push_back(i);
    typedef ft::vector<int>::iterator iter_type;
    ft::reverse_iterator<iter_type>   rev_it;
    rev_it = 3 + v.rbegin();
    std::cout << "The fourth element from the end is: " << *rev_it << '\n';
}

void testReverseIteratorRelationalOperators() {
    ft::vector<int> v;
    for (int i = 0; i < 10; i++) v.push_back(i);
    typedef ft::vector<int>::iterator iter_type;
    iter_type                         from(v.begin());
    iter_type                         until(v.end());
    ft::reverse_iterator<iter_type>   rev_until(from);
    ft::reverse_iterator<iter_type>   rev_from(until);
    std::cout << "v:";
    while (rev_from != rev_until) std::cout << ' ' << *rev_from++;
    std::cout << '\n';
}

void testReverseIteratorOperatorOffset() {
    ft::vector<int> v;
    for (int i = 0; i < 10; i++) v.push_back(i);
    typedef ft::vector<int>::iterator iter_type;
    ft::reverse_iterator<iter_type>   rev_iterator = v.rbegin();
    std::cout << "The fourth element from the end is: " << rev_iterator[3]
              << '\n';
}

void testReverseIteratorOperatorPointer() {
    // std::map<int, std::string> numbers;
    // numbers.insert(std::make_pair(1, "one"));
    // numbers.insert(std::make_pair(2, "two"));
    // numbers.insert(std::make_pair(3, "three"));
    // typedef std::map<int, std::string>::iterator map_iter;
    // ft::reverse_iterator<map_iter>              rev_end(numbers.begin());
    // ft::reverse_iterator<map_iter> rev_iterator(numbers.end()); for (;
    // rev_iterator != rev_end; ++rev_iterator)
    //     std::cout << rev_iterator->first << ' ' << rev_iterator->second
    //     <<
    //     '\n';
}

void testReverseIteratorOperatorMinusEqual() {
    ft::vector<int> v;
    for (int i = 0; i < 10; i++) v.push_back(i);
    typedef ft::vector<int>::iterator iter_type;
    ft::reverse_iterator<iter_type>   rev_iterator = v.rend();
    rev_iterator -= 4;
    std::cout << "rev_iterator now points to: " << *rev_iterator << '\n';
}

void testReverseIteratorOperatorMinusMinus() {
    ft::vector<int> v;
    for (int i = 0; i < 10; i++) v.push_back(i);
    typedef ft::vector<int>::iterator iter_type;
    ft::reverse_iterator<iter_type>   rev_begin(v.end());
    ft::reverse_iterator<iter_type>   rev_end(v.begin());
    ft::reverse_iterator<iter_type>   rev_iterator = rev_begin;
    while (rev_iterator != rev_end) std::cout << *rev_iterator++ << ' ';
    std::cout << '\n';
    while (rev_iterator != rev_begin) std::cout << *(--rev_iterator) << ' ';
    std::cout << '\n';
}

void testReverseIteratorOperatorMinus() {
    ft::vector<int> v;
    for (int i = 0; i < 10; i++) v.push_back(i);
    typedef ft::vector<int>::iterator iter_type;
    ft::reverse_iterator<iter_type>   rev_iterator;
    rev_iterator = v.rend() - 3;
    std::cout << "v.rend()-3 points to: " << *rev_iterator << '\n';
}

void testReverseIteratorOperatorPlusEqual() {
    ft::vector<int> v;
    for (int i = 0; i < 10; i++) v.push_back(i);
    typedef ft::vector<int>::iterator iter_type;
    ft::reverse_iterator<iter_type>   rev_iterator = v.rbegin();
    rev_iterator += 2;
    std::cout << "The third element from the end is: " << *rev_iterator << '\n';
}

void testReverseIteratorOperatorPlusPlus() {
    ft::vector<int> v;
    for (int i = 0; i < 10; i++) v.push_back(i);
    typedef ft::vector<int>::iterator iter_type;
    iter_type                         from(v.begin());
    iter_type                         until(v.end());
    ft::reverse_iterator<iter_type>   rev_until(from);
    ft::reverse_iterator<iter_type>   rev_from(until);
    std::cout << "v:";
    while (rev_from != rev_until) {
        std::cout << ' ' << *rev_from;
        ++rev_from;
    }
    std::cout << '\n';
}

void testReverseIteratorOperatorPlus() {
    ft::vector<int> v;
    for (int i = 0; i < 10; i++) v.push_back(i);
    typedef ft::vector<int>::iterator iter_type;
    ft::reverse_iterator<iter_type>   rev_it;
    rev_it = v.rbegin() + 3;
    std::cout << "The fourth element from the end is: " << *rev_it << '\n';
}

void testReverseIteratorOperatorAsterisk() {
    ft::vector<int> v;
    for (int i = 0; i < 10; i++) v.push_back(i);
    typedef ft::vector<int>::iterator iter_type;
    iter_type                         from(v.begin());
    iter_type                         until(v.end());
    ft::reverse_iterator<iter_type>   rev_until(from);
    ft::reverse_iterator<iter_type>   rev_from(until);
    std::cout << "v:";
    while (rev_from != rev_until) std::cout << ' ' << *rev_from++;
    std::cout << '\n';
}

void testReverseIteratorBase() {
    ft::vector<int> v;
    for (int i = 0; i < 10; i++) v.push_back(i);
    typedef ft::vector<int>::iterator iter_type;
    ft::reverse_iterator<iter_type>   rev_end(v.begin());
    ft::reverse_iterator<iter_type>   rev_begin(v.end());
    std::cout << "v:";
    for (iter_type it = rev_end.base(); it != rev_begin.base(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

void testReverseIteratorConstructor() {
    ft::vector<int> v;
    for (int i = 0; i < 10; i++) v.push_back(i);
    typedef ft::vector<int>::iterator iter_type;
    iter_type                         from(v.begin());
    iter_type                         until(v.end());
    ft::reverse_iterator<iter_type>   rev_until(from);
    ft::reverse_iterator<iter_type>   rev_from(until);
    std::cout << "v:";
    while (rev_from != rev_until) std::cout << ' ' << *rev_from++;
    std::cout << '\n';
}

void testDistance() {
    ft::vector<int> v;
    for (int i = 0; i < 10; i++) {
        v.push_back(i * 10);
    }
    ft::vector<int>::iterator first = v.begin();
    ft::vector<int>::iterator last = v.end();
    std::cout << "The distance is: " << ft::distance(first, last) << '\n';

    ft::map<int, int> m;
    for (int i = 0; i < 3; i++) {
        m[i] = i * 2;
    }
    ft::map<int, int>::iterator first_m = m.begin();
    ft::map<int, int>::iterator last_m = m.end();
    std::cout << "The distance is: " << ft::distance(first_m, last_m) << '\n';
}

void testAdvance() {
    ft::vector<int> v;
    for (int i = 0; i < 10; i++) {
        v.push_back(i * 10);
    }
    ft::vector<int>::iterator it = v.begin();
    ft::advance(it, 5);
    std::cout << "The sixth element in v is: " << *it << '\n';

    ft::map<int, int> m;
    for (int i = 0; i < 10; i++) {
        m[i] = i * 2;
    }
    ft::map<int, int>::iterator it_m = m.begin();
    ft::advance(it_m, 3);
    std::cout << "The fourth element in m is: " << (*it_m).second << '\n';
}

void testIteratorTraits() {
    typedef ft::iterator_traits<int*> traits;
    if (typeid(traits::iterator_category) ==
        typeid(ft::random_access_iterator_tag)) {
        std::cout << "int* is a random-access iterator";
    }
    typedef ft::iterator_traits<ft::vector<int>*> traits_v;
    if (typeid(traits_v::iterator_category) ==
        typeid(ft::random_access_iterator_tag)) {
        std::cout << "vector<int>* is a random-access iterator";
    }
    typedef ft::iterator_traits<ft::map<int, int>*> traits_m;
    if (typeid(traits_m::iterator_category) ==
        typeid(ft::bidirectional_iterator_tag)) {
        std::cout << "map<int, int>* is a bidirectional-access iterator";
    }
}

template <typename T, typename U>
void mapOutput(ft::map<T, U>& m) {
    for (typename ft::map<T, U>::iterator it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << " " << it->second << " ";
    }
    std::cout << std::endl;
}

bool fncomp(char lhs, char rhs) { return lhs < rhs; }
struct classcomp {
    bool operator()(const char& lhs, const char& rhs) const {
        return lhs < rhs;
    }
};
void testMapConstructor() {
    std::cout << "< Test Map Constructor >" << std::endl;
    ft::map<char, int> first;
    first['a'] = 10;
    first['b'] = 30;
    first['c'] = 50;
    first['d'] = 70;
    ft::map<char, int>            second(first.begin(), first.end());
    ft::map<char, int>            third(second);
    ft::map<char, int, classcomp> fourth;
    fourth['a'] = 10;
    fourth['b'] = 30;
    bool (*fn_pt)(char, char) = fncomp;
    ft::map<char, int, bool (*)(char, char)> fifth(fn_pt);
    fifth['c'] = 50;
    fifth['d'] = 70;
    mapOutput(first);
    mapOutput(second);
    mapOutput(third);
}

void testMapOperatorEqual() {
    std::cout << "< Test Map Operator= >" << std::endl;
    ft::map<char, int> first;
    ft::map<char, int> second;
    first['x'] = 8;
    first['y'] = 16;
    first['z'] = 32;
    second = first;
    std::cout << "Size of first: " << first.size() << '\n';
    first = ft::map<char, int>();
    std::cout << "Size of first: " << first.size() << '\n';
    std::cout << "Size of second: " << second.size() << '\n';
}

void testMapBegin() {
    std::cout << "< Test map.begin() >" << std::endl;
    ft::map<char, int> m;
    m['b'] = 100;
    m['a'] = 200;
    m['c'] = 300;
    for (ft::map<char, int>::iterator it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << " => " << it->second << '\n';
    }
}

void testMapEnd() {
    std::cout << "< Test map.end() >" << std::endl;
    ft::map<char, int> m;
    m['c'] = 1;
    m['b'] = 2;
    m['a'] = 3;
    for (ft::map<char, int>::iterator it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << " => " << it->second << '\n';
    }
}

void testMapRbegin() {
    std::cout << "< Test map.rbegin() >" << std::endl;
    ft::map<char, int> m;
    m['x'] = 100;
    m['y'] = 200;
    m['z'] = 300;
    ft::map<char, int>::reverse_iterator rit;
    for (rit = m.rbegin(); rit != m.rend(); ++rit) {
        std::cout << rit->first << " => " << rit->second << '\n';
    }
}

void testMapRend() {
    std::cout << "< Test map.rend() >" << std::endl;
    ft::map<char, int> m;
    m['x'] = 1;
    m['y'] = 2;
    m['z'] = 3;
    ft::map<char, int>::reverse_iterator rit;
    for (rit = m.rbegin(); rit != m.rend(); ++rit) {
        std::cout << rit->first << " => " << rit->second << '\n';
    }
}

void testMapEmpty() {
    std::cout << "< Test map.empty() >" << std::endl;
    ft::map<char, int> m;
    m['a'] = 10;
    m['b'] = 20;
    m['c'] = 30;
    while (!m.empty()) {
        std::cout << m.begin()->first << " => " << m.begin()->second << '\n';
        m.erase(m.begin());
    }
}

void testMapSize() {
    std::cout << "< Test map.size() >" << std::endl;
    ft::map<char, int> m;
    std::cout << "m.size() is " << m.size() << '\n';
    m['a'] = 101;
    std::cout << "m.size() is " << m.size() << '\n';
    m['b'] = 202;
    m['c'] = 302;
    std::cout << "m.size() is " << m.size() << '\n';
}

void testMapMaxSize() {
    std::cout << "< Test map.max_size() >" << std::endl;
    ft::map<int, int> m;
    if (m.max_size() > 1000) {
        for (int i = 0; i < 1000; ++i) {
            m[i] = 0;
        }
        std::cout << "The map contains 1000 elements.\n";
    } else {
        std::cout << "The map could not hold 1000 elements.\n";
    }
}

void testMapOperatorAccessElement() {
    std::cout << "< Test Map Operator[] >" << std::endl;
    ft::map<std::string, char> m;
    m["a"] = 'a';
    m["b"] = 'b';
    m["c"] = m["b"];
    std::cout << "m['a'] is " << m["a"] << '\n';
    std::cout << "m['b'] is " << m["b"] << '\n';
    std::cout << "m['c'] is " << m["c"] << '\n';
    std::cout << "m['d'] is " << m["d"] << '\n';
    std::cout << "m now contains " << m.size() << " elements.\n";
}

void testMapInsert() {
    std::cout << "< Test map::insert >" << std::endl;
    ft::pair<ft::map<char, int>::iterator, bool> ret;
    ft::map<char, int>                           m;
    ret = m.insert(ft::pair<char, int>('b', 100));
    std::cout << ret.first->first << " " << ret.first->second << " "
              << ret.second << std::endl;
    ret = m.insert(ft::pair<char, int>('z', 200));
    std::cout << ret.first->first << " " << ret.first->second << " "
              << ret.second << std::endl;
    ret = m.insert(ft::pair<char, int>('a', 300));
    std::cout << ret.first->first << " " << ret.first->second << " "
              << ret.second << std::endl;
    ret = m.insert(ft::pair<char, int>('a', 400));
    std::cout << ret.first->first << " " << ret.first->second << " "
              << ret.second << std::endl;
    ft::map<char, int>::iterator it;
    it = m.begin();
    it = m.insert(it, ft::pair<char, int>('c', 10));
    std::cout << it->first << " " << it->second << " " << std::endl;
    for (ft::map<char, int>::iterator it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << " " << it->second << " ";
    }
    std::cout << std::endl;
    ft::map<char, int> m2(m.begin(), m.end());
    for (ft::map<char, int>::iterator it = m2.begin(); it != m2.end(); ++it) {
        std::cout << it->first << " " << it->second << " ";
    }
    std::cout << std::endl;
}

void testMapErase() {
    std::cout << "< Test map.erase() >" << std::endl;
    ft::map<char, int>           m;
    ft::map<char, int>::iterator it;
    m['a'] = 10;
    m['b'] = 20;
    m['c'] = 30;
    m['d'] = 40;
    m['e'] = 50;
    m['f'] = 60;
    it = m.find('b');
    std::cout << "m.size(): " << m.size() << std::endl;
    m.erase(it);
    std::cout << "m.size(): " << m.size() << std::endl;
    m.erase('c');
    std::cout << "m.size(): " << m.size() << std::endl;
    it = m.find('e');
    std::cout << it->first << " " << it->second << std::endl;
    m.erase(it, m.end());
    std::cout << "m.size(): " << m.size() << std::endl;
    for (it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << " => " << it->second << '\n';
    }
}

void testMapSwap() {
    std::cout << "< Test map.swap() >" << std::endl;
    ft::map<char, int> foo, bar;
    foo['x'] = 100;
    foo['y'] = 200;
    bar['a'] = 11;
    bar['b'] = 22;
    bar['c'] = 33;
    foo.swap(bar);
    std::cout << "foo contains:\n";
    for (ft::map<char, int>::iterator it = foo.begin(); it != foo.end(); ++it) {
        std::cout << it->first << " => " << it->second << '\n';
    }
    std::cout << "bar contains:\n";
    for (ft::map<char, int>::iterator it = bar.begin(); it != bar.end(); ++it) {
        std::cout << it->first << " => " << it->second << '\n';
    }
}

void testMapClear() {
    std::cout << "< Test map.clear() >" << std::endl;
    ft::map<char, int> m;
    m['x'] = 100;
    m['y'] = 200;
    m['z'] = 300;
    std::cout << "m contains:\n";
    for (ft::map<char, int>::iterator it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << " => " << it->second << '\n';
    }
    m.clear();
    m['a'] = 1101;
    m['b'] = 2202;
    std::cout << "m contains:\n";
    for (ft::map<char, int>::iterator it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << " => " << it->second << '\n';
    }
}

void testMapKeyComp() {
    std::cout << "< Test map.key_comp() >" << std::endl;
    ft::map<char, int>              m;
    ft::map<char, int>::key_compare comp = m.key_comp();
    m['a'] = 100;
    m['b'] = 200;
    m['c'] = 300;
    std::cout << "m contains:\n";
    char                         highest = m.rbegin()->first;
    ft::map<char, int>::iterator it = m.begin();
    do {
        std::cout << it->first << " => " << it->second << '\n';
    } while (comp((*it++).first, highest));
}

void testMapValueComp() {
    std::cout << "< Test map.value_comp() >" << std::endl;
    ft::map<char, int> m;
    m['x'] = 101;
    m['y'] = 202;
    m['z'] = 303;
    std::cout << "m contains:\n";
    ft::pair<char, int>          highest = *m.rbegin();
    ft::map<char, int>::iterator it = m.begin();
    do {
        std::cout << it->first << " => " << it->second << '\n';
    } while (m.value_comp()(*it++, highest));
}

void testMapFind() {
    std::cout << "< Test map.find() >" << std::endl;
    ft::map<char, int>           m;
    ft::map<char, int>::iterator it;
    m['a'] = 50;
    m['b'] = 100;
    m['c'] = 150;
    m['d'] = 200;
    it = m.find('b');
    if (it != m.end()) m.erase(it);
    std::cout << "elements in m:" << '\n';
    std::cout << "a => " << m.find('a')->second << '\n';
    std::cout << "c => " << m.find('c')->second << '\n';
    std::cout << "d => " << m.find('d')->second << '\n';
}

void testMapCount() {
    std::cout << "< Test map.count() >" << std::endl;
    ft::map<char, int> m;
    char               c;
    m['a'] = 101;
    m['c'] = 202;
    m['f'] = 303;
    for (c = 'a'; c < 'h'; c++) {
        std::cout << c;
        if (m.count(c) > 0) {
            std::cout << " is an element of m.\n";
        } else {
            std::cout << " is not an element of m.\n";
        }
    }
}

void testMapLowerBoundUpperBound() {
    std::cout << "< Test map.lower_bound() map.upper_bound() >" << std::endl;
    ft::map<char, int>           m;
    ft::map<char, int>::iterator itLow, itUp;
    m['a'] = 20;
    m['b'] = 40;
    m['c'] = 60;
    m['d'] = 80;
    m['e'] = 100;
    itLow = m.lower_bound('b');
    itUp = m.upper_bound('d');
    std::cout << "itLow->first: " << itLow->first
              << ", itLow->second: " << itLow->second << std::endl;
    std::cout << "itUp->first: " << itUp->first
              << ", itUp->second: " << itUp->second << std::endl;
    m.erase(itLow, itUp);
    for (ft::map<char, int>::iterator it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << " => " << it->second << '\n';
    }
}

void testMapEqualRange() {
    std::cout << "< Test map.equal_range() >" << std::endl;
    ft::map<char, int> m;
    m['a'] = 10;
    m['b'] = 20;
    m['c'] = 30;
    ft::pair<ft::map<char, int>::iterator, ft::map<char, int>::iterator> ret;
    ret = m.equal_range('b');
    std::cout << "lower bound points to: ";
    std::cout << ret.first->first << " => " << ret.first->second << '\n';
    std::cout << "upper bound points to: ";
    std::cout << ret.second->first << " => " << ret.second->second << '\n';
}

void testMapGetAllocator() {
    int                        psize;
    ft::map<char, int>         m;
    ft::pair<const char, int>* p;
    p = m.get_allocator().allocate(5);
    psize = sizeof(ft::map<char, int>::value_type) * 5;
    std::cout << "The allocated array has a size of " << psize << " bytes.\n";
    m.get_allocator().deallocate(p, 5);
}

void testMapIterator() {
    std::cout << "< Test Map Iterator >" << std::endl;
    ft::map<char, int> m;
    m.insert(ft::pair<char, int>('d', 100));
    m.insert(ft::pair<char, int>('b', 100));
    m.insert(ft::pair<char, int>('c', 200));
    m.insert(ft::pair<char, int>('a', 300));
    for (ft::map<char, int>::iterator it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << " " << it->second << " " << std::endl;
    }
    for (ft::map<char, int>::iterator it = --m.end(); it != m.begin(); --it) {
        std::cout << it->first << " " << it->second << " " << std::endl;
    }
}

template <typename T>
void outputDeque(ft::deque<T>& dq) {
    typedef typename ft::deque<T>::iterator iterator;
    for (iterator it = dq.begin(); it != dq.end(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
    if (typeid(typename ft::deque<T>::iterator::value_type) == typeid(int)) {
        std::cout << "int!" << std::endl;
    } else {
        std::cout << "Others!" << std::endl;
    }
}

void testDequeConstructor() {
    std::cout << "<Test deque constructor>" << std::endl;
    ft::deque<int> first;
    ft::deque<int> second(128 * 10, 0);
    ft::deque<int> third(second.begin(), second.end());
    ft::deque<int> fourth(third);
    int            ints[] = {16, 2, 77, 29};
    ft::deque<int> fifth(ints, ints + sizeof(ints) / sizeof(int));

    std::cout << "first:  ";
    outputDeque(first);
    std::cout << "second: ";
    outputDeque(second);
    std::cout << "third:  ";
    outputDeque(third);
    std::cout << "fourth: ";
    outputDeque(fourth);
    std::cout << "fifth:  ";
    outputDeque(fifth);
}

void testDequeOperatorEqual() {
    std::cout << "<Test deque::operator=>" << std::endl;
    ft::deque<int> first(3);
    ft::deque<int> second(5);
    second = first;
    first = ft::deque<int>();
    std::cout << "Size of first: " << static_cast<int>(first.size()) << '\n';
    std::cout << "Size of second: " << static_cast<int>(second.size()) << '\n';
}

void testDequeBeginEnd() {
    std::cout << "<Test deque::begin() & deque::end()>" << std::endl;
    ft::deque<int> dq;
    for (int i = 1; i <= 5; i++) {
        dq.push_back(i);
    }
    std::cout << "dq contains:";
    ft::deque<int>::iterator it = dq.begin();
    while (it != dq.end()) {
        std::cout << ' ' << *it++;
    }
    std::cout << '\n';
}

void testDequeRbeginRend() {
    std::cout << "<Test deque::rbegin() & deque::rend()>" << std::endl;
    ft::deque<int>                   dq(5);
    ft::deque<int>::reverse_iterator rit = dq.rbegin();
    int                              i = 0;
    for (rit = dq.rbegin(); rit != dq.rend(); ++rit) {
        *rit = ++i;
    }
    std::cout << "dq contains:";
    for (ft::deque<int>::iterator it = dq.begin(); it != dq.end(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
}

void testDequeSize() {
    std::cout << "<Test deque::size()>" << std::endl;
    ft::deque<int> dq;
    std::cout << "0. size: " << dq.size() << '\n';
    for (int i = 0; i < 5; i++) {
        dq.push_back(i);
    }
    std::cout << "1. size: " << dq.size() << '\n';
    dq.insert(dq.begin(), 5, 100);
    std::cout << "2. size: " << dq.size() << '\n';
    dq.pop_back();
    std::cout << "3. size: " << dq.size() << '\n';
}

void testDequeMaxSize() {
    std::cout << "<Test deque::max_size()>" << std::endl;
    ft::deque<int> dq;
    if (100 < dq.max_size())
        dq.resize(100);
    else
        std::cout << "That size exceeds the limit.\n";
    std::cout << "dq.size(): " << dq.size() << std::endl;
}

void testDequeEmpty() {
    std::cout << "<Test deque::empty()>" << std::endl;
    ft::deque<int> dq;
    int            sum(0);
    for (int i = 1; i <= 10; i++) {
        dq.push_back(i);
    }
    while (!dq.empty()) {
        sum += dq.front();
        dq.pop_front();
    }
    std::cout << "total: " << sum << '\n';
}

void testDequeOperatorReference() {
    std::cout << "<Test deque::operator[]>" << std::endl;
    std::deque<int>            dq(10);
    std::deque<int>::size_type sz = dq.size();
    for (unsigned i = 0; i < sz; i++) {
        dq[i] = i;
    }
    for (unsigned i = 0; i < sz / 2; i++) {
        int temp;
        temp = dq[sz - 1 - i];
        dq[sz - 1 - i] = dq[i];
        dq[i] = temp;
    }
    std::cout << "dq contains:";
    for (unsigned i = 0; i < sz; i++) {
        std::cout << ' ' << dq[i];
    }
    std::cout << '\n';
}

void testDequeAt() {
    std::cout << "<Test deque::at()>" << std::endl;
    ft::deque<unsigned> dq(10);
    for (unsigned i = 0; i < dq.size(); i++) {
        dq.at(i) = i;
    }
    std::cout << "dq contains:";
    for (unsigned i = 0; i < dq.size(); i++) {
        std::cout << ' ' << dq.at(i);
    }
    std::cout << '\n';
}

void testDequeFront() {
    std::cout << "<Test deque::front()>" << std::endl;
    ft::deque<int> dq;
    dq.push_front(42);
    dq.push_back(20);
    std::cout << "front: " << dq.front() << std::endl;
    std::cout << "back:  " << dq.back() << std::endl;
    dq.front() -= dq.back();
    std::cout << "dq.front() is now " << dq.front() << '\n';
}

void testDequeBack() {
    std::cout << "<Test deque::back()>" << std::endl;
    ft::deque<int> dq;
    dq.push_back(10);
    while (dq.back() != 0) {
        dq.push_back(dq.back() - 1);
    }
    std::cout << "dq contains:";
    for (ft::deque<int>::iterator it = dq.begin(); it != dq.end(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
}

void testDequeAssign() {
    std::cout << "<Test deque::assign()>" << std::endl;
    ft::deque<int> first;
    ft::deque<int> second;
    ft::deque<int> third;
    first.assign(7, 100);
    ft::deque<int>::iterator it;
    it = first.begin() + 1;
    second.assign(it, first.end() - 1);
    int ints[] = {42, 7, 4};
    third.assign(ints, ints + 3);
    std::cout << "Size of first: " << static_cast<int>(first.size()) << '\n';
    std::cout << "Size of second: " << static_cast<int>(second.size()) << '\n';
    std::cout << "Size of third: " << static_cast<int>(third.size()) << '\n';
}

int main() {
    std::cout << "<< DEQUE TEST >>" << std::endl;
    testDequeConstructor();
    testDequeOperatorEqual();
    testDequeBeginEnd();
    testDequeRbeginRend();
    testDequeSize();
    testDequeMaxSize();
    testDequeEmpty();
    testDequeOperatorReference();
    testDequeAt();
    testDequeFront();
    testDequeBack();
    testDequeAssign();
    std::cout << std::endl;

    std::cout << "<< MAP TEST >>" << std::endl;
    testMapConstructor();
    testMapOperatorEqual();
    testMapBegin();
    testMapEnd();
    testMapRbegin();
    testMapRend();
    testMapEmpty();
    testMapSize();
    testMapMaxSize();
    testMapInsert();
    testMapErase();
    testMapSwap();
    testMapClear();
    testMapKeyComp();
    testMapValueComp();
    testMapFind();
    testMapCount();
    testMapLowerBoundUpperBound();
    testMapEqualRange();
    testMapGetAllocator();
    testMapIterator();
    testMapOperatorAccessElement();
    std::cout << std::endl;

    std::cout << "<< FUNCTIONAL TEST >>" << std::endl;
    testBinaryFunction();
    testLess();
    std::cout << std::endl;

    std::cout << "<< VECTOR TEST >>" << std::endl;
    testVectorConstructor();
    testVectorOperatorEqual();
    testVectorBegin();
    testVectorEnd();
    testVectorRbegin();
    testVectorRend();
    testVectorSize();
    testVectorMaxSize();
    testVectorResize();
    testVectorCapacity();
    testVectorEmpty();
    testVectorReserve();
    testVectorOperatorReference();
    testVectorAt();
    testVectorFront();
    testVectorBack();
    testVectorAssign();
    testVectorPushBack();
    testVectorPopBack();
    testVectorInsert();
    testVectorErase();
    testVectorSwap();
    testVectorClear();
    testVectorGetAllocator();
    testVectorRelationalOperators();
    testVectorSwapNonMember();
    std::cout << std::endl;

    std::cout << "<< ALGORITHM TEST >>" << std::endl;
    testFill();
    testCopyBackward();
    testCopy();
    testMax();
    testMin();
    testSwap();
    testEqual();
    testLexicographicalCompare();
    std::cout << std::endl;

    std::cout << "<< PAIR TEST >>" << std::endl;
    testPairConstructor();
    testPairOperatoEqual();
    testPairRelationalOperators();
    testMakePair();
    std::cout << std::endl;

    std::cout << "<< REVERSE_ITERATOR >>" << std::endl;
    testReverseIteratorConstructor();
    testReverseIteratorBase();
    testReverseIteratorOperatorAsterisk();
    testReverseIteratorOperatorPlus();
    testReverseIteratorOperatorPlusPlus();
    testReverseIteratorOperatorPlusEqual();
    testReverseIteratorOperatorMinus();
    testReverseIteratorOperatorMinusMinus();
    testReverseIteratorOperatorMinusEqual();
    testReverseIteratorOperatorPointer();
    testReverseIteratorOperatorOffset();
    testReverseIteratorRelationalOperators();
    testReverseIteratorOperatorPlusNonmember();
    testReverseIteratorOperatorMinusNonmember();
    std::cout << std::endl;

    std::cout << "<< ITERATOR_TRAITS TEST >>" << std::endl;
    testDistance();
    testAdvance();
    testIteratorTraits();
    std::cout << std::endl;
    return 0;
}
