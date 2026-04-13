/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:54:25 by root              #+#    #+#             */
/*   Updated: 2026/04/06 18:03:13 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include "../utils/colors.hpp"
#include <exception>
#include <iostream>
#include <stdexcept>

int main(int ac, char **av) {
	try {
		if (ac != 2)
			throw std::runtime_error("./btc \"filename\"");
		btc::process(av[1]);
	}
	catch (std::exception &e) {
		std::cerr << RED << "Error: " << e.what() << RESET << std::endl;
		return 1;
	}
	return 0;
}