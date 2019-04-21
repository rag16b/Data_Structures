//-------HASHTABLE.H--------
//
// Ryan Gutierrez
// COP4530 - 0001
// Project 5
// Goals: Understand and get familiar with the data structure hash tables,
//        and its applications in managing user accounts.
// Use: This is the declaration of the member functions of the HashTable
//      class.

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <iterator>
#include <algorithm>

// max_prime is used by the helpful functions provided
// to you.
static const unsigned int max_prime = 1301081;
// the default_capacity is used if the initial capacity 
// of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 11;

namespace cop4530 {
	template <typename K, typename V>
	class HashTable {
		public:
			HashTable(size_t size);	// constructor
			~HashTable();		// destructor
			bool contains(const K &k) const;	// checks if key is in hashtable
			bool match(const std::pair<K, V> & kv) const;	// checks if key-value pair is in hashtable
			bool insert(const std::pair<K, V> & kv);	// add the key-value pair to the hashtable
			bool insert(std::pair<K, V> && kv);		// move version of insert
			bool remove(const K &k);	// delete the key k and corresponding value if in hashtable 
			void clear();			// delete all elements in hashtable (calls makeEmpty())
			bool load(const char * filename);	// load the contents of file into hashtable
			void dump() const;	// dilpay all entries in hashtable
			size_t size() const;	// return the number of elements in the hash table
			bool write_to_file(const char * filename) const;	// write all hashtable elements to file
		private:
			// private member functions
			void makeEmpty();		// deletes all elements in the hashtable
			void rehash();			// called when num of elements in hash table is > size of vector
			size_t myhash(const K &k) const;// returns the index of the vector entry where k should be stored
			// private memebr functions provided by professor
			unsigned long prime_below(unsigned long);	// determines a new proper underlying vector size
			void setPrimes(std::vector<unsigned long> &);	// sets all prime number indexes to 1
			
			// private member data
			std::vector< std::list<std::pair<K, V>> > table;
			size_t tableSize;
	};
	#include "hashtable.hpp"
}
#endif
