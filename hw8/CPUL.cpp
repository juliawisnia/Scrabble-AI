#include <iostream>
#include <set>
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

void permute(std::set<std::string>& hand, std::string input, size_t n) {
	if (n == 0) return;
	do {
		hand.emplace(input.substr(0, input.size()));
	} while (std::next_permutation(input.begin(), input.begin() + input.size()));

	for (size_t i = 0; i < n; i++) {
		std::string temp = "";
		for (size_t j = 0; j < input.size(); j++) {
			if (i == j) continue;
			temp += input[j];
		}
		permute(hand, temp, n - 1);
	}
}

int main() {
	std::set<std::string> hand;
	std::string input = "california";
	permute(hand, input, input.size());
	std::set<std::string>::iterator it;
	for (it = hand.begin(); it != hand.end(); ++it) std::cout << (*it) << std::endl;
	return 0;
}