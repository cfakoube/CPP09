/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 05:26:56 by root              #+#    #+#             */
/*   Updated: 2025/12/17 02:01:30 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Error: bad input.\nExcepted: ./RPN \"inverted Polish mathematical expression\"." << std::endl; return 1;
	}

	try {
		rpn(av[1]);
		return 0;
	}
	catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
}