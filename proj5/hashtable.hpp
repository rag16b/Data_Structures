//-------HASHTABLE.HPP--------
//
// Ryan Gutierrez
// COP4530 - 0001
// Project 5
// Goals: Understand and get familiar with the data structure hash tables,
//	  and its applications in managing user accounts.
// Use: This is the implementation of the member functions of the HashTable
//	class.

#include "hashtable.h"

//----------------------PUBLIC MEMBER FUNCTIONS---------------------------
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size = 101) {
	table.resize(prime_below(size));
	tableSize = 0;
}

template <typename K, typename V>
HashTable<K, V>::~HashTable() {
	clear();
}

template <typename K, typename V>
bool HashTable<K, V>::contains(const K &k) const {
	// get the given list at k as the possible list containing k. this will be done for a lot of functions
	std::list<std::pair<K, V>> currList = table[myhash(k)];
	for (auto & listPos : currList)
		if (k == listPos.first)		// first because the first part of the pair is the key
			return true;
	return false;
}

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> & kv) const {
	std::list<std::pair<K, V>> currList = table[myhash(kv.first)];
	if (currList.size() > 0) {
		for (auto & listPos : currList)
			if (kv.first == listPos.first && kv.second == listPos.second)	// if the key and value are both in the table
				return true;
	}
	return false;

}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> & kv) {
	// now I did it as a reference variable because I may need to change data within the table
	std::list<std::pair<K, V>> & currList = table[myhash(kv.first)];
	if (currList.size() > 0) {
		for (auto & listPos : currList) {
			if (kv.first == listPos.first && kv.second == listPos.second)	// if kv is already in the table return false
				return false;
			else if (kv.first == listPos.first) {	// if only the key is in the table, update the value
				listPos.second = kv.second;
				break;
			}
		}
		currList.push_back(kv);					// if the pair nor the key is found, add the pair to the list/table
	}
	else
		currList.push_back(kv);					// if the list is empty, add the pair
	
	if (++tableSize > table.size())	// resize if needed
		rehash();
	return true;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V> && kv) {			// works the same as non move insert; uses move funtion when needed
	// now I did it as a reference variable because I may need to change data within the table
	std::list<std::pair<K, V>> & currList = table[myhash(kv.first)];
	if (currList.size() > 0) {
		for (auto & listPos : currList) {
			if (kv.first == listPos.first && kv.second == listPos.second)	// if kv is already in the table return false
				return false;
			else if (kv.first == listPos.first) {	// if only the key is in the table, update the value
				listPos.second = kv.second;	// MAY NEED TO FIX, CHECK LATER
				break;
			}
		}
		currList.push_back(std::move(kv));					// if the pair nor the key is found, add the pair to the list/table
	}
	else
		currList.push_back(std::move(kv));					// if the list is empty, add the pair
	
	if (++tableSize > table.size())	// resize if needed
		rehash();
	return true;
}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K &k) {
	std::list<std::pair<K, V>> & currList = table[myhash(k)];
	auto itr = currList.begin();
	for (auto & listPos : currList) {
		if (k == listPos.first) {
			currList.erase(itr);	// erase the key and value at found position
			--tableSize;		// decrement current size of the table
			return true;
		}
		std::advance(itr,1);
	}
	return false;
}

template <typename K, typename V>
void HashTable<K, V>::clear() {
		makeEmpty();
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char * filename) {
	std::ifstream in;
	in.open(filename);
	if (!in.good()) {
		std::cout << "Could not find a file with the name specified." << std::endl;
		return false;
	}
	
	std::string currLine, key, val;
	while(std::getline(in,currLine)) {	// grabs one line until EOF
		std::stringstream s(currLine);	// with string stream I can properly ignore any type of white space (with getline and a delimiter, there is no way to do that as far as I can tell).
		s >> key >> val;
		auto p = std::make_pair (key, val);
		insert(p);
	}
	in.close();
	return true;
}

template <typename K, typename V>
void HashTable<K, V>::dump() const {
	int numLists, numPairs = 0;
	for (auto & currList : table) {
		std::cout << "v[" << numLists++ << "]: ";
		for (auto & listPos : currList) {
			if (numPairs++ > 0)
				std::cout << ":";
			std::cout << listPos.first << " " << listPos.second;
		}
		numPairs = 0;
		std::cout << std::endl;
	}
}

template <typename K, typename V>
size_t HashTable<K, V>::size() const {
	return tableSize;
}

template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char * filename) const {
	std::ofstream out;
	out.open(filename);
	
	for (auto & currList : table) {
		for (auto & listPos : currList)
			out << listPos.first << " " << listPos.second << std::endl;
	}
	out.close();
	return true;
}

//----------------------PRIVATE MEMBER FUNCTIONS--------------------------
template <typename K, typename V>
void HashTable<K, V>::makeEmpty() {
	for (auto & currList : table)
		currList.clear();
	tableSize = 0;
}

// ***I USED THE FUNCTION THAT WAS PROVIDED TO US VIA THE CH5_HASH2.PPTX POWER POINT SLIDES TO WRITE THIS FUNCTION
template <typename K, typename V>
void HashTable<K, V>::rehash() {
	auto oldLists = table;
	
	// create new double-sized, empty table
	table.resize(prime_below(2*table.size()));
	for (auto & currList : table)
		currList.clear();
	
	// copy table over
	tableSize = 0;
	for (auto & currList : oldLists)
		for (auto & x : currList)
			insert(std::move(x));
}

template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const {
	unsigned h = 101;
	for (auto & x : k)
		h = (h * 223) ^ (x * 107);
	return h % table.size();
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}
