/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:54:25 by root              #+#    #+#             */
/*   Updated: 2025/12/27 07:27:58 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
 
int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Error: bad input\nUsage: ./btc <filename>" << std::endl;
		return 1;
	}

	try {
		openFile(av[1]); 
		openFile("data.csv");
		map data = loadData("data.csv");
		convertInput(av[1], data);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	
	return 0;
}