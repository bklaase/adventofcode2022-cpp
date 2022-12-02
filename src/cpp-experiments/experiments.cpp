#include <iostream>

//// experiments; uncomment to work with
#include <lists.hpp>

using namespace std;

int main() {
	cout << "hello experiments!" << endl;
	makeListList();
	cout << "this is in the list! -> " << mylist.front().front() << endl;

	int sumresult = std::accumulate(l2.cbegin(), l2.cend(), 0);
	cout << "sumresult: " << sumresult << endl;

	cout << "all done" << endl;
}
