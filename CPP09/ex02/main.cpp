/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 05:53:05 by root              #+#    #+#             */
/*   Updated: 2026/01/07 15:34:25 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av) {
	try {
		struct timeval start, end;
		
		gettimeofday(&start, NULL);
		vec input = loadVec(ac, av);
		vec v = sortVec(input);
		gettimeofday(&end, NULL);
		double vTime = getElapsedTime(start, end);
		
		gettimeofday(&start, NULL);
		deq input_ = loadDeq(ac, av);
		deq d = sortDeq(input_);
		gettimeofday(&end, NULL);
		double dTime = getElapsedTime(start, end);
		
		displaySeq(input, "Before: ");
		displaySeq(v, "After: ");
		displayTime(v.size(), vTime, "vector");
		displayTime(d.size(), dTime, "deque");
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
