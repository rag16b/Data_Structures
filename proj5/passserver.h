//-------PASSSERVER.H--------
//
// Ryan Gutierrez
// COP4530 - 0001
// Project 5
// Goals: Understand and get familiar with the data structure hash tables,
//        and its applications in managing user accounts.
// Use: This is the declaration of the member functions of the PassServer
//      class.

#ifndef PASSSERVER_H
#define PASSSERVER_H

#include "hashtable.h"

namespace cop4530 {
	class PassServer : public HashTable <std::string, std::string> {
		public:
			PassServer(size_t size);  // constructor, create a hash table of the specified size. prime_below() will be called.
			~PassServer();  //  destructor. We do not want to have memory leak.
			bool load(const char *filename);        // load a password file into the HashTable object. Each line contains a pair of username and encrypted password.
			bool addUser(std::pair<std::string, std::string> & kv);  // add a new username and password. Password should be encrypted before insertion. The pair should not be added if the username already exists in the hash table.
			bool addUser(std::pair<std::string, std::string> && kv);  // move version of addUser.
			bool removeUser(const std::string & k);      // delete an existing user with username k.
			bool changePassword(const std::pair<std::string, std::string> &p, const std::string & newpassword); // change an existing user's password.
			bool find(const std::string & user) const;   // check if a user exists (if user is in the hash table).
			void dump();    // show the structure and contents of the HashTable object to the screen. Same format as the dump() function in the HashTable class template.
			size_t size() const;    // return the size of the HashTable (the number of username/password pairs in the table).
			bool write_to_file(const char *filename) const; // save user and pass combo into a file. same format as write_to_file() in hashtable class
			
			// my public member functions
			size_t capacity();	// returns the capacity of the underlying hash table
		private:
			std::string encrypt(const std::string & str);
	};
}
#endif
