#include <iostream>
#include <sstream>
#include <string>
#include "stack.h"

using namespace std;
using namespace cop4530;

bool isOperator(string);
int precedence(char);

int main(){

	string in, post;	// in takes input (either an expression or "exit"). post will hold the final expression
	string op;		// current string (Operator/Operand)
	string lastOp;		// will store previous Operator/Operand
	Stack<char> tokens;	// stack for evaluating postfix expressions
	bool error = false;

	cout << "Enter infix expression (\"exit\" to quit): ";

	while(getline(cin, in) && in != "exit"){
		post = "";	// resetting
		stringstream sstream(in);
		
		// converting from infix to postfix************************************************
		while(getline(sstream, op, ' ')){
			if (op != "(" && op != ")" && !isOperator(op))
				post += (op + " ");
			else if (op == "(")
				tokens.push(op[0]);
			else if (isOperator(op)){
				string s(1,tokens.top());
				//if (tokens.top() == '(')		// testing
				//	cout << tokens << endl;
				while(!tokens.empty() && tokens.top() != '(' && (isOperator(s) && precedence(op[0]) <= precedence(tokens.top()))){
					post += tokens.top();
					post += " ";
					tokens.pop();
					string s(1,tokens.top());
				}
				tokens.push(op[0]);
			}
			else if (op == ")"){
				if (isOperator(lastOp)){
					cout << "Error: Mismatched parentheses." << endl;
					error = true;
					break;
				}
				while(tokens.top() != '('){
					if (tokens.empty()){
						cout << "Error: Stack was emptied before finding matching parenthesis." << endl;
						error = true;
						break;
					}
					post += tokens.top();
					post += " ";
					tokens.pop();
				}
				if (error == true)
					break;
				tokens.pop();
			}
			lastOp = op;
		}
		// dealing with end of input
		if (isOperator(op) || op == "("){
			cout << "Error: Invalid expression" << endl;
			error = true;
			break;
		}
		while(!tokens.empty()){
			if (tokens.top() == '('){
				cout << "Error: Mismatched parentheses." << endl;
				error = true;
				break;
			}
			post += tokens.top();
			post += " ";
			tokens.pop();
		}

		// printing postfix after conversion from infix
		if (error == false)
			cout << "\nPostfix expression: " << post << endl;

		// postfix evaluation**************************************************************
		

		cout << "Enter infix expression (\"exit\" to quit): ";
	}

	return 0;
}

bool isOperator(string temp){
	if (temp == "*" || temp == "/" || temp == "+" || temp == "-")
		return true;
	return false;
}

int precedence(char temp){
	if (temp == '*' || temp == '/')
		return 2;
	else if (temp == '+' || temp == '-')
		return 1;
}
