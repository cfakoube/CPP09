/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 05:26:56 by root              #+#    #+#             */
/*   Updated: 2026/04/07 18:56:14 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include "../utils/colors.hpp"
#include <exception>
#include <iostream>
#include <stdexcept>

int main(int ac, char **av) {
	try {
		if (ac != 2)
			throw std::runtime_error("./RPN \"digit digit operator\".");
		rpn::process(av[1]);
	}
	catch (const std::exception &e) {
		std::cerr << RED <<  "Error: " << e.what() << RESET << std::endl;
		return 1;
	}
	return 0;
}