#include <iostream>
#include <stack>
#include <string>
#include <sstream>

int main() {
    std::string read;
    std::cin >> read;
    std::stack<char> stk;

    if (read.size() % 2 != 0) {
        std::cout << "not rolled up" << std::endl;
        return 0;
    }

    for (size_t i = 0; i < read.size(); i++) {
        if (read[i] != 'n' && read[i] != 's' && read[i] != 'e' && read[i] != 'w') {
            std::cout << "invalid" << std::endl;
            return -1;
        }

        if ((i + 1 < read.size()) && ((i == 'n' && i + 1 == 's') || (i == 's' && i + 1 == 'n') || (i == 'w' && i + 1 == 'e') || (i == 'e' && i + 1 == 'w'))) {
            i++;
        }

        else {
            char prev = stk.top();
            if (!stk.empty() && ((i == 'n' && prev == 's') || (i == 's' && prev == 'n') || (i == 'w' && prev == 'e') || (i == 'e' && prev== 'w'))) {
                stk.pop();
            }
            else stk.push(i);
        }
    }

    if (stk.empty()) std::cout << "rolled up" << std::endl;
    else std::cout << "not rolled up" << std::endl;
    
    return 0;
}
