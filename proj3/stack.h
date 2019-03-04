//-------STACK.H--------
//
// Ryan Gutierrez
// COP4530 - 0001
// Project 3
// Goals: (1) Implement a generic Stack as an adaptor class template, (2) Write 
//  a program that parses infix arithmetic expressions to postfix arithmetic 
//  expressions using a Stack, and (3) Write a program that evaluates postfix 
//  arithmetic expressions using a Stack.

#ifndef DL_STACK_H	// NOT SURE WHAT THIS DOES, JUST THAT IT WAS IN LIST.H
#define	DL_STACK_H	//  IN PROJECT 2
#include <iostream>

namespace cop4530 {

	template <typename T>
		class stack {
			private:
				int top;
			public:
				Stack();
				~Stack();
				Stack (const Stack<T>&); // copy constructor.   
				Stack(Stack<T> &&); // move constructor.
				Stack<T>& operator= (const Stack <T>&); // copy assignment operator=.
				Stack<T> & operator=(Stack<T> &&); // move assignment operator=
				bool empty() const; // returns true if the Stack contains no elements, and false otherwise.  
				void clear(); // delete all elements from the stack.
				void push(const T& x); // adds  x  to the Stack.   copy version.
				void push(T && x); // adds x to the Stack. move version.
				void pop(); // removes and discards the most recently added element of the Stack.  
				T& top(); // mutator that returns a reference to the most recently added element of the Stack.  
				const T& top() const; // accessor that returns the most recently added element of the Stack.  
				int size() const; // returns the number of elements stored in the Stack.

				// print elements of Stack to ostream os. ofc is the separator between elements in the stack when they are printed out.
				//  Note that print() prints elements in the opposite order of the Stack (that is, the oldest element should be printed first).
				void print(std::ostream& os, char ofc = ' ') const;
		}
	// overloading comparison operators
	template <typename T>
		std::ostream& operator<< (std::ostream& os, const Stack<T>& a);
	template <typename T>
		bool operator== (const Stack<T>& a, const Stack <T>& b);
	template <typename T>
		bool operator!= (const Stack<T>& a, const Stack <T>& b);

	// overloading output operator
	template <typename T>
		bool operator<= (const Stack<T>& a, const Stack <T>& b);

#include "stack.hpp"
}

#endif
