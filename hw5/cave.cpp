#include <iostream>
#include <stack>
#include <string>
#include <sstream>

int main() {
    std::string read;
    std::cin >> read;
    std::stack<char> stk;

    for (size_t i = 0; i < read.size(); i++) {
        if (read[i] != 'n' && read[i] != 'e' && read[i] != 'w' && read[i] != 's') {
            std::cout << "invalid" << std::endl;
            return -1;
        }

        stk.push(read[i]);

        if ((i - 1) >= 0) {
            int j = i - 1;
            if ((read[i] == 'n' && read[j] == 's') || (read[i] == 's' && read[j] == 'n') || (read[i] == 'w' && read[j] == 'e') || (read[i] == 'e' && read[j] == 'w')) {
                stk.pop();
                stk.pop();
            }
        }
    }

    char dir, dir2;
    while (!stk.empty()) {
        dir = stk.top();
        dir2 = stk.top();
        if ((dir == 's' && dir2 != 'n') || (dir == 'n' && dir2 != 's') || (dir == 'w' && dir2 != 'e') || (dir == 'e' && dir2 != 'w')) {
            std::cout << "not rolled up " << std::endl; 
            return 0;
        }
        stk.pop();
        stk.pop();
    }

    std::cout << "rolled up" << std::endl;
    return 0;
}