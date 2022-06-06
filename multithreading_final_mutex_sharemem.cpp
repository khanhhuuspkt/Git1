#include <iostream>
#include <thread>
#include <list>
#include <algorithm>
#include <mutex>
using namespace std;

// a global variable
list<int> myList;
mutex mu;
void addToList(int max, int interval, string thr)
{
    mu.lock();
	for (int i = 0; i < max; i++) {
		if( (i % interval) == 0) myList.push_back(i);
	}
    mu.unlock();
    
    for (int j = 0; j < max ; j++) {
        cout << endl << thr << endl;
    }
}

void printList()
{
    mu.lock();
	for (auto itr = myList.begin(), end_itr = myList.end(); itr != end_itr; ++itr ) {
		cout << *itr << ",";
	}
    mu.unlock();
}

int main()
{
	int max = 200;

	std::thread t1(addToList, max, 1,"thread 1");
	std::thread t2(addToList, max, 10, "thread 2");
	std::thread t3(printList);

	t1.join();
	t2.join();
	t3.join();

	return 0;
}