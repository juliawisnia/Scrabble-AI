#include <iostream>
#include <queue>
#include <utility>
#include <string>
#include <algorithm>
#include <functional>
#include <bits/stdc++.h>

struct sortByLength {
	bool operator()(std::string a, std::string b) {
		return (a.size() < b.size());
	}
};

void permutate(std::priority_queue<std::string, std::vector<std::string>, sortByLength>& hand, std::string input) {
	for (size_t i = 0; i < input.size(); i++) {
		std::sort(input.begin(), input.begin() + i);
		do {
			hand.emplace(input.substr(0, i + 1));
		} 
		while (std::next_permutation(input.begin(), input.begin() + i + 1));
	}
}

int main() {
	std::priority_queue<std::string, std::vector<std::string>, sortByLength> hand;
	std::string input = "abc";
	permutate(hand, input);
	while (!hand.empty()) {
		std::cout << hand.top() << std::endl;
		hand.pop();
	}
	std::cout << std::endl;
}