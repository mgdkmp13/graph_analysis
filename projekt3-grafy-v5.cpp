#include <iostream>
#include "Graph.h"
using namespace std;

void readInput(long long k) {
	for (long long i = 0; i < k; i++) {
		long long graphOrder, size, edges = 0, vert;
		cin >> graphOrder;
		long long** adjList = new long long* [graphOrder];
		long long* listSizes = new long long[graphOrder];
		long long* degrees = new long long[graphOrder];
		for (long long j = 0; j < graphOrder; j++) {
			degrees[j] = 0;
		}

		for (long long j = 0; j < graphOrder; j++) {
			cin >> size;
			adjList[j] = new long long[size];
			listSizes[j] = size;
			degrees[size]++;
			for (long long k = 0; k < size; k++) {
				cin >> vert;
				adjList[j][k] = vert;
				edges++;
			}
		}
		edges /= 2;
		Graph graph(graphOrder, adjList, listSizes, degrees, edges);
		graph.showStats();
	}
}

int main() {
	long long k;
	cin >> k;
	readInput(k);
}


