/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:54:11 by root              #+#    #+#             */
/*   Updated: 2026/04/07 04:44:46 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include "../utils/colors.hpp"
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

map btc::data;
const std::string& btc::valueFormat = "V V. .V V.V -V -V. -.V -V.V +V +V. +.V +V.V";

btc::btc() {}
btc::btc(const btc& other) {(void)other;}
btc &btc::operator=(const btc& other) {(void)other; return *this;}
btc::~btc() {}

void btc::checkFirstLine(std::ifstream& file, const std::string& filename, const std::string& firstLine) {
	std::string line;
	std::getline(file, line);
	if (line != firstLine)
		throw std::runtime_error("the first line of " + filename + " should be '" + firstLine + "'");
}

void btc::process(const std::string& infile) {
	loadData("data.csv");
	std::ifstream f(infile.c_str());
	f.fail() ? throw std::runtime_error("could not open '" + infile + "'") : checkFirstLine(f, infile, "date | value");
	
	for (std::string line; std::getline(f, line);)
		if (isValidFormat(line, " | ") && isValidDate(line))
			findAmount(line.substr(0,10), std::atof(line.substr(13).c_str()));
		else
			display("Error: bad input => " + line, RED);
}

void btc::loadData(const std::string& filename) {
	std::ifstream f(filename.c_str());
	f.fail() ? throw std::runtime_error("could not open '" + filename + "'") : checkFirstLine(f, filename, "date,exchange_rate");
	
	for (std::string line; std::getline(f, line);) {
		if (!isValidFormat(line, ",") || !isValidDate(line) || std::atof(line.substr(11).c_str()) < 0)
			throw std::runtime_error("invalid line in data.csv: \"" + line + "\"");
		data[line.substr(0,10)] = std::atof(line.substr(11).c_str());
	}
			
	if (data.empty())
		throw std::runtime_error("empty database");
}

bool btc::isValidFormat(std::string line, std::string sep) {
	std::string tmp;
	for (unsigned int i = 0; i < line.size(); i++) {
		if (!std::isdigit(line[i]))
			tmp.push_back(std::tolower(line[i]));
		else if (i < 10)
			tmp.push_back('D');
		else if (!std::isdigit(line[i - 1]))
			tmp.push_back('V');
	}
	
	std::istringstream iss(valueFormat);
	for (std::string V; iss >> V; void())
		if (tmp == "DDDD-DD-DD" + sep + V)
			return true;
	return false;
}

bool btc::isValidDate(std::string line) {
	int year 	= std::atoi(line.substr(0, 4).c_str());
	int month 	= std::atoi(line.substr(5, 2).c_str());
	int day 	= std::atoi(line.substr(8, 2).c_str());
	
	if ((month < 1 || month > 12) || (day < 1 || day > 31)	|| 
		((month == 4 || month == 6 || month == 9 || month ==  11) && day > 30)	||
				(month == 2 && day > 29) || (!__isleap(year) && month == 2 && day > 28))
		return false;
	return true;
}

void btc::findAmount(std::string date, double value) {
	if (date < data.begin()->first)
		return display("Error: no data for this date => " + date, RED);
	if (value < 0 || value > 1000)
		return display(value < 0 ? "Error: not a positive number." : "Error: too large a number.", RED);
	map::const_iterator it = data.lower_bound(date);
	if (it == data.end() || it->first != date)
		it--;
	std::ostringstream oss;
	oss << date << " => " << value << " = " << (value * it->second);
	display(oss.str(), GREEN);
}

void	btc::display(std::string message, std::string color) {
	std::cout << color << message << RESET << std::endl;
}