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

//----------------------public member functions---------------------------
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size = 101) {
	list.resize(prime_below(size));
	tableSize = 0;			// NOT SURE WHAT THIS IS USEFUL FOR
}

template <typename K, typename V>
HashTable<K, V>::~HashTable() {
	clear();
}

template <typename K, typename V>
bool HashTable<K, V>::contains(const K &k) const {
	// get the given list at k as the possible list containing k
	auto & tempList = list[myhash(k)];
	for (int i = 0; i < tempList.size(); i++)
		if (tempList.first == k)		// FIRST?????????
			return true;
	return false;
}

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> & kv) const {

}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> & kv) {

}

template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V> && kv) {

}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K &k) {

}

template <typename K, typename V>
void HashTable<K, V>::clear() {
	makeEmpty();
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char * filename) {

}

template <typename K, typename V>
void HashTable<K, V>::dump() const {

}

template <typename K, typename V>
size_t HashTable<K, V>::size() const {

}

template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char * filename) const {

}

//----------------------private member functions--------------------------
template <typename K, typename V>
void HashTable<K, V>::makeEmpty() {
	
}

template <typename K, typename V>
void HashTable<K, V>::rehash() {

}

template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const {

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
