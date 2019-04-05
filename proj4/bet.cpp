//-------BET.CPP--------
//
// Ryan Gutierrez
// COP4530 - 0001
// Project 4
// Goals: Experience with binary tree and its application in converting
//        postfix expressions into infix expressions, experience in
//        developing recursive algorithms.
// Use: This is the declaration of  a binary expression tree which will
//      be used to convert postfix expressions into infix expressions

#include "bet.h"
#include <iostream>
#include <sstream>

using namespace std;

// PUBLIC MEMBER FUNCTIONS
BET::BET() { root = nullptr; }

BET::BET(const string postfix) { buildFromPostfix(postfix); }

BET::BET(const BET& bet) {
	clear();
	root = clone(bet.root);
	ops.push(root);
}

BET::~BET() {
	makeEmpty(root);
	delete root;
}

bool BET::buildFromPostfix(const string postfix) {
	bool valid = true;	// flag that will be set false in the event of an error
	string error;
	// string library already exist because I included in bet.h
	if (!empty()) {
		clear();
		makeEmpty(root);
	}
	//for (int i = 0; i < postfix.length(); i++) {
	stringstream sstream(postfix);
	string s;
	while (getline(sstream,s,' ')) {
		if (isOperand(s)) {	// if its an operand
			// create new node with the operand
			BinaryNode* temp = new BinaryNode;
			temp->element = s;
			temp->lNode = nullptr;
			temp->rNode = nullptr;
			// push new node onto stack
			ops.push(temp);
				// testing
				//cout << temp->element << endl;
		}
		else if (isOperator(s)) {
			// pop corresponding operands from stack
			BinaryNode *lNode, *rNode;
			if (!ops.empty()) {
				lNode = ops.top();
				ops.pop();
			}
			else {
				valid = false;
				break;
			}
			if (!ops.empty()) {
				rNode = ops.top();
				ops.pop();
			}
			else {
				valid = false;
				break;
			}
			// creating a new node with the oprator and corresponding operands
			BinaryNode* newNode = new BinaryNode;
			newNode->element = s;
			newNode->lNode = lNode;
			newNode->rNode = rNode;
			// push new node onto stack
			ops.push(newNode);
				// testing
				//cout << newNode->element << endl;
		}
	}
	if (!ops.empty()) {
		root = ops.top();
		ops.pop();
		if (!ops.empty())
			valid = false;
	}
	else
		valid = false;
	
	if (valid == false) {
		cout << "Invalid postfix expression... " << error << endl;
		// clean up any partially made trees
		makeEmpty(root);
		clear();
		return false;
	}
	return valid;
}// end buildFromPostfix

const BET & BET::operator=(const BET & bet) {
	clear();
	clone(root);
	ops.push(root);
	return *this;
}

void BET::printInfixExpression() { printInfixExpression(root); }

void BET::printPostfixExpression() { printPostfixExpression(root); }

size_t BET::size() { return size(root); }

size_t BET::leaf_nodes() { return leaf_noes(root); }

bool BET::empty() {
	if (root == nullptr)
		return true;
	return false;
}

// PRIVATE MEMBER FUNCTIONS
// clears the stack
void BET::clear() {
	while(!ops.empty())
		ops.pop();
	root = nullptr;
}

bool BET::isOperand(string str) {
	if (str.length() == 1) {
		char c = str[0];
		return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'));
	}
	return true;
}

bool BET::isOperator(string s) { return (s == "*" || s == "/" || s == "+" || s == "-"); }

// RECURSIVELY DEFINED PRIVATE MEMBER FUNCTIONS
void BET::makeEmpty(BinaryNode* &t) {
	if (t != nullptr) {		// need to check bc if it is, then there is a segfault
		if (t->lNode != nullptr)
			makeEmpty(t->lNode);
		else if (t->rNode != nullptr)
			makeEmpty(t->rNode);
		else
			delete t;
	}
	t = nullptr;
}

BET::BinaryNode* BET::clone(BinaryNode *t) const{
	if (t != nullptr) {
		BinaryNode *temp = new BinaryNode;
		temp->element = t->element;
		temp->lNode = clone(t->lNode);
		temp->rNode = clone(t->rNode);
		return temp;
	}
	return nullptr;
}

void BET::printInfixExpression(BinaryNode *n) {
	
}

void BET::printPostfixExpression(BinaryNode *n) {
	
}

size_t BET::size(BinaryNode *t) {
	
}

size_t BET::leaf_nodes(BinaryNode *t) {
	
}
