#include <iostream>
#include <stack>
#include <string>
#include <sstream>

int main() {
    std::string read;
    std::cin >> read;
    int north = 0;
    int west = 0;

    // if north, add 1, south, subtract 1
    for (size_t i = 0; i < read.size(); i++) {
        if (read[i] != 'n' && read[i] != 'e' && read[i] != 'w' && read[i] != 's') {
            std::cout << "invalid" << std::endl;
            return -1;
        }
        
        if (read[i] == 'n') north++;
        else if (read[i] == 's') north--;
        else if (read[i] == 'w') west++;
        else if (read[i] == 'e') west--;
    }

    if ((north == 0) && (west == 0)) std::cout << "rolled up" << std::endl;
    else std::cout << "not rolled up" <<std::endl;

    return 0;
}