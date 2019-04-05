//-------BET.H--------
//
// Ryan Gutierrez
// COP4530 - 0001
// Project 4
// Goals: Experience with binary tree and its application in converting
//	  postfix expressions into infix expressions, experience in
//	  developing recursive algorithms.
// Use: This is the declaration of  a binary expression tree which will
//	be used to convert postfix expressions into infix expressions

#include <stack>	// may change to something else later
#include <string>	// not sure why I would need this

using namespace std;

class BET{
	public:
		BET();				// default zero-parameter constructor.
		BET(const string postfix);	// one-parameter constructor, where parameter "postfix" is string containing a postfix expression. The tree should be built based on the postfix expression. Tokens in the postfix expression are separated by space.
		BET(const BET&);			// copy constructor.
		~BET();				// destructor.
		bool buildFromPostfix(const string postfix);	// parameter "postfix" is string containing a postfix expression. The tree should be built based on the postfix expression. Tokens in the postfix expression are separated by space. If the tree contains nodes before the function is called, you need to first delete the existing nodes. Return true if the new tree is built successfully. Return false if an error is encountered.
		const BET & operator= (const BET &);		// assignment operator.
		void printInfixExpression();		// call the private version of the printInfixExpression function to print out the infix expression.
		void printPostfixExpression();		// call the private version of the printPostfixExpression function to print out the postfix expression.
		size_t size();		// call the  private version of the size function to return the number of nodes in the tree.
		size_t leaf_nodes();	// call the private version of the leaf_nodes function to return the number of leaf nodes in the tree.
		bool empty();		//return true if the tree is empty. Return false otherwise.
	private:
		// private member data
		struct BinaryNode{
			string element;
			BinaryNode* lNode;
			BinaryNode* rNode;
		};

		stack<BinaryNode*> ops;	// a stack that will hold binary nodes containing operators and operands
		BinaryNode* root;	// root node

		void clear();		// clears the stack
		bool isOperand(string c); // returns true if c is an operand
		bool isOperator(string c);// returns true if c is an operator

		// recursively defined private member functions
		void makeEmpty(BinaryNode* &t);			// delete all nodes in the subtree pointed to by t. Called by functions such as the destructor.
		BinaryNode * clone(BinaryNode *t) const;	// clone all nodes in the subtree pointed to by t. Called by functions such as the assignment operator=.

		void printInfixExpression(BinaryNode *n);	// print to the standard output the corresponding infix expression. Note that you may need to add parentheses depending on the precedence of operators. You should not have unnecessary parentheses.
		void printPostfixExpression(BinaryNode *n);	// print to the standard output the corresponding postfix expression.
		size_t size(BinaryNode *t);			// return the number of nodes in the subtree pointed to by t.
		size_t leaf_nodes(BinaryNode *t);		// return the number of leaf nodes in the subtree pointed to by t.
};
