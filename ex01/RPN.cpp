/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 00:37:52 by root              #+#    #+#             */
/*   Updated: 2026/04/08 22:08:30 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include "../utils/colors.hpp"
#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>

std::list<double>	rpn::_list;

rpn::rpn() {}
rpn::rpn(const rpn& other) {(void)other;}
rpn &rpn::operator=(const rpn& other) {(void)other; return *this;}
rpn::~rpn() {}

bool rpn::isOperator(const char c) {return (c == '+' || c == '-' || c == '*' || c == '/');}

void rpn::calcul(char _operator) {
	double operand[2];
	for (int i = 1; i >= 0; i--, _list.pop_back())
		operand[i] = _list.back();

	switch (_operator) {
		case '+':
			return _list.push_back(operand[0] + operand[1]);
		case '-':
			return _list.push_back(operand[0] - operand[1]);
		case '*':
			return _list.push_back(operand[0] * operand[1]);
		case '/':
			operand[1] != 0 ? _list.push_back(operand[0] / operand[1]) : throw std::runtime_error("divison by zero");
	}
}

void rpn::process(const std::string& input) {
	_list.clear(); 
	
	std::istringstream iss(input);
	for (std::string tmp; iss >> tmp; void()) {
		if (tmp.size() != 1 || (!isOperator(tmp[0]) && !std::isdigit(tmp[0])))
			throw std::runtime_error("invalid input => " + tmp);
		if (std::isdigit(tmp[0]))
			_list.push_back(tmp[0] - '0');
		else {
			if (_list.size() < 2)
				throw std::runtime_error("invalid RPN expression");
			calcul(tmp[0]);
		}
	}
	
	if (_list.size() != 1)
		throw std::runtime_error("invalid RPN expression");
	std::cout << GREEN << _list.back() << RESET << std::endl;
}