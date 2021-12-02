/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 05:35:30 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/02 10:09:47 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>

#ifndef NAMESPACE_FT
#include <functional>
#include <iterator>
#include <vector>
namespace ft = std;
#else
#include "algorithm.hpp"
#include "functional.hpp"
#include "iterator.hpp"
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
    int myarray[] = {501, 502, 503};
    v.insert(v.begin(), myarray, myarray + 3);
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
    int myints[] = {1776, 7, 4};
    third.assign(myints, myints + 3);
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
    ft::vector<int> myints;
    std::cout << "0. size: " << myints.size() << '\n';
    for (int i = 0; i < 10; i++) myints.push_back(i);
    std::cout << "1. size: " << myints.size() << '\n';
    myints.insert(myints.end(), 10, 100);
    std::cout << "2. size: " << myints.size() << '\n';
    myints.pop_back();
    std::cout << "3. size: " << myints.size() << '\n';
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
    int             myints[] = {16, 2, 77, 29};
    ft::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
    std::cout << "The contents of fifth are:";
    for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

void testMakePair() {
    ft::pair<int, int> foo;
    ft::pair<int, int> bar;
    foo = ft::make_pair(10, 20);
    bar = ft::make_pair(10.5, 'A');
    std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
    std::cout << "bar: " << bar.first << ", " << bar.second << '\n';
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

void testCopy() {
    int             myints[] = {10, 20, 30, 40, 50, 60, 70};
    ft::vector<int> v(7);
    ft::copy(myints, myints + 7, v.begin());
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
    ft::swap(x, y);
    ft::vector<int> foo(4);
    ft::vector<int> bar(4, 10);
    ft::swap(foo, bar);
    outputVec(foo);
    outputVec(bar);
}

bool mypredicate(int i, int j) { return (i == j); }
void testEqual() {
    int             myints[] = {20, 40, 60, 80, 100};
    ft::vector<int> v(myints, myints + 5);
    if (ft::equal(v.begin(), v.end(), myints))
        std::cout << "The contents of both sequences are equal.\n";
    else
        std::cout << "The contents of both sequences differ.\n";
    v[3] = 81;
    if (ft::equal(v.begin(), v.end(), myints, mypredicate))
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

void testIteratorTraits() {
    typedef ft::iterator_traits<int*> traits;
    if (typeid(traits::iterator_category) ==
        typeid(ft::random_access_iterator_tag))
        std::cout << "int* is a random-access iterator";
}

int main() {
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
    testIteratorTraits();
    std::cout << std::endl;
    return 0;
}
