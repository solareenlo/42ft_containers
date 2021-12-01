/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 01:26:10 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/01 17:47:58 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#include "../vector.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

#include "../algorithm.hpp"
#include "catch.hpp"

TEST_CASE("vector::insert", "[vector]") {
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

    std::vector<int>           std_v(3, 100);
    std::vector<int>::iterator it2;

    it2 = std_v.begin();
    it2 = std_v.insert(it2, 200);

    std_v.insert(it2, 2, 300);

    it2 = std_v.begin();

    std::vector<int> anothervector2(2, 400);
    std_v.insert(it2 + 2, anothervector2.begin(), anothervector2.end());

    std_v.insert(std_v.begin(), myarray, myarray + 3);

    REQUIRE(ft::equal(v.begin(), v.end(), std_v.begin()) == true);
}

TEST_CASE("vector::pop_back", "[vector]") {
    ft::vector<int> v;
    int             sum(0);
    v.push_back(100);
    v.push_back(200);
    v.push_back(300);

    while (!v.empty()) {
        sum += v.back();
        v.pop_back();
    }

    REQUIRE(sum == 100 + 200 + 300);
}

TEST_CASE("vector::push_back", "[vector]") {
    ft::vector<int> v;
    int             n = 10;

    for (int i = 0; i < n; i++) {
        v.push_back(i);
    }

    REQUIRE(int(v.size()) == n);
}

TEST_CASE("vector::assign", "[vector]") {
    ft::vector<int> first;
    ft::vector<int> second;
    ft::vector<int> third;

    first.assign(7, 100);

    ft::vector<int>::iterator it;
    it = first.begin() + 1;

    second.assign(it, first.end() - 1);

    int myints[] = {1776, 7, 4};
    third.assign(myints, myints + 3);

    REQUIRE(first.size() == 7);
    REQUIRE(second.size() == 5);
    REQUIRE(third.size() == 3);
}

TEST_CASE("vector::back", "[vector]") {
    ft::vector<int>  v;
    std::vector<int> std_v;

    v.push_back(10);
    std_v.push_back(10);

    while (v.back() != 0) {
        v.push_back(v.back() - 1);
        std_v.push_back(std_v.back() - 1);
    }
    while (std_v.back() != 0) {
        std_v.push_back(std_v.back() - 1);
    }

    REQUIRE(ft::equal(v.begin(), v.end(), std_v.begin()) == true);
}

TEST_CASE("vector::front", "[vector]") {
    std::vector<int> v;

    v.push_back(78);
    v.push_back(16);

    v.front() -= v.back();

    REQUIRE(v.front() == 78 - 16);
}

TEST_CASE("vector::at", "[vector]") {
    ft::vector<int>  v(10);
    std::vector<int> std_v(10);

    for (unsigned i = 0; i < v.size(); i++) {
        v.at(i) = i;
        std_v.at(i) = i;
    }

    REQUIRE(ft::equal(v.begin(), v.end(), std_v.begin()) == true);
}

