/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:54:11 by root              #+#    #+#             */
/*   Updated: 2026/01/07 15:46:35 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int err = BAD_INPUT;

void error(std::string line, int n) {
	switch(n) {
		case BAD_INPUT:
			std::cerr << "Error: bad input => " << line << std::endl;
			break;
		case NOT_POSITIVE_NUMBER:
			std::cerr << "Error: not a positive number."<< std::endl;
			break;
		case TOO_LARGE_NUMBER:
			std::cerr << "Error: too large a number." << std::endl;
			break;
		case DATE_TOO_OLD:
			std::cerr << "Error: date is too old" << std::endl;
			break;
		case DATE_DOESNT_EXIST:
			std::cerr << "Error: date does not exist." << std::endl;
	}
}

void openFile(std::string file_name) {
	std::ifstream file(file_name.c_str());
	if (!file || !file.is_open()) {
		throw std::runtime_error("Could not open '" + file_name + "'.");
	}
	return ;
}

map loadData(std::string data_name) {
	map m;
	std::string line;
	std::ifstream data(data_name.c_str());
	
	std::getline(data, line);
	if (line != "date,exchange_rate")
		throw std::runtime_error("the first line of data.csv should be 'date,exchange_rate'.");
	for (int i = 0; getline(data, line); i++) {
		if (!isValidFormat(line, ",") || !isValidDate(line.substr(0, 10)) || atof(line.substr(11).c_str()) < 0)
			throw std::runtime_error("invalid line in data.csv: \"" + line + "\"");
		m[line.substr(0, 10)] = std::atof(line.substr(11).c_str());
	}
		
	return m;
}

bool isValidFormat(std::string line, std::string sep) {
	err	= BAD_INPUT;
	std::string format 	= "XXXX-XX-XX" + sep + "X";
	size_t lsize = line.length();
	size_t fsize = format.length();
	
	for (size_t i = 0; i < lsize; i++) {
		if (i < fsize) {
			if (isalpha(line[i]))
				return false;
			if (isdigit(line[i]) || (i == fsize - 1 && fsize != lsize && (line[i] == '-' || line[i] == '+' || line[i] == '.')))
				line[i] = 'X';
		}
		else {
			if (!isdigit(line[i]) && line[i] != '.' && line[i] != 'f')
				return false;
			if ((line[i] == '.' && line.find('.', i + 1) != std::string::npos) || (line[i] == 'f' && i != line.length() - 1))
				return false;
		}
	}
	if (format != line.substr(0, format.length()))
		return false;
	return true;
}

bool isValidDate(std::string date) {
	int year 	= atoi(date.substr(0, 4).c_str());
	int month 	= atoi(date.substr(5, 2).c_str());
	int day 	= atoi(date.substr(8, 2).c_str());
	
	err = DATE_DOESNT_EXIST;
	if ((month < 1 || month > 12) || (day < 1 || day > 31))
		return false;
	if ((month == 4 || month == 6 || month == 9 || month ==  11) && day > 30)
		return false;
	if ((month == 2 && day > 29) || (!__isleap(year) && month == 2 && day > 28))
		return false;
	err = DATE_TOO_OLD;
	return true;
}
	
bool isValidValue(std::string value) {
	double d;
	d = std::atof(value.c_str());
	if (d < 0) {
		err = NOT_POSITIVE_NUMBER; return false;
	}
	if (d > 1000) {
		err = TOO_LARGE_NUMBER; return false;
	}
	return true;
}
	
bool isValidLine(std::string line, map m) {
	map::const_iterator it = m.begin();
		
	if (!isValidFormat(line, " | ") || !isValidDate(line.substr(0, 10)) || line.substr(0, 10) < it->first || !isValidValue(line.substr(13))) 
		return false;
	return true;
}

void convertInput(std::string file_name, map m) {
	std::string line;
	std::ifstream input(file_name.c_str());
	std::getline(input, line);
	if (isValidLine(line, m))
		displayLine(line, m);
	else if (line != "date | value")
		error(line, BAD_INPUT);
	for (int i = 0; std::getline(input, line); i++) {
		if (isValidLine(line, m))
			displayLine(line, m);
		else
			error(line, err);
	}
	return ;
}

void displayLine(std::string line, map m) {
	double 				value 	= std::atof(line.substr(13).c_str());
	std::string 		date 	= line.substr(0, 10);
	map::const_iterator it		= m.lower_bound(date);
	
	if (it == m.end() || it-> first != date)
		it--;
	std::cout << date << " => " << value << " = " << (value * it->second) << std::endl;
}