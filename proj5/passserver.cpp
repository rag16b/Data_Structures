//-------PASSSERVER.H--------
//
// Ryan Gutierrez
// COP4530 - 0001
// Project 5
// Goals: Understand and get familiar with the data structure hash tables,
//        and its applications in managing user accounts.
// Use: This is the definition of the member functions of the PassServer
//      class.

#include "passserver.h"
using namespace cop4530;

//----------------------PUBLIC MEMBER FUNCTIONS---------------------------
PassServer::PassServer(size_t size = 101) : HashTable<std::string, std::string>(size){}

PassServer::~PassServer() {

}

bool PassServer::load(const char *filename) {

}

bool PassServer::addUser(std::pair<string,  string> & kv) {

}

bool PassServer::addUser(std::pair<string, string> && kv) {

}

bool PassServer::removeUser(const string & k) {

}
bool PassServer::changePassword(const pair<string, string> &p, const string & newpassword) {

}

bool PassServer::find(const string & user) const {

}

void PassServer::dump() {

}

size_t PassServer::size() const {

}

bool PassServer::write_to_file(const char *filename) const {

}

//----------------------PRIVATE MEMBER FUNCTIONS--------------------------
std::string PassServer::encrypt(const std::string & str) {

}
