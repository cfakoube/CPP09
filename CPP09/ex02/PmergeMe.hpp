/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 05:40:13 by root              #+#    #+#             */
/*   Updated: 2026/01/07 15:34:30 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <sys/time.h>
#include <climits>
#include <exception>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>

typedef std::vector<int> vec;
typedef std::deque<int> deq;
typedef std::pair<int, int> intPair;
typedef std::vector<intPair> vecPair;
typedef std::deque<intPair> deqPair;

vec loadVec(int ac, char **av);
vec sortVec(vec v);

deq loadDeq(int ac, char **av);
deq sortDeq(deq d);

std::vector<size_t> jacobsthalSequence(size_t n);
void displaySeq(vec seq, std::string str);
void displayTime(size_t size, double totalMicroseconds, const std::string& containerType);
double getElapsedTime(struct timeval start, struct timeval end);

#endif