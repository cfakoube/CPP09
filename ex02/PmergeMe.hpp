/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 05:40:13 by root              #+#    #+#             */
/*   Updated: 2026/04/08 21:27:46 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <deque>
#include <string>
#include <utility>
#include <vector>

typedef std::vector<int> vec;
typedef std::deque<int> deq;
typedef std::pair<int, int> intPair;
typedef std::vector<intPair> vecPair;
typedef std::deque<intPair> deqPair;

class PmergeMe {
    public:
        static void process(const std::string& input);

    private:
        static vec          vecInput;
        static deq          deqInput;
        static vec          vecMainChain;
        static deq          deqMainChain;
        static vec          jacobSthalSequence;
        static double       vecTime;
        static double       deqTime;

        PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        static void parseInput(const std::string& input);
        static void vecProcess();
        static void deqProcess();
        static void output();

        static vec vecSort(vec V);
        static deq deqSort(deq D);

        static int vecBinaryInsertion(int toInsert, int larger, vec V);
        static int deqBinaryInsertion(int toInsert, int larger, deq D);

        static void setJacobSthalSequence(int size);
};


#endif