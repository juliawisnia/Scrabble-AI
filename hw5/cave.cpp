#include <iostream>
#include <stack>
#include <string>
#include <sstream>

int main() {
    std::string read;
    std::cin >> read;
    std::stack<char> stk;

    for (size_t i = 0; i < read.size(); i++) {
        if (read[i] != 'n' && read[i] != 's' && read[i] != 'e' && read[i] != 'w') {
            std::cout << "invalid" << std::endl;
            return -1;
        }

        if ((i + 1 < read.size()) && ((read[i] == 'n' && read[i + 1] == 's') || (read[i] == 's' && read[i + 1] == 'n') 
                                || (read[i] == 'w' && read[i + 1] == 'e') || (read[i] == 'e' && read[i + 1] == 'w'))) {
            i++;
            continue;
        }

        else {
            if (stk.empty()) {
                stk.push(read[i]);
                continue;
            }

            char prev = stk.top();
            if ((read[i] == 'n' && prev == 's') || (read[i] == 's' && prev == 'n') 
                                || (read[i] == 'w' && prev == 'e') || (read[i] == 'e' && prev == 'w')) {
                stk.pop();
            }
            else stk.push(read[i]);
        }
    }

    if (stk.empty()) std::cout << "rolled up" << std::endl;
    else std::cout << "not rolled up" << std::endl;
    
    return 0;
}
