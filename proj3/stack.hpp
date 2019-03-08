//-------STACK.HPP--------
//
// Ryan Gutierrez
// COP4530 - 0001
// Project 3
// Goals: (1) Implement a generic Stack as an adaptor class template, (2) Write
//  a program that parses infix arithmetic expressions to postfix arithmetic
//  expressions using a Stack, and (3) Write a program that evaluates postfix
//  arithmetic expressions using a Stack.

#include "stack.h"

//----------- public member functions ------------
// CONSTRUCTOR
template <typename T>
Stack<T>::Stack() { }
// DESTRUCTOR
template <typename T>
Stack<T>::~Stack() { clear(); }
// COPY CONSTUCTOR
template <typename T>
Stack<T>::Stack(const Stack<T>& temp){		// copy constructor
	auto itr = temp.vecData.begin();
	for (int i = 0; i < temp.size(); i++,itr++)
		push(*itr);
}
// MOVE CONSTRUCTOR
template <typename T>
Stack<T>::Stack( Stack<T> && temp) : vecData{ temp.vecData }	// move constructor
	{ temp.clear(); }


// ASSIGNMENT OPERATORS
template <typename T>
Stack<T>& Stack<T>::operator= (const Stack<T>& temp){	// copy assign
	Stack<T> copy = temp;
	std::swap(*this,copy);
	return *this;
}
template <typename T>
Stack<T>& Stack<T>::operator= (Stack<T> && temp)	// move assign
	{ std::swap(vecData,temp.vecData); }

// MUTATORS
template <typename T>
void Stack<T>::clear()
	{ vecData.clear(); }
template <typename T>
void Stack<T>::push(const T& x)		// copy push
	{ vecData.push_back(x);	}	// the end of the vector is the top of the stack as explained in our textbook
template <typename T>
void Stack<T>::push(T && x)		// move push
	{ vecData.push_back(std::move(x)); }
template <typename T>
void Stack<T>::pop()
	{ vecData.pop_back(); }
// ACCESSORS
template <typename T>
bool Stack<T>::empty() const
	{ return (vecData.size() <= 0); }
template <typename T>
T& Stack<T>::top()
	{ return vecData.back(); }
template <typename T>
const T& Stack<T>::top() const
	{ return vecData.back(); }
template <typename T>
int Stack<T>::size() const
	{ return vecData.size(); }


// PRINT
template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const{
	auto itr = vecData.begin();
	for (int i = 0; i < size(); i++,itr++)
		os << *itr << ofc;
}


//------------- global non-member functions --------------
// insertion operator overload
template <typename T>
std::ostream& operator<< (std::ostream& os, const Stack<T>& a){
	a.print(os);
	return os;
}
// comparison operator overloads
template <typename T>
bool operator== (const Stack<T>& a, const Stack<T>& b){
	if (a.size() == b.size()){
		Stack<T> stkL(a), stkR(b);
		for (int i = 0; i < stkL.size(); i++){
			if (stkL.top() != stkR.top())
				return false;
			stkL.pop(), stkR.pop();
		}
		return true;
	}
	return false;
}
template <typename T>
bool operator!= (const Stack<T>& a, const Stack<T>& b)
	{ return !(a == b); }
template <typename T>
bool operator<= (const Stack<T>& a, const Stack<T>& b){
	if (a == b)
		return true;

	if (a.size() < b.size())
		return true;
	else if (a.size() == b.size()){
		Stack<T> stkL(a), stkR(b);
		for (int i = 0; i < stkL.size(); i++){
			if (stkL.top() > stkR.top())
				return false;
			stkL.pop(), stkR.pop();
		}
		return true;
	}
	return false;	
}
