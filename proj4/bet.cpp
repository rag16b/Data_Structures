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
	root = clone(bet.root);
	ops.push(root);
	return *this;
}

void BET::printInfixExpression() { printInfixExpression(root); cout << endl; }

void BET::printPostfixExpression() { printPostfixExpression(root); cout << endl; }

size_t BET::size() { return size(root); }

size_t BET::leaf_nodes() { return leaf_nodes(root); }

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

bool BET::isLeaf(BinaryNode *n) { return (n->lNode == nullptr && n->rNode == nullptr); }

int BET::precedence(string s) {
	if (s == "*" || s == "/")
		return 2;
	else if (s == "+" || s == "-")
		return 1;
	else
		return 0;
}

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
	if (n != nullptr) {
		//if ((isOperator(n->element) && isOperator(n->rNode->element)) || ((isOperator(n->element) && isOperator(n->lNode->element)))) {
		if (isOperator(n->element) && isOperator(n->rNode->element) && precedence(n->element) > precedence(n->rNode->element)) {
			if (!isLeaf(n->rNode)) {
				if (isOperand(n->rNode->rNode->element))
					cout << "( ";
			}
		}
		// print left child node (r bc I must have stored it wrong)
		printInfixExpression(n->rNode);
		if (isOperator(n->element) && !isOperand(n->rNode->element) && precedence(n->element) > precedence(n->rNode->element))
			cout << ") ";

		// print current node
		cout << n->element << " ";

		
		if (isOperator(n->element) && isOperator(n->lNode->element) && precedence(n->element) >= precedence(n->lNode->element)) {
			if (!isLeaf(n->lNode)) {
				if (isOperand(n->lNode->rNode->element))
				cout << "( ";
			}
		}
		// print right child node (l bc I must have stored it wrong)
		printInfixExpression(n->lNode);
		//if ((isOperator(n->element) && isOperator(n->rNode->element)) || (isOperator(n->element) && isOperator(n->lNode->element)))
		if (isOperator(n->element) && isOperator(n->lNode->element) && precedence(n->element) >= precedence(n->lNode->element))
			cout << ") ";
	}
}

void BET::printPostfixExpression(BinaryNode *n) {
	if (n != nullptr) {
		//if (n->lNode == nullptr)
			printPostfixExpression(n->rNode);
		//else if (n->rNode == nullptr)
			printPostfixExpression(n->lNode);
		//else
			cout << n->element << " ";
	}
}

size_t BET::size(BinaryNode *t) {
	if (t == nullptr)	// in case of empty tree
		return 0;
	else
		return 1 + size(t->lNode) + size(t->rNode); // recursive call
}

size_t BET::leaf_nodes(BinaryNode *t) {
	if (t == nullptr)	// in case of empty tree
		return 0;
	else if(t->lNode == nullptr && t->rNode == nullptr)	// any node without children is a leaf
		return 1;
	else
		return 0 + leaf_nodes(t->lNode) + leaf_nodes(t->rNode);	// recursion
}
