#include <iostream>
#include <fstream>
#include <cstring> 

int main (int argc, char* argv[]) {
  	if (argc < 2) {
    	std::cerr << "Please provide a file." << std::endl;
    	return 1;
	}

	std::ifstream input;
	input.open(argv[1]);

	int num;
	input >> num;

	std::string *output=new std::string[num];
	for (int i=num-1; i>=0; i--) {
		input >> output[i];
	}

	for (int i=0; i<num; i++) {
		std::cout << output[i] << std::endl;
	}

	delete[] output;
}