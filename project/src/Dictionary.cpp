#include "Dictionary.h"
#include <set>
#include <string>
#include <fstream>
#include <iostream>

Dictionary::Dictionary (std::string dictionary_file_name) {
	std::ifstream ifile;
	ifile.open(dictionary_file_name);

	if (ifile.fail()) {
		std::cout << "Error: Invalid dictionary" << std::endl;
	}

	std::stringstream ss;
	ss << ifile;

	while (!ifile.eof()) {
		std::string word;
		ss >> word;

		for (int i=0; i<word.size(); i++) {
			std::toupper(word[i]);
		}

		dictionary.insert(word);
	}
}

Dictionary::~Dictionary () {
}

bool Dictionary::isLegalWord (std::string & word) const {
	for (size_t i = 0; i < word.size(); i++) {
		std::toupper(word[i]);
	}

	std::set<string>::iterator it;
	it = dictionary.find(word);

	if (it == dictionary.end()) return false;

	else return true;
}