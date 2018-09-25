# CS 104 Student Repository

- **Name**: Julia Wisnia
- **USC ID**: 2096592657
- **Email**: wisnia@usc.edu

PARSER
My parser has 5 helper functions to calculate expressions.

compute()
This function is responsible for the main stack containing the expressions.
It pushes everything except closed parens that it finds, and calls closedParen()
when a closed paren is found. It also checks for different edge cases with each
operator, such as no operator next to a number, etc. These are all described by
comments in the code.

removeSpaces()
This function is called before anything is applied to the string. It removes
spaces from each line so that I can more easily tell when operators are misplaced.
It takes in the line, then creates another string. Everything from the original line
that is not a whitespace is added to the new string, then this is returned.

checkBalancedParens()
The first one checks for balanced parentheses by adding the number 
of open parens to  a count int, then subtracting the closed parens. 
If not zero, the expression is malformed.

closedParen()
This function makes up the bulk of the assignment, and triggers
when a closedParen is found, carrying out calculations. This function
works by popping ints from the main stack in "compute", and concatanating
them, then pushing that onto a calculation stack. Shift operators are
accounted for before it is pushed. Then it pushes operations, makes sure
that there are not mixed operators, and pushes the final number back onto
the main stack for compute, so that any cases outside those parens will 
have access to the previous sums.

noParentheses()
This function is called when there are no parentheses, but still an expression.
It concatanates ints with shift operators, but returns false if there are any
other operators without parentheses.

main()
First, my main makes sure that there are enough arguments and that the file
inputted can open. Then, all it does is read lines from the file, and call compute
on them one by one. The rest of the functions are called within compute.
