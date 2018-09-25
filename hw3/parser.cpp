#include <iostream>
#include <fstream>
#include <sstream>
#include "stackint.h"

bool CheckBalancedParentheses(std::string input) {
	StackInt stk;
    int len=input.size();
    int cnt=0;

    //empty line
    if (len==0) return true;

    for (int i=0; i<len; i++) {
    	if (input[i]=='(') {
    		cnt++;
    	}
    	else if(input[i]==')') {
    		cnt--;
    	}
    }

    if(cnt==0) return true;
    
    else return false;
}

int closedParen(StackInt &stk, int &total) {
	const int OPEN_PAREN=-2;
	const int PLUS=-4;
	const int MULTIPLY=-5;
	const int SHIFTLEFT=-6;
	const int SHIFTRIGHT=-7;

	//only closed parens
	if (stk.empty()) return -3;

	bool flag=false;
	StackInt calculate;

	while (stk.top()!=OPEN_PAREN) {
		int n=1;
		int val=0;
		bool start=false;
		//while the top is not an operator
		while (stk.top()>-2 && !stk.empty()) {
			start=true;
			val+=(stk.top())*n;
			stk.pop();
			n*=10;
		}

		while(stk.top()==SHIFTRIGHT || stk.top()==SHIFTLEFT) {
			//if there's a shift operator with nothing in front
			if (!start) {
				return -3;
			}

			while (stk.top()==SHIFTRIGHT) {
				stk.pop();
				val=val/2;
			}

			while (stk.top()==SHIFTLEFT) {
				stk.pop();
				val=val*2;
			}
		}
		//push value onto new stack
		calculate.push(val);
		if (stk.top()==MULTIPLY||stk.top()==PLUS) {
			flag=true;
			//operator without an int in front
			if (!start) {
				//std::cout<<"Line 97"<<std::endl;
				return -3;
			}
			calculate.push(stk.top());
			stk.pop();
		}
	}
	//if there are no operators inside the parentheses
	if (flag==false) {
		return -3;
	}
	stk.pop();

	//we now have a stack calculate with just what is inside the parentheses
	total=calculate.top();
	calculate.pop();

	bool add=false;
	bool mult=false;

	while (!calculate.empty()) {
		if (calculate.top()==PLUS) {
			add=true;
			calculate.pop();
			total+=calculate.top();
			calculate.pop();
		}

		else if (calculate.top()==MULTIPLY) {
			mult=true;
			calculate.pop();
			total*=calculate.top();
			calculate.pop();
		}
		//should never trigger
		else return -3;
	}
	//mixing operators inside parentheses
	if (add && mult) return -3;

	stk.push(total);
	return 1;
}

int noParentheses(StackInt &stk, int &total) {
	//const int OPEN_PAREN=-2;
	const int PLUS=-4;
	const int MULTIPLY=-5;
	const int SHIFTLEFT=-6;
	const int SHIFTRIGHT=-7;

	StackInt calculate;

	int n=1;
	int val=0;
	bool start=false;
	//while the top is not an operator
	while (stk.top()>-2 && !stk.empty()) {
		start=true;
		val+=(stk.top())*n;
		stk.pop();
		n*=10;
	}

	while(stk.top()==SHIFTRIGHT || stk.top()==SHIFTLEFT) {
		//no int in front
		if (!start) return -3; 

		while (stk.top()==SHIFTRIGHT) {
			stk.pop();
			val=val/2;
		}

		while (stk.top()==SHIFTLEFT) {
			stk.pop();
			val=val*2;
		}
	}
	//push value onto new stack
	calculate.push(val);

	//should not have operators w/o parentheses
	if (stk.top()==MULTIPLY || stk.top()==PLUS) return -3;

	stk.pop();

	//we now have a stack calculate with just what is inside the parentheses
	total=calculate.top();
	calculate.pop();

	stk.push(total);
	return 1;
}

std::string removeSpaces(std::string str) { 
    std::string temp; 

    int len=str.size();
    for (int i=0; i<len; i++) {
    	if (!isspace(str[i])) {
    		temp=temp+str[i];
    	}

    	else continue;
    }

    return temp; 
} 

void compute(std::string output) {
	StackInt stk;
	int total=0;
	bool paren=false;

	const int OPEN_PAREN=-2;
	const int PLUS=-4;
	const int MULTIPLY=-5;
	const int SHIFTLEFT=-6;
	const int SHIFTRIGHT=-7;

	std::string input=removeSpaces(output);

	if (!CheckBalancedParentheses(input)) {
		std::cout<<"Malformed"<<std::endl;
		return;
	}

	int len=input.size();
	//empty line
	if (len==0) return;

	for (int i=0; i<len; i++) {
		if (input[i]=='(') {
			paren=true;
			//if there's a number with no operator in front
			if (!stk.empty() && stk.top()>-2) {
				std::cout<<"Malformed"<<std::endl;
				return;
			}
			else stk.push(OPEN_PAREN);
		}
		else if (input[i]=='+') {
			//operator without parentheses
			if (!paren) {
				std::cout<<"Malformed"<<std::endl;
				return;
			}
			else stk.push(PLUS);
		}
		else if (input[i]=='*') {
			//operator without parentheses
			if (!paren) {
				std::cout<<"Malformed"<<std::endl;
				return;
			}
			else stk.push(MULTIPLY);
		}
		else if (input[i]=='<') stk.push(SHIFTLEFT); 
		else if (input[i]=='>') stk.push(SHIFTRIGHT);
		else if (input[i]==')') {
			int j=closedParen(stk, total);
			//problem returned from closedParen
			if (j<0) {
				std::cout<<"Malformed"<<std::endl;
				return;
			}
		}
		else {
			//if shifts after int
			if (input[i+1]=='<' || input[i+1]=='>') {
				std::cout<<"Malformed"<<std::endl;
				return;
			}
			//if there's a number after the parentheses w/o operator
			if (input[i-1]==')') {
				std::cout<<"Malformed"<<std::endl;
				return;
			}
			int num=input[i]-'0'; //convert to int
			if (num==0||num==1||num==2||num==3||num==4||num==5||num==6
				||num==7||num==8||num==9) {
				stk.push(num);
			}
			//if it's a character other than accepted ones or int
			else {
				std::cout<<"Malformed"<<std::endl;
				return;
			}
		}
	}

	//there were no parentheses
	if (!stk.empty()) {
		int j=noParentheses(stk, total);
		if (j<0) {
			std::cout<<"Malformed"<<std::endl;
			return;
		}
	}

	std::cout<<total<<std::endl;
}

int main(int argc, char* argv[]) {
	//wrong number of arguments
	if (argc!=2) return -1;

	std::ifstream ifile;
	ifile.open(argv[1]);

	//cannot open file
	if (ifile.fail()) return -1;

	std::string line;

	//check for end of file flag
	while (!ifile.eof()) {
		getline(ifile, line);
		compute(line);
	}

	return 0;
}