/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 05:35:30 by tayamamo          #+#    #+#             */
/*   Updated: 2021/11/30 06:19:50 by tayamamo         ###   ########.fr       */
/*   Copyright 2021                                                           */
/* ************************************************************************** */

#include <iostream>

#include "vector.hpp"

int main() {
    ft::vector<int> v(5);
    for (int i = 0; i < 5; i++) {
        v[i] = i;
    }
    for (int i = 0; i < 5; i++) {
        std::cout << "v[" << i << "]: " << v[i] << std::endl;
    }
    return 0;
}
