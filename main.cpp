/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 05:35:30 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/01 18:34:18 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#include <iostream>
#include <typeinfo>
#include <vector>

#include "vector.hpp"

template <typename T>
void outputVec(ft::vector<T> v) {
    ft::vector<int>::iterator it;
    for (it = v.begin(); it < v.end(); it++) {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
}

void testVectorGetAllocator() {
    ft::vector<int>  v;
    std::vector<int> std_v;
    int*             p;
    int*             std_p;
    unsigned int     i;

    p = v.get_allocator().allocate(5);
    std_p = std_v.get_allocator().allocate(5);

    for (i = 0; i < 5; i++) {
        v.get_allocator().construct(&p[i], i);
    }
    for (i = 0; i < 5; i++) {
        std_v.get_allocator().construct(&std_p[i], i);
    }
    std::cout << (ft::equal(v.begin(), v.end(), std_v.begin()) == true)
              << std::endl;

    for (i = 0; i < 5; i++) {
        v.get_allocator().destroy(&p[i]);
    }
    v.get_allocator().deallocate(p, 5);

    for (i = 0; i < 5; i++) {
        std_v.get_allocator().destroy(&p[i]);
    }
    std_v.get_allocator().deallocate(std_p, 5);
}

void testVectorInsert() {
    ft::vector<int>           v(3, 100);
    ft::vector<int>::iterator it;
    outputVec(v);

    it = v.begin();
    it = v.insert(it, 200);
    outputVec(v);

    v.insert(it, 2, 300);
    outputVec(v);

    it = v.begin();

    ft::vector<int> anothervector(2, 400);
    v.insert(it + 2, anothervector.begin(), anothervector.end());
    outputVec(v);

    int myarray[] = {501, 502, 503};
    v.insert(v.begin(), myarray, myarray + 3);
    outputVec(v);
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

void testVectorRbeginRend() {
    ft::vector<int>                   v(5);
    ft::vector<int>::reverse_iterator rit = v.rbegin();

    std::cout << v.end() - v.begin() << std::endl;
    std::cout << v.rend() - v.rbegin() << std::endl;
    std::cout << *v.begin() << std::endl;
    std::cout << *(v.end() - 1) << std::endl;
    std::cout << *v.rbegin() << std::endl;
    std::cout << *(v.rend() - 1) << std::endl;
    int i = 0;
    for (; rit != v.rend(); ++rit) {
        *rit = ++i;
    }

    i = 5;
    for (ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
        --i;
    }
    std::cout << std::endl;
}

void testVectorPushback() {
    std::vector<int> std_v;
    ft::vector<int>  v;
    int              n = 3;
    for (int i = 0; i < n; i++) {
        std_v.push_back(i);
        v.push_back(i);
    }
    for (int i = 0; i < n; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
    ft::equal(v.begin(), v.end(), v.begin());
}

void testIteratorTraits() {
    typedef ft::iterator_traits<int*> traits;
    if (typeid(traits::iterator_category) ==
        typeid(ft::random_access_iterator_tag)) {
        std::cout << "int* is a random-access iterator" << std::endl;
    }
    typedef ft::iterator_traits<int*> traits2;
    if (typeid(traits2::iterator_category) ==
        typeid(ft::random_access_iterator_tag)) {
        std::cout << "int* is a random-access iterator" << std::endl;
    }
}

void testVectorBegin() {
    std::vector<int> myvector;
    for (int i = 1; i <= 5; i++) myvector.push_back(i);

    std::cout << "myvector contains:";
    for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end();
         ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

void testVectorOperatorEqual() {
    std::vector<int> foo(3, 0);
    std::vector<int> bar(5, 0);

    bar = foo;
    foo = std::vector<int>();

    std::cout << "Size of foo: " << int(foo.size()) << '\n';
    std::cout << "Size of bar: " << int(bar.size()) << '\n';
}

void testVectorConstructor() {
    std::vector<int> first;
    std::vector<int> second(4, 100);
    std::vector<int> third(second.begin(), second.end());
    std::vector<int> fourth(third);

    int              myints[] = {16, 2, 77, 29};
    std::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

    std::cout << "The contents of fifth are:";
    for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}

int main() {
    testVectorGetAllocator();
    testVectorInsert();
    testVectorAssign();
    testVectorRbeginRend();
    testVectorPushback();
    testIteratorTraits();
    testVectorBegin();
    testVectorOperatorEqual();
    testVectorConstructor();
    return 0;
}
