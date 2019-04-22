#include <iostream>
#include <string>
#include "passserver.h"

using namespace std;
using namespace cop4530;

int main() {
	PassServer ps(101);
	
	auto user1 = make_pair("Ryan","pass");
	auto user2 = make_pair("Zachary","isgay");
	ps.addUser(user1);
	ps.addUser(user2);
	
	ps.load("Test");
	
	ps.dump();

	ps.removeUser("Ryan");
	cout << endl;
	ps.dump();
	cout << endl << ps.size() << endl << endl;
	
	if (ps.find("Zachary"))
		cout << "Found Zachary" << endl;
	else
		cout << "Could not find Zachary" << endl;

	if (ps.find("Hank"))
		cout << "Found Hank" << endl;
	else
		cout << "Could not find Hank" << endl;
	
	ps.write_to_file("outtest");
	
	return 0;
}
