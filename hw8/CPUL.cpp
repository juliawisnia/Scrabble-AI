#include <iostream>
#include <queue>
#include <utility>
#include <functional>
#include <bits/stdc++.h>

std::string CPULStrategy() {
	return "";
}

struct sortByLength {
	bool operator()(std::string a, std::string b) {
		return (a.size() < b.size());
	}
};

void helper(std::priority_queue<std::string, std::vector<std::string>, sortByLength>* handResult, std::string input, size_t k) {
	for (size_t i = 0; i < input.size(); i++) {
		std::string temp = "";
		for (size_t j = i; j < k; j++) {
			temp += input[i + j];
		}
		handResult->emplace(temp);
		helper(handResult, )
	}
}

void handPermutations(std::priority_queue<std::string, std::vector<std::string>, sortByLength>& handResult, std::string input) {
	size_t k = input.size();
	for (size_t i = 1; i <= k; i++) {
		helper(&handResult, input, i);
	}
}

int main() {
	std::priority_queue<std::string, std::vector<std::string>, sortByLength> hand;
	std::string input = "oka";
	handPermutations(hand, input);
	while (!hand.empty()) {
		std::cout << hand.top() << std::endl;
		hand.pop();
	}
	std::cout << std::endl;
}