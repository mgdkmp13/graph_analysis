#pragma once
#include <iostream>
using namespace std;

class nodequeue {
public:
	long long data;
	nodequeue* next;
	nodequeue* prev;

	nodequeue();
	nodequeue(long long data);
	nodequeue(const nodequeue& other);
	~nodequeue();
};
