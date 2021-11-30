/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 01:26:10 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/01 08:02:45 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#include "../vector.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

#include "../algorithm.hpp"
#include "catch.hpp"

TEST_CASE("vector::resize") {
    ft::vector<int> v;

    for (int i = 1; i < 10; i++) {
        v.push_back(i);
    }

    v.resize(5);
    v.resize(8, 100);
    v.resize(12);

    int             myints[] = {1, 2, 3, 4, 5, 100, 100, 100, 0, 0, 0, 0};
    int             n = sizeof(myints) / sizeof(int);
    ft::vector<int> expected;
    for (int i = 0; i < n; i++) {
        expected.push_back(myints[i]);
    }
    REQUIRE(ft::equal(v.begin(), v.end(), expected.begin()) == true);
}

TEST_CASE("vector::max_size") {
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
TEST_CASE("vector::rbegin & vector::rend") {
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

TEST_CASE("vector::begin & vector::end") {
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

TEST_CASE("vector::operator=") {
    ft::vector<int> foo(3, 0);
    ft::vector<int> bar(5, 0);

    bar = foo;
    foo = ft::vector<int>();

    REQUIRE(foo.size() == 0);
    REQUIRE(bar.size() == 3);
}

TEST_CASE("vector::constructor") {
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

TEST_CASE("vectors can be sized and resized", "[vector]") {
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
