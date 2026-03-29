/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:54:22 by root              #+#    #+#             */
/*   Updated: 2025/12/27 09:02:34 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>
#include <cctype>


# define BAD_INPUT 				1
# define TOO_LARGE_NUMBER 		2
# define NOT_POSITIVE_NUMBER	3
# define DATE_TOO_OLD			4
# define DATE_DOESNT_EXIST		5

typedef std::map<std::string, double> map;

extern int err;

map     loadData(std::string data_name);
void    openFile(std::string file_name);
void    convertInput(std::string input, map m);
void    displayLine(std::string line, map m);
void    error(std::string line, int n);

bool isValidLine(std::string line, map m);
bool isValidFormat(std::string line, std::string sep);
bool isValidDate(std::string date);
bool isValidValue(std::string value);

#endif