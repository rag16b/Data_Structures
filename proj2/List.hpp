//-------LIST.HPP-------
//
// Ryan Gutierrez
// COP4530 - 0001
// Project 2
// Understanding generic programming and information hiding by 
//  developing generic containers. Getting familiar with the 
//  concept of class template and its usage. Use of nested 
//  (iterator) classes. Use of namespace. Operator overloading.

// ATTENTION GRADER: Note that the functions with a bunch of tilde's ("~") commented
//		      next to them are functions that I wrote. All other functions
//		      were retrieved from the textbook (some edits were made to all four
//		      begin() and end() functions as per the professors' recommendations
//		      in his office hours).

#include "List.h"

// CONST_ITERATOR MEMBERS-------------------------------------------
template <typename T>
List<T>::const_iterator::const_iterator() : current{ nullptr }
	{}
template <typename T>
const T & List<T>::const_iterator::operator*() const 
	{ return retrieve(); }

template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++(){
	current = current->next;
	return *this; 
}
template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int){
	const_iterator old = *this;
	++(*this);
	return old;
}
template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--(){
	current = current->prev;
	return *this; 
}
template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int){
	const_iterator old = *this;
	--(*this);
	return old;
}

template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const
	{ return current == rhs.current; }
template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const
	{ return !(*this == rhs.current); }

template <typename T>
T & List<T>::const_iterator::retrieve() const
	{ return current->data; }
template <typename T>
List<T>::const_iterator::const_iterator( Node *p ) : current{ p }
	{}
// end const_iterator member function implementations---------------

// ITERATOR MEMBERS-------------------------------------------------
template <typename T>
List<T>::iterator::iterator()
	{}
template <typename T>
T & List<T>::iterator::operator*()
	{ return const_iterator::retrieve(); }
template <typename T>
const T & List<T>::iterator::operator*() const
	{ return const_iterator::operator*(); }

template <typename T>
typename List<T>::iterator & List<T>::iterator::operator++(){
	this->current = this->current->next;
	return *this;
}
template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int){
	iterator old = *this;
	++(*this);
	return old;
}
template <typename T>
typename List<T>::iterator & List<T>::iterator::operator--(){
	this->current = this->current->prev;
	return *this;
}
template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int){	// try calling const_iterator version of this
	iterator old = *this;
	--(*this);
	return old;
}

template <typename T>
List<T>::iterator::iterator( Node *p ) : const_iterator{ p }
	{}
// end iterator member function implementations---------------------

// LIST MEMEBERS----------------------------------------------------
template <typename T>
List<T>::List()
	{ init(); }
template <typename T>
List<T>::List(const List &rhs){
	init();
	for ( auto & x : rhs )
		push_back( x );
}
template <typename T>
List<T>::List(List && rhs) : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }{
	rhs.theSize = 0;
	rhs.head = nullptr;
	rhs.tail = nullptr;
}
template <typename T>		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
List<T>::List(int num, const T & val){
	init();
	for (int i = 0; i < num; i++)
		push_front(val);
}
template <typename T>		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
List<T>::List(const_iterator start, const_iterator end){
	init();
	while(start != end)
		push_back((start++).current->data);
}

template <typename T>
List<T>::~List(){
	clear();
	delete head;
	delete tail;
}

template <typename T>
const List<T> & List<T>::operator=(const List<T> &rhs){
	List copy = rhs;
	std::swap( *this, copy );
	return *this;
}
template <typename T>
List<T> & List<T>::operator=( List && rhs){
	std::swap( theSize, rhs.theSize );
	std::swap( head, rhs.head );
	std::swap( tail, rhs.tail );
}

template <typename T>
int List<T>::size() const
	{ return theSize; }
template <typename T>
bool List<T>::empty() const
	{ return size() == 0; }
template <typename T>
void List<T>::clear(){
	while( !empty() )
		pop_front();
}
template <typename T>	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void List<T>::reverse(){
	List<T>::iterator itr = begin();
	List<T> temp;
	while(itr != end())
		temp.push_front((itr++).current->data);
	*this = temp;
}

template <typename T>
T & List<T>::front()
	{ return *begin(); }
template <typename T>
const T & List<T>::front() const
	{ return *begin(); }
template <typename T>
T & List<T>::back()
	{ return *--end(); }
template <typename T>
const T & List<T>::back() const
	{ return *--end(); }

template <typename T>
void List<T>::push_front(const T & val)
	{ insert(begin(),val); }
template <typename T>
void List<T>::push_front(T && val)
	{ insert(begin(),std::move(val)); }
template <typename T>
void List<T>::push_back(const T & val)
	{ insert(end(),val); }
template <typename T>
void List<T>::push_back(T && val)
	{ insert(end(),std::move(val)); }
template <typename T>
void List<T>::pop_front()
	{ erase(begin()); }
template <typename T>
void List<T>::pop_back()
	{ erase(--end()); }

template <typename T>	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void List<T>::remove(const T & val){
	List<T>::iterator temp = begin();
	while(temp != end()){
		if(*temp == val)
			erase(temp);
		temp++;
	}
}

template <typename T>	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void List<T>::print(std::ostream & os, char ofc) const{
	List<T>::const_iterator temp = begin();
	while(temp != end())
		os << *(temp++) << ofc;
}

template <typename T>
typename List<T>::iterator List<T>::begin()
	{ return { iterator(head->next) }; }
template <typename T>
typename List<T>::const_iterator List<T>::begin() const
	{ return { iterator(head->next) }; }
template <typename T>
typename List<T>::iterator List<T>::end()
	{ return { iterator(tail) }; }
template <typename T>
typename List<T>::const_iterator List<T>::end() const
	{ return { iterator(tail) }; }
template <typename T>
typename List<T>::iterator List<T>::insert( List<T>::iterator itr, const T& val ){
	Node *p = itr.current;
	theSize++;
	return { p->prev = p->prev->next = new Node{val,p->prev,p} };
}
template <typename T>
typename List<T>::iterator List<T>::insert( List<T>::iterator itr, T && val ){
	Node *p = itr.current;
	theSize++;
	return { p->prev = p->prev->next = new Node{std::move(val),p->prev,p} };	
}
template <typename T>
typename List<T>::iterator List<T>::erase( List<T>::iterator itr ){
	Node *p = itr.current;
	iterator retVal{ p->next };
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	theSize--;
	return retVal;
}
template <typename T>
typename List<T>::iterator List<T>::erase( List<T>::iterator start, iterator end ){
	for( iterator itr = start; itr != end; )
		itr = erase( itr );
	return end;
}

template <typename T>
void List<T>::init(){
	theSize = 0;
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->prev = head;
}
// end List function implementations--------------------------------

// GLOBAL FUNCTION DEFINITIONS--------------------------------------
template <typename T>	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool operator==(const List<T> & lhs, const List<T> & rhs){
	if (lhs.size() == rhs.size()){
		typename List<T>::const_iterator itrL = lhs.begin();
		typename List<T>::const_iterator itrR = rhs.begin();
		for (int i = 0; i < lhs.size(); i++){
			if (*(itrL++) != *(itrR++))
				return false;
		}
		return true;
	}
	return false;
}
template <typename T>	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool operator!=(const List<T> & lhs, const List<T> & rhs){
	return !(lhs == rhs);
}
template <typename T>	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::ostream & operator<<(std::ostream & os, const List<T> & l){
	l.print(os);
	return os;
}
// end global function implementations------------------------------
