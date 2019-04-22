#include <iostream>
#include "passserver.h"

using namespace std;
using namespace cop4530;

void Menu();

int main() {
	
	char choice;
	size_t size;
	string username;
	string password;
	string filename;
	string newPW;
	
	// getting server size
	cout << "Enter preferred hash table capacity: ";
	cin >> size;
	// creating password server hash table
	PassServer ps(size);
	cout << ps.capacity() << endl;
	
	// main loop
	do {
		Menu();
		cin >> choice;
		
		switch (choice) {
			case 'l':	// load from file
				cout << "Enter password file name to load from: ";
				cin >> filename;
				if (!ps.load(filename.c_str()))
					cout << "\nError: Cannot open file " << filename << endl;
				break;
			case 'a':	// add user
				cout << "Enter username: ";
				cin >> username;
				cout << "Enter password: ";
				cin >> password;
				if (ps.find(username))
					cout << "\n*****Error: User already exists. Could not add user.\n";
				else {
					auto p = make_pair(username,password);
					ps.addUser(p);
					cout << "User " << username << " added.\n";
				}
				break;
			case 'r':	// remove user
				cout << "Enter username: ";
				cin >> username;
				if (ps.find(username)) {
					ps.removeUser(username);
					cout << "\nUser " << username << " deleted.";
				}
				else
					cout << "\n*****Error: User not found. Could not delete user";
				break;
			case 'c':	// change password
				cout << "Enter username: ";
				cin >> username;
				cout << "Enter password: ";
				cin >> password;
				cout << "\nEnter new password: ";
				cin >> newPW;
				if (ps.changePassword(make_pair(username,password),newPW))
					cout << "\nPassword changed for user " << username << endl;
				else
					cout << "\n*****Error: Could not change user password" << endl;
				break;
			case 'f':	// find user
				cout << "Enter username: ";
				cin >> username;
				if (ps.find(username))
					cout << "\nUser '" << username << "' found.\n";
				else
					cout << "\nUser '" << username << "' not found.\n";
				break;
			case 'd':	// dump hash table
				ps.dump();
				break;
			case 's':	// return size of hash table
				cout << "Size of hashtable: " << ps.size() << endl;
				break;
			case 'w':	// write to password file
				cout << "Enter password file name to write to: ";
				cin >> filename;
				ps.write_to_file(filename.c_str());
				break;
			default:	// default case; also handles x (quit)
				break;
		}
	} while (choice != 'x');
	
        return 0;
}

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice: ";
}
