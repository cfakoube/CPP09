/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 00:37:52 by root              #+#    #+#             */
/*   Updated: 2026/01/07 15:37:36 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

double calcul(double o1, double o2, char o) {
	switch (o) {
		case '+':
			return o1 + o2;
		case '-':
			return o1 - o2;
		case '*':
			return o1 * o2;
		case '/':
			if (o2 == 0)
				throw std::runtime_error("divison by zero.");
			return o1 / o2;
	}
	return 0;
}

int rpn(char *input) {
	double result;
	double operand1;
	double operand2;
	char operator_ = '\0';
	std::list<double> stack_;
	
	for (int i = 0; input[i]; i++) {
		while (isspace(input[i]))
			i++;
		if (!input[i]) break;
		if (std::string("0123456789+-*/").find(input[i]) == std::string::npos || (input[i +1] && !isspace(input[i +1]))) {
				throw std::runtime_error("invalid input.");
		}
		if (isdigit(input[i])) 
			stack_.push_back(double(input[i] - '0'));
		else if (stack_.size() < 2) {
				throw std::runtime_error("invalid RPN expression.");
		}
		else {
			operator_ = input[i];
			operand2 = stack_.back();
			stack_.pop_back();
			operand1 = stack_.back();
			stack_.pop_back();
			result = calcul(operand1, operand2, operator_);
			stack_.push_back(result);
		}
	}
	if (stack_.size() != 1 || !operator_) {
				throw std::runtime_error("invalid RPN expression.");
	}
	else 
		std::cout << result << std::endl;
	return 0;
}