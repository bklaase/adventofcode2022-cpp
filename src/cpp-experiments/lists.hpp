#include <list>
#include <numeric>

// list<int> mylist = {};
using namespace std;

list<list<int>> mylist = {};
list<int> l1 = {1,2,3};
list<int> l2 = {4,5,6};

void makeListList() {
  mylist.push_back(l1);
  mylist.push_back(l2);
}

// list<int> sumInnerlists (list<list<int>> listlist) {
// 	int sum = [](list<int> list) {std::accumulate(list.cbegin(), list.cend(), 0)};
// 	auto 
// 	//std::transform(listlist.begin(), listlist.end(), 
// 	return {};
// }
