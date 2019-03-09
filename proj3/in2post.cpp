#include <iostream>
#include <sstream>
#include <string>
#include "stack.h"

using namespace std;
using namespace cop4530;

bool isOperator(string);
int precedence(char);
bool evaluatable(string);
string calculate(string,string,string);

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
			// dealing with extra spaces
			while(sstream.peek() == ' ')
				sstream.ignore();
			// conversion
			if (op != "(" && op != ")" && !isOperator(op))
				post += (op + " ");
			else if (op == "(")
				tokens.push(op[0]);
			else if (isOperator(op)){
				string s(1,tokens.top());
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
			cout << "\nPostfix expression: " << post << endl;	// had to add \n for file as stdin. not sure why

		// postfix evaluation**************************************************************
		if (evaluatable(post)){
			Stack<string> values;		// new string stack to deal with operands
			stringstream sstream(post);
			string lhs, rhs;		// used to send operands to calculate function
			double result;			// will store final result
			while(getline(sstream, op, ' ')){
				if (!isOperator(op))
					values.push(op);
				else{
					if (values.size() < 2){
						cout << "Error: Too few operands to do a calculation." << endl;
						error = true;
						break;
					}
					rhs = values.top(); values.pop();
					lhs = values.top(); values.pop();
					values.push(calculate(lhs,rhs,op));
				}
			}
			if (values.size() == 1)
				result = atof(values.top().c_str());
			else if (values.size() == 0)
				result = 0.0;
			else{
				cout << "Error: Too many operands were left over at the end of calculation." << endl;
				error = true;
				break;
			}

			if (error == false)
				cout << "Postfix evaluation: " << post << "= " << result << endl;
		}
		else
			cout << "Postfix evaluation: " << post << "= " << post << endl;

		tokens.clear();		// resetting
		error = false;
		cout << "Enter infix expression (\"exit\" to quit): ";
	}

	return 0;
}

bool isOperator(string temp){	// returns true if the given string is an operator
	if (temp == "*" || temp == "/" || temp == "+" || temp == "-")
		return true;
	return false;
}

int precedence(char temp){	// returns a precednce value depending on the operand
	if (temp == '*' || temp == '/')
		return 2;
	else if (temp == '+' || temp == '-')
		return 1;
}

bool evaluatable(string temp){	// returns true if the postfix expression contains only numerical operands
	for (int i = 0; i < temp.size(); i++)
		if (isalpha(temp[i]))
			return false;
	return true;
}

// calculates a single operation
string calculate(string operand1, string operand2, string oprator){
	double op1 = atof(operand1.c_str());
	double op2 = atof(operand2.c_str());
	double result = 0;
	char c = oprator[0];

	switch(c){
		case '*':
			result = op1 * op2;
			break;
		case '/':
			result = op1 / op2;
			break;
		case '+':
			result = op1 + op2;
			break;
		case '-':
			result = op1 - op2;
			break;
	}
	return (to_string(result));
}
