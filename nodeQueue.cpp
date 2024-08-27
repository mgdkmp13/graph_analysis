#define _CRT_SECURE_NO_WARNINGS
#include "nodequeue.h"

nodequeue::nodequeue() {
	this->next = nullptr;
	this->prev = nullptr;
	this->data = 0;
}

nodequeue::nodequeue(long long data) {
	this->next = nullptr;
	this->prev = nullptr;
	this->data = data;
}


nodequeue::nodequeue(const nodequeue& other) {
	this->next = nullptr;
	this->prev = nullptr;
	this->data = other.data;
}

nodequeue::~nodequeue() {
	this->next = nullptr;
	this->prev = nullptr;
}