TEST_CASE("vector::operator[] ", "[vector]") {
    ft::vector<int>            v(10);

    ft::vector<int>::size_type sz = v.size();

    for (unsigned i = 0; i < sz; i++) {
        v[i] = i;
    }

    for (unsigned i = 0; i < sz / 2; i++) {
        int temp;
        temp = v[sz - 1 - i];
        v[sz - 1 - i] = v[i];
        v[i] = temp;
    }

    int             myints[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int             n = sizeof(myints) / sizeof(int);
    ft::vector<int> std_v;
    for (int i = 0; i < n; i++) {
        std_v.push_back(myints[i]);
    }
    REQUIRE(ft::equal(v.begin(), v.end(), std_v.begin()) == true);
}

TEST_CASE("vector::reserve", "[vector]") {
    ft::vector<int>  ft_v(5);
    std::vector<int> v(5);
    REQUIRE(ft_v.size() == v.size());
    REQUIRE(ft_v.capacity() >= 5);

    SECTION("resizing bigger changes size and capacity") {
        int n = 10;
        v.resize(n);
        ft_v.resize(n);
        REQUIRE(ft_v.size() == v.size());
        REQUIRE(ft_v.capacity() >= 10);
    }
    SECTION("resizing smaller changes size but not capacity") {
        int n = 0;
        v.resize(n);
        ft_v.resize(n);
        REQUIRE(ft_v.size() == v.size());
        REQUIRE(ft_v.capacity() >= 0);
    }
    SECTION("reserving bigger changes capacity but not size") {
        ft_v.reserve(10);
        REQUIRE(ft_v.size() == 5);
        REQUIRE(ft_v.capacity() >= 10);
    }
    SECTION("reserving smaller does not change size or capacity") {
        ft_v.reserve(0);
        REQUIRE(ft_v.size() == 5);
        REQUIRE(ft_v.capacity() >= 5);
    }
}

TEST_CASE("vector::empty", "[vector]") {
    ft::vector<int> v;
    int             sum(0);
    int             expected = 0;

    for (int i = 1; i <= 10; i++) {
        v.push_back(i);
        expected += i;
    }

    while (!v.empty()) {
        sum += v.back();
        v.pop_back();
    }

    REQUIRE(sum == expected);
}

TEST_CASE("vector::capacity", "[vector]") {
    ft::vector<int> v;

    for (int i = 0; i < 100; i++) {
        v.push_back(i);
    }

    int size = v.size();
    int capacity = v.capacity();
    REQUIRE(size == 100);
    REQUIRE(capacity >= size);
    REQUIRE(capacity <= v.max_size());
}

TEST_CASE("vector::resize", "[vector]") {
    ft::vector<int> v;

    for (int i = 1; i < 10; i++) {
        v.push_back(i);
    }

    v.resize(5);
    v.resize(8, 100);
    v.resize(12);

    int             myints[] = {1, 2, 3, 4, 5, 100, 100, 100, 0, 0, 0, 0};
    int             n = sizeof(myints) / sizeof(int);
    ft::vector<int> std_v;
    for (int i = 0; i < n; i++) {
        std_v.push_back(myints[i]);
    }
    REQUIRE(ft::equal(v.begin(), v.end(), std_v.begin()) == true);
}

TEST_CASE("vector::max_size", "[vector]") {
    ft::vector<int> v;

    for (int i = 0; i < 100; i++) {
        v.push_back(i);
    }

    REQUIRE(v.size() == 100);
    REQUIRE(v.capacity() >= v.size());
    REQUIRE(v.max_size() >= v.capacity());
}

TEST_CASE("vector::size") {
    ft::vector<int> v;
    REQUIRE(v.size() == 0);

    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }
    REQUIRE(v.size() == 10);

    v.insert(v.end(), 10, 100);
    REQUIRE(v.size() == 20);

    v.pop_back();
    REQUIRE(v.size() == 19);
}

/*
 * +---+---+---+---+---+---+---+
 * |   | 1 | 2 | 3 | 4 | 5 |   |
 * +---+---+---+---+---+---+---+
 *   ↑   ↑               ↑   ↑
 *   |   |               |   |
 *rend() |         rbegin()  end()
 *       |                   rbegin().base()
 *     begin()
 *     rend().base()
 */
TEST_CASE("vector::rbegin & vector::rend", "[vector]") {
    ft::vector<int>                   v(5);
    ft::vector<int>::reverse_iterator rit = v.rbegin();

    int                               i = 0;
    for (; rit != v.rend(); ++rit) {
        *rit = ++i;
    }

    i = *v.rend().base();
    for (ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        REQUIRE(*it == i);
        --i;
    }
}

TEST_CASE("vector::begin & vector::end", "[vector]") {
    ft::vector<int> v;
    for (int i = 1; i <= 5; i++) {
        v.push_back(i);
    }

    int i = 1;
    for (ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        REQUIRE(*it == i);
        i++;
    }
}

TEST_CASE("vector::operator=", "[vector]") {
    ft::vector<int> foo(3, 0);
    ft::vector<int> bar(5, 0);

    bar = foo;
    foo = ft::vector<int>();

    REQUIRE(foo.size() == 0);
    REQUIRE(bar.size() == 3);
}

TEST_CASE("vector::constructor", "[vector]") {
    ft::vector<int> first;
    REQUIRE(first.size() == 0);
    ft::vector<int> second(4, 100);
    REQUIRE(second.size() == 4);
    ft::vector<int> third(second.begin(), second.end());
    REQUIRE(third.size() == 4);
    REQUIRE(second == third);
    ft::vector<int> fourth(third);
    REQUIRE(fourth.size() == 4);
    REQUIRE(second == fourth);
    int             myints[] = {16, 2, 77, 29};
    int             n = sizeof(myints) / sizeof(int);
    ft::vector<int> fifth(myints, myints + n);
    REQUIRE(fifth.size() == n);
    REQUIRE(ft::equal(fifth.begin(), fifth.end(), myints));
}
