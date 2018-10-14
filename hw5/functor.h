#include <iostream>
#include <string>

struct NumStrComp {
    bool operator()(const std::string& lhs, const std::string& rhs) {
        std::string lWord;
        std::string rWord;

        int lSum = 0;
        int rSum = 0;

        for (size_t i = 0; i < lhs.size(); i++) lWord += std::toupper(lhs[i]);
        for (size_t j = 0; j < rhs.size(); j++) rWord += std::toupper(rhs[j]);
        
        for (size_t i = 0; i < lWord.size(); i++) {
            int curr = lWord[i];
            if (curr > 64) curr -= 55;
            else curr -= 48;
            lSum += curr;
        }
        for (size_t j = 0; j < rWord.size(); j++) {
            int curr = rWord[j];
            if (curr > 64) curr -= 55;
            else curr -= 48;
            rSum += curr;
        }

        return ((lSum < rSum) || (rSum == lSum && lhs < rhs));
    }

};