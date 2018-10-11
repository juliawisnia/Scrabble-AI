#include "Dictionary.h"
#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

Dictionary::Dictionary (std::string dictionary_file_name) {
	std::ifstream ifile;
	ifile.open(dictionary_file_name);

	if (ifile.fail()) {
		std::cout << "Error: Invalid dictionary" << std::endl;
	}

	std::string line;
	while (getline(ifile, line)) {
		std::string word;
		std::stringstream ss(line);
		ss >> word;

		std::string copyWord = "";

		for (size_t i=0; i<word.size(); i++) {
			copyWord += std::toupper(word[i]);
		}
		
		dictionary.insert(copyWord);
	}
}

Dictionary::~Dictionary () {
}

bool Dictionary::isLegalWord (std::string & word) const {
	std::string upper = " ";
	for (size_t i = 0; i < word.size(); i++) {
		upper += std::toupper(word[i]);
	}

	std::set<std::string>::iterator it;
	it = dictionary.find(upper);

//	if (it != dictionary.end()) return true;

//	else return false;
return true;
}