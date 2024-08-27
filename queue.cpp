#define _CRT_SECURE_NO_WARNINGS
#include "queue.h"
#define PRIOR_N 4


queue::queue() {
	this->front = nullptr;
	this->back = nullptr;
}

void queue::put(long long data) {
	nodequeue* newNode = new nodequeue(data);
	if (this->front == nullptr) {
		this->front = newNode;
		this->back = newNode;
	}
	else if (this->front == this->back) {
		newNode->next = this->front;
		this->back = newNode;
		this->front->prev = this->back;
	}
	else {
		newNode->next = this->back;
		this->back->prev = newNode;
		this->back = newNode;
	}
}

void queue::removeFront() {
	if (this->front != nullptr) {
		nodequeue* tmp = this->front;

		if (this->front->prev != nullptr) {
			this->front->prev->next = nullptr;
			this->front = this->front->prev;
			tmp->prev = nullptr;
			delete tmp;
		}
		else {
			this->front->next = nullptr;
			this->front = nullptr;
			delete tmp;
		}
	}
	else {
		cout << "Empty queue\n";
	}
}

nodequeue queue::getFront() {
	if (this->front != nullptr) {
		nodequeue tmp = nodequeue(*this->front);
		return tmp;
	}
	else {
		cout << "Empty queue\n";
		return NULL;
	}
}

void queue::print() {
	nodequeue* tmp = this->front;
	while (tmp != nullptr) {
		cout << tmp->data << " ";
		tmp = tmp->prev;
	}
	cout << '\n';
}

bool queue::isEmpty() {
	if (this->front == nullptr) {
		return true;
	}
	return false;
}

queue::~queue() {
	while (this->front != nullptr) {
		nodequeue* temp = this->front;
		this->front = this->front->prev;
		delete temp;
	}
}