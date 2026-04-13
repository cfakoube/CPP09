/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 05:39:55 by root              #+#    #+#             */
/*   Updated: 2026/04/08 21:27:41 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <sys/time.h>

vec      PmergeMe::vecInput;
deq      PmergeMe::deqInput;
vec      PmergeMe::vecMainChain;
deq      PmergeMe::deqMainChain;
vec      PmergeMe::jacobSthalSequence;
double   PmergeMe::vecTime = 0;
double   PmergeMe::deqTime = 0;

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& other) {(void)other;}
PmergeMe& PmergeMe::operator=(const PmergeMe& other) {(void)other; return *this;}
PmergeMe::~PmergeMe() {}

void PmergeMe::parseInput(const std::string& input) {
    std::istringstream iss(input);
    for (std::string tmp; iss >> tmp;) {
        int n;
        char c;
        std::istringstream _iss(tmp);
        if (!(_iss >> n) || n < 0 || _iss >> c)
            throw std::runtime_error("invalid argument => '" + tmp + "'");
        vecInput.push_back(n);
        deqInput.push_back(n);
    }

    if (vecInput.empty())
        throw std::runtime_error("./PmergeMe int int int int int int...");
}

vec PmergeMe::vecSort(vec V) {
    int size = V.size();
    if (size <= 1)
        return V;
        
    int alone = -1;
    if (size % 2 != 0) {
        size -= 1;
        alone = V.back();
    }

    vecPair pair;
    vec     larger;
    for (int i = 0, big, small; i < size; i += 2) {
        big = std::max(V[i], V[i + 1]);
        small = std::min(V[i], V[i + 1]);
        pair.push_back(std::make_pair(big, small));
        larger.push_back(big);
    }

    larger = vecSort(larger);

    vec mainChain;
    vecPair pairSorted;
    std::vector<bool> used(pair.size(), false);

    for (unsigned int i = 0; i < larger.size(); i++) {
        for (unsigned int j = 0; j < pair.size(); j++ ) {
            if (used[j] == false && larger[i] == pair[j].first) {
                mainChain.push_back(larger[i]);
                pairSorted.push_back(std::make_pair(pair[j].first, pair[j].second));
                used[j] = true;
                break;
            } 
        } 
    }

    setJacobSthalSequence(pairSorted.size());
    
    if (pairSorted.size() > 0)
        mainChain.insert(mainChain.begin(), pairSorted[0].second);
    
    for (unsigned int i = 0, idx; i < jacobSthalSequence.size(); i++) { 
            idx = vecBinaryInsertion(pairSorted[jacobSthalSequence[i]].second, pairSorted[jacobSthalSequence[i]].first, mainChain);
            mainChain.insert(mainChain.begin() + idx, pairSorted[jacobSthalSequence[i]].second);
    }
    
    if (alone != -1)
        mainChain.insert(mainChain.begin() + vecBinaryInsertion(alone, -1, mainChain), alone);

    return mainChain;
}

deq PmergeMe::deqSort(deq D) {
    int size = D.size();
    if (size <= 1)
        return D;
        
    int alone = -1;
    if (size % 2 != 0) {
        size -= 1;
        alone = D.back();
    }

    deqPair pair;
    deq     larger;
    for (int i = 0, big, small; i < size; i += 2) {
        big = std::max(D[i], D[i + 1]);
        small = std::min(D[i], D[i + 1]);
        pair.push_back(std::make_pair(big, small));
        larger.push_back(big);
    }

    larger = deqSort(larger);

    deq mainChain;
    deqPair pairSorted;
    std::vector<bool> used(pair.size(), false);

    for (unsigned int i = 0; i < larger.size(); i++) {
        for (unsigned int j = 0; j < pair.size(); j++ ) {
            if (used[j] == false && larger[i] == pair[j].first) {
                mainChain.push_back(larger[i]);
                pairSorted.push_back(std::make_pair(pair[j].first, pair[j].second));
                used[j] = true;
                break;
            } 
        } 
    }

    setJacobSthalSequence(pairSorted.size());
    
    if (pairSorted.size() > 0)
        mainChain.insert(mainChain.begin(), pairSorted[0].second);
    
    for (unsigned int i = 0, idx; i < jacobSthalSequence.size(); i++) { 
            idx = deqBinaryInsertion(pairSorted[jacobSthalSequence[i]].second, pairSorted[jacobSthalSequence[i]].first, mainChain);
            mainChain.insert(mainChain.begin() + idx, pairSorted[jacobSthalSequence[i]].second);
    }
    
    if (alone != -1)
        mainChain.insert(mainChain.begin() + deqBinaryInsertion(alone, -1, mainChain), alone);

    return mainChain;
}

void PmergeMe::setJacobSthalSequence(int size) {
    jacobSthalSequence.clear();
    if (size <= 1)
        return;
    jacobSthalSequence.push_back(1);
    jacobSthalSequence.push_back(3);
    
    for (int i = 0; jacobSthalSequence.back() < size; i++)
        jacobSthalSequence.push_back((jacobSthalSequence[i] * 2) + jacobSthalSequence[i + 1]);
    
    vec insertionOrder;
    insertionOrder.push_back(1);
    for (unsigned int i = 1; i < jacobSthalSequence.size(); i++) {
        if (jacobSthalSequence[i] < size)
            insertionOrder.push_back(jacobSthalSequence[i]);
        for (int j = jacobSthalSequence[i] - 1; j > jacobSthalSequence[i - 1]; j--)
            if (j < size)
                insertionOrder.push_back(j);
    }
    
    jacobSthalSequence = insertionOrder;
}

int PmergeMe::vecBinaryInsertion(int toInsert, int larger, vec V) {
    int left = 0;
    int right = V.size();

    if (larger != -1) {
        vec::iterator it = std::find(V.begin(), V.end(), larger);
        if (it != V.end())
            right = it - V.begin();
    }

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (V[mid] <= toInsert)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

int PmergeMe::deqBinaryInsertion(int toInsert, int larger, deq D) {
    int left = 0;
    int right = D.size();

    if (larger != -1) {
        deq::iterator it = std::find(D.begin(), D.end(), larger);
        if (it != D.end())
            right = it - D.begin();
    }

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (D[mid] <= toInsert)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

void PmergeMe::output() {
    std::cout << "Before: ";
    for (vec::iterator it = vecInput.begin(); it != vecInput.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl << "After: ";
    for (vec::iterator it = vecMainChain.begin(); it != vecMainChain.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    int nbElements = vecInput.size();
    std::cout << "Time to process a range of " << nbElements << " elements with std::vector : " << vecTime << " us" << std::endl;
    std::cout << "Time to process a range of " << nbElements << " elements with std::deque : " << deqTime << " us" << std::endl;
}

void PmergeMe::vecProcess() {
    timeval start, end;
    gettimeofday(&start, NULL);
    vecMainChain = vecSort(vecInput);
    gettimeofday(&end, NULL);
    vecTime = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
}

void PmergeMe::deqProcess() {
    timeval start, end;
    gettimeofday(&start, NULL);
    deqMainChain = deqSort(deqInput);
    gettimeofday(&end, NULL);
    deqTime = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
}

void PmergeMe::process(const std::string& input) {
    parseInput(input);
    vecProcess();
    deqProcess();
    output();
}