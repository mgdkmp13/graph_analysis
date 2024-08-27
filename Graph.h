#include <iostream>
using namespace std;

class Graph {
public:
	long long graphOrder;
	long long** adjList;
	long long* listSizes;
	long long* degrees;
	long long edges;

	Graph();
	Graph(long long graphOrder, long long** adjList, long long*listSizes, long long*degrees, long long edges);

	void showStats();

	void degreeSequence();
	long long* components(long long & componentsNumber);
	void bipartiteness(long long* oneIdFromComponent, long long componentsNumber);
	void complementsEdges();
	void DFS(bool*& visited, long long startVer, long long& numVisited);
	bool isBipartite(long long* sides, long long startVer);
	void greedyColoring();
	void LFColoring();


	void mergeSort(long long* tab, long long* indices, long long l, long long r);
	void merge(long long* tab1, long long* indices, long long l, long long mid, long long r);


	~Graph();
};