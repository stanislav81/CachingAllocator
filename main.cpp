/*
 * main.cpp
 *
 *  Created on: 11.11.2011
 *      Author: stan
 */

#include <iostream>
#include <stdio.h>
#include <sys/time.h>
#include "CacheAllocator.h"
#include "TimeUtils.h"
#include <list>
using namespace std;

struct A {
	int a;
	int b;
	char *c;
};

class B : A {
	int d;
	char buffer[128];
public:
	B(): A ()
	{}
	void setD(int& x) {
		d = x;
	}
	int& getD() {return d;}
};

void testGetFree() {

	int NUMBER = 100000;

	cout << "allocated B objects: " << NUMBER  << ", " << "size of B: " << sizeof(B) << " (bytes)" << endl;

	// ----------------------------------------------
	list<B*> box2;

	cache_allocator::CacheAllocator ca;
	ca.prepareFreeList<B>(NUMBER);

	double start2 = utils::time::GetMilliseconds();

	for (int i = 0; i < NUMBER; i++) {
		B *b = ca.getBlock<B>();
		box2.push_back(b);
	}

	for(list<B*>::iterator it = box2.begin(); it != box2.end(); ++it) {
		ca.freeBlock(*it);
	}

	double delta2 = utils::time::GetMilliseconds() - start2;

	cout << "Time with caching: " << delta2 <<  " (ms)" << endl;

	// ----------------------------------------------

	list<B*> box;
	double start1 = utils::time::GetMilliseconds();

	for (int i = 0; i < NUMBER; i++) {
		box.push_back(new B);
	}

	for(list<B*>::iterator it = box.begin(); it != box.end(); ++it) {
		delete *it;
	}

	double delta1 = utils::time::GetMilliseconds() - start1;

	cout << "Time without caching: " << delta1 << " (ms)" << endl;

	// -------------------------------------------------------
	cout << "Profit: " << ((delta1 - delta2)/delta2) * 100 << " %" << endl;
}

int main(int argc, char **argv) {

	testGetFree();

	return 0;
}


