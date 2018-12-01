//
// Dictionary class implementation from Jamie's solution
//

#include <string>
#include <fstream>

#include "Dictionary.h"
#include "Exceptions.h"
#include "Util.h"

Dictionary::Dictionary(std::string dictionary_file_name):
words()
{
	std::ifstream dictFileStream(dictionary_file_name);

	if(!dictFileStream)
	{
		throw FileException("DICTIONARY");
	}

	while(!dictFileStream.eof())
	{
		std::string word;
		dictFileStream >> word;

		if (dictFileStream.eof() && word.empty())
		{
			break;
		}

		makeLowercase(word);
		words.insert(word);
	}
}

Dictionary::~Dictionary()
{
	// default destructor is OK
}

bool Dictionary::isLegalWord(std::string const &word) const
{
	//search in TrieSet
	TrieNode* temp = words.prefix(word);
	// if it was not in dictionary, or it was but not as a word, not legal
	if (temp == nullptr || !temp->inSet) return false;
	else return true;
}
