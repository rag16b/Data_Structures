#include <iostream>
#include <string>
#include "hashtable.h"

using namespace std;
using namespace cop4530;

int main() {
	HashTable<string, string> table;
	
	pair <string, string> a, r, z, h;
	r.first = "ryan";
	r.second = "test";
	h.first = "heather";
	h.second = "hart";
	
	table.insert(r);
	table.insert(h);
	
	cout << endl;
	table.dump();	
	cout << endl << table.size() << endl;
	
	table.load("Test");
	table.dump();
	cout << endl << table.size() << endl;
	
	return 0;
}
