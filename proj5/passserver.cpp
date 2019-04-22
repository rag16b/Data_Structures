//-------PASSSERVER.CPP--------
//
// Ryan Gutierrez
// COP4530 - 0001
// Project 5
// Goals: Understand and get familiar with the data structure hash tables,
//        and its applications in managing user accounts.
// Use: This is the definition of the member functions of the PassServer
//      class.

#include <crypt.h>
#include <unistd.h>
#include <cstring>
#include "passserver.h"
using namespace cop4530;

//----------------------PUBLIC MEMBER FUNCTIONS---------------------------
PassServer::PassServer(size_t size = 101) : HashTable<std::string, std::string>(size){}

PassServer::~PassServer() { /*don't think I need to do anything here*/ }

bool PassServer::load(const char *filename) {
	std::ifstream in;
	in.open(filename);
	if (!in.good()) {
		std::cout << "Could not find a file with the name specified." << std::endl;
		return false;
	}

	std::string currLine, key, val;
	while(std::getline(in,currLine)) {      // grabs one line until EOF
		std::stringstream s(currLine);  // with string stream I can properly ignore any type of white space (with getline and a delimiter, there is no way to do that as far as I can tell).
		s >> key >> val;
		auto p = std::make_pair (key, val);
		addUser(p);			// only difference between hashtable load function is I use addUser instead of Insert to insure that it's encrypted
	}
	in.close();
	return true;
}

bool PassServer::addUser(std::pair<std::string, std::string> & kv) {
	auto p = std::make_pair(kv.first,encrypt(kv.second));
	return HashTable<std::string, std::string>::insert(p);
}

bool PassServer::addUser(std::pair<std::string, std::string> && kv) {
	auto p = std::make_pair(kv.first,encrypt(kv.second));
	return HashTable<std::string, std::string>::insert(std::move(p));
}

bool PassServer::removeUser(const std::string & k) {
	return HashTable<std::string, std::string>::remove(k);
}

bool PassServer::changePassword(const std::pair<std::string, std::string> &p, const std::string & newpassword) {	// NEED TO TEST
	if (find(p.first)) {
		auto oldPass = std::make_pair(p.first,encrypt(p.second));
		auto newPass = std::make_pair(p.first,encrypt(newpassword));
		
		if (HashTable<std::string, std::string>::match(oldPass) && !HashTable<std::string, std::string>::match(newPass)) {
			HashTable<std::string, std::string>::remove(p.first);
			return HashTable<std::string, std::string>::insert(newPass);
		}
	}
	return false;
}

bool PassServer::find(const std::string & user) const {
	return HashTable<std::string, std::string>::contains(user);
}

void PassServer::dump() {
	return HashTable<std::string, std::string>::dump();
}

size_t PassServer::size() const {
	return HashTable<std::string, std::string>::size();
}

bool PassServer::write_to_file(const char *filename) const {
	return HashTable<std::string, std::string>::write_to_file(filename);
}

size_t PassServer::capacity() {
	return HashTable<std::string, std::string>::capacity();
}

//----------------------PRIVATE MEMBER FUNCTIONS--------------------------
std::string PassServer::encrypt(const std::string & str) {
	char salt[] = "$1$########";
	
	char * password = new char [100];
	strcpy(password,crypt(str.c_str(), salt));
	std::string pass(password);
	return pass.substr(12);
}
