/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 05:39:55 by root              #+#    #+#             */
/*   Updated: 2026/02/11 10:35:37 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iomanip>

double getElapsedTime(struct timeval start, struct timeval end) {
	return (static_cast<double>(end.tv_usec - start.tv_usec));
}

void displayTime(size_t size, double totalMicroseconds, const std::string& containerType) {
	std::cout << "Time to process a range of " << size << " elements with std::" 
		<< containerType << " : " << std::fixed << std::setprecision(5) << totalMicroseconds << " us" << std::endl;
}


vec loadVec(int ac, char **av) {
	if (ac < 2)
	throw std::runtime_error("invalid input.\nUsage: ./PmergeMe \"positive int sequence\"");
	
	vec v;
	std::string input;
	for (int i = 1; i < ac; i++) {
		input += av[i];
		if (i + 1 != ac)
		input += " ";
	}

	std::stringstream ss(input);
	for (long value = 0; !ss.eof(); v.push_back(value)) {
		ss >> value;
		if (ss.fail() || value <= 0 || value > INT_MAX)
		throw std::runtime_error("bad input.");
		ss >> std::ws;
	}
	return v;
}

void displaySeq(vec seq, std::string str) {
	std::cout << str;
	for (vec::iterator it = seq.begin(); it != seq.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

std::vector<size_t> jacobsthalSequence(size_t n) {
	std::vector<size_t> jacob;
	if (n == 0) return jacob;
	
	jacob.push_back(0);
	if (n == 1) 
		return jacob;
	
	jacob.push_back(1);
	
	size_t prev = 0, curr = 1;
	while (true) {
		size_t next = curr + 2 * prev;
		if (next >= n)
			break;
		jacob.push_back(next);
		prev = curr;
		curr = next;
	}
	
	return jacob;
}

vec sortVec(vec v) {
	size_t n = v.size();
	
	if (n <= 1)
		return v;
	
	bool odd = (n % 2 != 0);
	if (odd)
		n--;
	
	vecPair pairs;
	for (size_t i = 0; i < n; i += 2) {
		if (v[i] > v[i + 1])
			pairs.push_back(std::make_pair(v[i], v[i + 1]));
		else
			pairs.push_back(std::make_pair(v[i + 1], v[i]));
	}
	
	int straggler = -1;
	if (odd)
		straggler = v.back();
	
	if (pairs.size() > 1) {
		vec larger;
		for (size_t i = 0; i < pairs.size(); i++)
			larger.push_back(pairs[i].first);
		
		larger = sortVec(larger);
		
		vecPair sortedPairs;
		for (size_t i = 0; i < larger.size(); i++) {
			for (size_t j = 0; j < pairs.size(); j++) {
				if (pairs[j].first == larger[i]) {
					sortedPairs.push_back(pairs[j]);
					pairs[j].first = -1;
					break;
				}
			}
		}
		pairs = sortedPairs;
	}
	
	vec mainChain;
	vec pending;
	
	if (!pairs.empty()) {
		mainChain.push_back(pairs[0].second);
		mainChain.push_back(pairs[0].first);
	}
	
	for (size_t i = 1; i < pairs.size(); i++) {
		mainChain.push_back(pairs[i].first);
		pending.push_back(pairs[i].second);
	}
	
	if (pending.size() > 0) {
		std::vector<size_t> jacob = jacobsthalSequence(pending.size() + 1);
		std::vector<size_t> insertionOrder;
		std::vector<bool> inserted(pending.size(), false);
		
		for (size_t i = 1; i < jacob.size(); i++) {
			size_t idx = jacob[i];
			if (idx <= pending.size()) {
				size_t start = (i == 1) ? idx : jacob[i - 1] + 1;
				for (size_t j = idx; j >= start && j > 0; j--) {
					if (j - 1 < pending.size() && !inserted[j - 1]) {
						insertionOrder.push_back(j - 1);
						inserted[j - 1] = true;
					}
				}
			}
		}
		
		for (size_t i = 0; i < pending.size(); i++) {
			if (!inserted[i])
				insertionOrder.push_back(i);
		}
		
		for (size_t i = 0; i < insertionOrder.size(); i++) {
			size_t idx = insertionOrder[i];
			int valueToInsert = pending[idx];
			
			size_t left = 0;
			size_t right = mainChain.size();
			while (left < right) {
				size_t mid = left + (right - left) / 2;
				if (mainChain[mid] < valueToInsert)
					left = mid + 1;
				else
					right = mid;
			}
			mainChain.insert(mainChain.begin() + left, valueToInsert);
		}
	}
	
	if (odd) {
		size_t left = 0;
		size_t right = mainChain.size();
		while (left < right) {
			size_t mid = left + (right - left) / 2;
			if (mainChain[mid] < straggler)
				left = mid + 1;
			else
				right = mid;
		}
		mainChain.insert(mainChain.begin() + left, straggler);
	}
	
	return mainChain;
}

deq loadDeq(int ac, char **av) {
	if (ac < 2)
		throw std::runtime_error("invalid input.\nUsage: ./PmergeMe \"positive int sequence\"");
	
	deq d;
	std::string input;
	for (int i = 1; i < ac; i++) {
		input += av[i];
		if (i + 1 != ac)
			input += " ";
	}

	std::stringstream ss(input);
	for (long value = 0; !ss.eof(); d.push_back(value)) {
		ss >> value;
		if (ss.fail() || value <= 0 || value > INT_MAX)
			throw std::runtime_error("bad input.");
		ss >> std::ws;
	}
	return d;
}

void displaySeqDeq(deq seq, std::string str) {
	std::cout << str;
	for (deq::iterator it = seq.begin(); it != seq.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

deq sortDeq(deq d) {
	size_t n = d.size();
	
	if (n <= 1)
		return d;
	
	bool odd = (n % 2 != 0);
	if (odd)
		n--;
	
	deqPair pairs;
	for (size_t i = 0; i < n; i += 2) {
		if (d[i] > d[i + 1])
			pairs.push_back(std::make_pair(d[i], d[i + 1]));
		else
			pairs.push_back(std::make_pair(d[i + 1], d[i]));
	}
	
	int straggler = -1;
	if (odd)
		straggler = d.back();
	
	if (pairs.size() > 1) {
		deq larger;
		for (size_t i = 0; i < pairs.size(); i++)
			larger.push_back(pairs[i].first);
		
		larger = sortDeq(larger);
		
		deqPair sortedPairs;
		for (size_t i = 0; i < larger.size(); i++) {
			for (size_t j = 0; j < pairs.size(); j++) {
				if (pairs[j].first == larger[i]) {
					sortedPairs.push_back(pairs[j]);
					pairs[j].first = -1;
					break;
				}
			}
		}
		pairs = sortedPairs;
	}
	
	deq mainChain;
	deq pending;
	
	if (!pairs.empty()) {
		mainChain.push_back(pairs[0].second);
		mainChain.push_back(pairs[0].first);
	}
	
	for (size_t i = 1; i < pairs.size(); i++) {
		mainChain.push_back(pairs[i].first);
		pending.push_back(pairs[i].second);
	}
	
	if (pending.size() > 0) {
		std::vector<size_t> jacob = jacobsthalSequence(pending.size() + 1);
		std::vector<size_t> insertionOrder;
		std::vector<bool> inserted(pending.size(), false);
		
		for (size_t i = 1; i < jacob.size(); i++) {
			size_t idx = jacob[i];
			if (idx <= pending.size()) {
				size_t start = (i == 1) ? idx : jacob[i - 1] + 1;
				for (size_t j = idx; j >= start && j > 0; j--) {
					if (j - 1 < pending.size() && !inserted[j - 1]) {
						insertionOrder.push_back(j - 1);
						inserted[j - 1] = true;
					}
				}
			}
		}
		
		for (size_t i = 0; i < pending.size(); i++) {
			if (!inserted[i])
				insertionOrder.push_back(i);
		}
		
		for (size_t i = 0; i < insertionOrder.size(); i++) {
			size_t idx = insertionOrder[i];
			int valueToInsert = pending[idx];
			
			size_t left = 0;
			size_t right = mainChain.size();
			while (left < right) {
				size_t mid = left + (right - left) / 2;
				if (mainChain[mid] < valueToInsert)
					left = mid + 1;
				else
					right = mid;
			}
			mainChain.insert(mainChain.begin() + left, valueToInsert);
		}
	}
	
	if (odd) {
		size_t left = 0;
		size_t right = mainChain.size();
		while (left < right) {
			size_t mid = left + (right - left) / 2;
			if (mainChain[mid] < straggler)
				left = mid + 1;
			else
				right = mid;
		}
		mainChain.insert(mainChain.begin() + left, straggler);
	}
	
	return mainChain;
}