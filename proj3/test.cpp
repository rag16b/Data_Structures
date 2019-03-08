#include <iostream>
#include <cstdlib>
#include "stack.h"

using namespace std;
using namespace cop4530;

int main() {
	
	Stack<int> intstk;
	
	cout << "inserting 10 elements" << endl;
	for (unsigned int i = 0; i < 10; i++)
		intstk.push(i);
	
	cout << "\nThe Size of the above stack is: " << intstck.size() << endl << endl;

	return 0;
}
