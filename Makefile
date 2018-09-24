all: parser
	
parser: parser.cpp circular_list_int.cpp stackint.cpp
	g++ -g -Wall -std=c++11 parser.cpp circular_list_int.cpp stackint.cpp -o parser