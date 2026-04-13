/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 05:27:13 by root              #+#    #+#             */
/*   Updated: 2026/04/08 22:06:50 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <list>
#include <string>

class rpn {
    public:
        static void     process(const std::string& input);

    private:
        static std::list<double>    _list;

        rpn();
        ~rpn();
        rpn(const rpn& other);
        rpn &operator=(const rpn& other);

        static void     calcul(char _operator);
        static bool     isOperator(const char c);
};

#endif