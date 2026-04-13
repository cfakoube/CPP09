/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:54:22 by root              #+#    #+#             */
/*   Updated: 2026/04/07 04:37:56 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <fstream>
#include <map>
#include <string>

typedef std::map<std::string, double> map;

class btc {
    public:
        static void    process(const std::string& infile);

    private:
        static map                  data;
        static const std::string&   valueFormat;

        btc();
        btc(const btc& other);
        btc &operator=(const btc& other);
        ~btc();

        static void    loadData(const std::string& filename);
        static void    checkFirstLine(std::ifstream& f, const std::string& filename, const std::string& firstLine);
        static void    findAmount(std::string date, double value);
        static void    display(std::string message, std::string color);

        static bool    isValidFormat(std::string line, std::string sep);
        static bool    isValidDate(std::string line);
};

#endif