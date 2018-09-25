#include <iostream>
#include <fstream>
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
    // for (int i=0; i<len; i++) {
    // 	if (input[i]=='('||input[i]==')') {
    // 		cnt++;
    // 	}
    // }

    // if (cnt%2!=0) return false;

    // for (int i=0; i<len; i++) {
    // 	if (input[i]=='(') {
    // 		stk.push(input[i]);
    // 	}
    // 	//if any other types of parens
    // 	if (input[i]=='['||input[i]==']'||input[i]=='{'||input[i]=='}') {
    // 		return false;
    // 	}
    // }

    // for (int j=0; j<len; j++) {
    // 	//should not have operators +/* without parentheses
    // 	if (stk.empty() && (input[j]=='+'||input[j]=='*')) {
    // 		return false;
    // 	}

    // 	else if (input[j]==')') {
    // 		stk.pop();
    // 	}
    // }

    // if (!stk.empty()) {
    // 	return false;
    // }

    // return true;
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
				//std::cout<<"Line 77"<<std::endl;
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
	//std::cout<<calculate.top()<<std::endl;
	//if there are no operators inside the parentheses
	if (flag==false) {
		//std::cout<<"Line 106"<<std::endl;
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
	if (stk.top()==MULTIPLY||stk.top()==PLUS) return -3;

	stk.pop();

	//we now have a stack calculate with just what is inside the parentheses
	total=calculate.top();
	calculate.pop();

	stk.push(total);
	return 1;
}

void compute(std::string input) {
	StackInt stk;
	int total=0;

	const int OPEN_PAREN=-2;
	const int PLUS=-4;
	const int MULTIPLY=-5;
	const int SHIFTLEFT=-6;
	const int SHIFTRIGHT=-7;

	if (!CheckBalancedParentheses(input)) {
		std::cout<<"Malformed"<<std::endl;
		return;
	}

	int len=input.size();

	//empty line
	if (len==0) return;

	bool notSpace=false;
	for (int i=0; i<len; i++) {
		if (!isspace(input[i])) notSpace=true;
	}
	//line only contains spaces
	if (!notSpace) return;

	for (int i=0; i<len; i++) {
		if (input[i]=='(') {
			if (!stk.empty() && stk.top()>-2) {
				std::cout<<"Malformed"<<std::endl;
				return;
			}
			else stk.push(OPEN_PAREN);
		}
		else if (input[i]=='+') stk.push(PLUS);
		else if (input[i]=='*') stk.push(MULTIPLY);
		else if (input[i]=='<') stk.push(SHIFTLEFT);
		else if (input[i]=='>') stk.push(SHIFTRIGHT);
		else if (input[i]==' ') continue;
		else if (input[i]=='	') continue;
		else if (input[i]==')') {
			int j=closedParen(stk, total);
			if (j<0) {
				std::cout<<"Malformed"<<std::endl;
				return;
			}
		}
		else {
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