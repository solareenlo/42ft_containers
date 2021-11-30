/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 01:26:10 by tayamamo          #+#    #+#             */
/*   Updated: 2021/11/30 07:30:31 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#include "../vector.hpp"

#include <vector>

#include "catch.hpp"

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
