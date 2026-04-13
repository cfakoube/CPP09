/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 05:53:05 by root              #+#    #+#             */
/*   Updated: 2026/04/08 21:27:44 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "../utils/colors.hpp"
#include <iostream>
#include <sstream>

static std::string setInput(int ac, char **av) {
	std::ostringstream oss;
	for (int i = 1; i < ac; i++)
		oss << av[i] << " ";
	return (oss.str());
}

int main(int ac, char **av) {
	try {
		std::string input = setInput(ac, av);
		PmergeMe::process(input);
	}
	catch (std::exception &e) {
		std::cerr << RED << "Error: " << e.what() << RESET << std::endl;
	}
}
