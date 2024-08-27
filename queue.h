#pragma once
#include "nodequeue.h"
#include <iostream>
using namespace std;



class queue {
public:
	nodequeue* front;
	nodequeue* back;
	queue();
	~queue();
	void put(long long data);
	nodequeue getFront();
	void removeFront();
	bool isEmpty();
	void print();
};