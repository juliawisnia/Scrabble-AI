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

	std::string word;

	while (!ifile.eof()) {

		getline(ifile, word);

		for (int i=0; i<word.size(); i++) {
			std::toupper(word[i]);
		}

		dictionary.insert(word);
	}
}

Dictionary::~Dictionary () {
}

bool Dictionary::isLegalWord (std::string const & word) const {
	std::set<string>::iterator it;
	it = dictionary.find(word);

	if (it == dictionary.end()) return false;

	else return true;
}