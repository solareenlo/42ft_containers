/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 05:35:30 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/02 06:32:42 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <string>
#include <typeinfo>

#ifndef NAMESPACE_FT
#include <iterator>
#include <vector>
namespace ft = std;
#else
#include "iterator.hpp"
#include "utility.hpp"
#include "vector.hpp"
#endif

template <typename T>
void outputVec(ft::vector<T> v) {
    ft::vector<int>::iterator it;
    for (it = v.begin(); it < v.end(); it++) {
        std::cout << ' ' << *it;
    }
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
    // ft::reverse_iterator<map_iter>              rev_iterator(numbers.end());
    // for (; rev_iterator != rev_end; ++rev_iterator)
    //     std::cout << rev_iterator->first << ' ' << rev_iterator->second <<
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
    std::cout << "<< VECTOR TEST >>" << std::endl;
    std::cout << std::endl;

    std::cout << "<< PAIR TEST >>" << std::endl;
    testMakePair();
    testPairRelationalOperators();
    testPairOperatoEqual();
    testPairConstructor();
    std::cout << std::endl;

    std::cout << "<< REVERSE_ITERATOR >>" << std::endl;
    testReverseIteratorOperatorMinusNonmember();
    testReverseIteratorOperatorPlusNonmember();
    testReverseIteratorRelationalOperators();
    testReverseIteratorOperatorOffset();
    testReverseIteratorOperatorPointer();
    testReverseIteratorOperatorMinusEqual();
    testReverseIteratorOperatorMinusMinus();
    testReverseIteratorOperatorMinus();
    testReverseIteratorOperatorPlusEqual();
    testReverseIteratorOperatorPlusPlus();
    testReverseIteratorOperatorPlus();
    testReverseIteratorOperatorAsterisk();
    testReverseIteratorBase();
    testReverseIteratorConstructor();
    std::cout << std::endl;

    std::cout << "<< ITERATOR_TRAITS TEST >>" << std::endl;
    testIteratorTraits();
    std::cout << std::endl;
    return 0;
}
