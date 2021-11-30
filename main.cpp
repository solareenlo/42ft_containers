/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 05:35:30 by tayamamo          #+#    #+#             */
/*   Updated: 2021/12/01 08:08:02 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#include <iostream>
#include <typeinfo>
#include <vector>

#include "vector.hpp"

int main() {
    {
        ft::vector<int>                   v(5);
        ft::vector<int>::reverse_iterator rit = v.rbegin();

        std::cout << v.end() - v.begin() << std::endl;
        std::cout << v.rend() - v.rbegin() << std::endl;
        std::cout << *v.begin() << std::endl;
        std::cout << *v.end() << std::endl;
        std::cout << *v.rbegin() << std::endl;
        std::cout << *(v.rend()-1) << std::endl;
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
    {
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

    {
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

    {
        ft::vector<int> v(5);

        for (int i = 0; i < 5; i++) {
            v[i] = i;
        }
        for (int i = 0; i < 5; i++) {
            std::cout << "v[" << i << "]: " << v[i] << std::endl;
        }
        v.resize(10);
        std::cout << "size: " << v.size() << std::endl;
        v.resize(0);
        std::cout << "size: " << v.size() << std::endl;
    }
    return 0;
}
