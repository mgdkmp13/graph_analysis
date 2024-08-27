#include "Graph.h"
#include <fstream>
#include "queue.h"
using namespace std;


Graph::Graph() {
	this->graphOrder = 0;
	this->adjList = nullptr;
	this->listSizes = nullptr;
	this->degrees = nullptr;
	this->edges = 0;
}

Graph::Graph(long long graphOrder, long long** adjList, long long*listSizes, long long*degrees, long long edges) {
	this->graphOrder = graphOrder;
	this->adjList = adjList;
	this->listSizes = listSizes;
	this->degrees = degrees;
	this->edges = edges;
}

void Graph::showStats() {
	// 1
	degreeSequence();
	long long componentsNumber = 0;
	long long* oneIdFromComponent = this->components(componentsNumber);
	// 2
	cout << endl << componentsNumber << endl;
	// 3
	bipartiteness(oneIdFromComponent, componentsNumber);
	//4
	cout << "?\n";
	//5
	cout << "?\n";
	//6
	greedyColoring();
	//7
	LFColoring();
	//8
	cout << "?\n";
	// 9
	cout << "?\n";
	// 10
	complementsEdges();

	delete[] oneIdFromComponent;
}

void Graph::degreeSequence() {
	for (long long i = this->graphOrder - 1; i >= 0; i--) {
		for (long long j = 0; j < this->degrees[i]; j++) {
			cout << i << " ";
		}
	}
}


long long* Graph::components(long long& componentsNumber) {
	long long* oneIdFromComponent = new long long[this->graphOrder];;
	bool* visited = new bool[this->graphOrder];
	for (long long i = 0; i < this->graphOrder; i++) {
		visited[i] = false;
	}
	long long numVisited = 0;

	for (long long i = 0; i < this->graphOrder; i++) {
		if (numVisited >= this->graphOrder) {
			break;
		}
		if (!visited[i]) {
			DFS(visited, i, numVisited);
			oneIdFromComponent[componentsNumber] = i;
			componentsNumber++;
		}
	}
	delete[] visited;
	return oneIdFromComponent;

}

void Graph::complementsEdges() {
	long long maxEdges = (this->graphOrder * (this->graphOrder - 1)) / 2;
	cout << (maxEdges - this->edges) << endl;
}

void Graph::bipartiteness(long long* oneIdFromComponent, long long componentsNumber) {
	long long* sides = new long long[this->graphOrder];
	for (long long i = 0; i < this->graphOrder; i++) {
		sides[i] = 0;
	}
	for (long long i = 0; i < componentsNumber; i++) {
		long long startVer = oneIdFromComponent[i];
		if (!isBipartite(sides, startVer)) {
			cout << "F\n";
			delete[]sides;
			return;
		}
	}
	cout << "T\n";
	delete[]sides;
}

void Graph::DFS(bool*& visited, long long startVer, long long& numVisited) {
	if (startVer<0 || startVer > graphOrder - 1 || numVisited >= graphOrder || (visited[startVer])) {
		return;
	}

	visited[startVer] = true;
	numVisited++;

	for (long long i = 0; i < listSizes[startVer]; i++) {
		if (!visited[(adjList[startVer][i] - 1)]) {
			DFS(visited, adjList[startVer][i] - 1, numVisited);
		}
	}
}

bool Graph::isBipartite(long long*sides, long long startVer) {
	sides[startVer] = 1;
	queue q;
	q.put(startVer);

	while (!q.isEmpty()) {
		long long currentVer = q.getFront().data;
		q.removeFront();

		for (long long i = 0; i < this->listSizes[currentVer]; i++) {
			long long ver = this->adjList[currentVer][i] - 1;
			if (sides[ver] == 0) {
				long long color = 1;
				if (sides[currentVer] == 1) {
					color = 2;
				}
				sides[ver] = color;
				q.put(ver);
			}
			else if (sides[ver] == sides[currentVer]) {
				return false;
			}
		}
	}
	return true;
}

void Graph::greedyColoring() {
	long long* colors = new long long[this->graphOrder];
	bool* isTaken = new bool[this->graphOrder];
	for (long long i = 0; i < this->graphOrder; i++) {
		colors[i] = 0;
		isTaken[i] = false;
	}
	colors[0] = 1;
	for (long long i = 1; i < this->graphOrder; i++) {
		for (long long j = 0; j < this->listSizes[i]; j++) {
			long long help = this->adjList[i][j] - 1;
			long long u = colors[help];
			if (u != 0) {
				isTaken[u-1] = true;
			}
		}
		for (long long j = 0; j < this->graphOrder; j++) {
			if (isTaken[j]) {
				continue;
			}
			else {
				colors[i] = j + 1;
				break;
			}
		}
		for (long long j = 0; j < this->listSizes[i]; j++) {
			long long help = this->adjList[i][j] - 1;
			long long u = colors[help];
			if (u != 0) {
				isTaken[u-1] = false;
			}
		}
	}

	for (long long i = 0; i < this->graphOrder; i++) {
		cout << colors[i] << " ";
	}
	cout << endl;

	delete[] colors;
	delete[] isTaken;
}


void Graph::merge(long long* tab1, long long* indices, long long l, long long mid, long long r) {
	long long itL = 0;
	long long itR = 0;
	long long it = l;
	long long size_l = mid - l + 1;
	long long size_r = r - mid;
	long long size = size_l + size_r;
	long long* left = new long long[size_l];
	long long* right = new long long[size_r];
	long long* leftIdx = new long long[size_l];
	long long* rightIdx = new long long[size_r];

	for (long long i = 0; i < size_l; i++) {
		left[i] = tab1[l + i];
		leftIdx[i] = indices[l + i];
	}
	for (long long j = 0; j < size_r; j++) {
		right[j] = tab1[mid + j + 1];
		rightIdx[j] = indices[mid + j + 1];
	}

	while (itL < size_l && itR < size_r) {
		if (left[itL] > right[itR] || (left[itL] == right[itR] && leftIdx[itL] < rightIdx[itR])) {
			tab1[it] = left[itL];
			indices[it] = leftIdx[itL];
			itL++;
		}
		else if (left[itL] <= right[itR] || (left[itL] == right[itR] && leftIdx[itL] > rightIdx[itR])) {
			tab1[it] = right[itR];
			indices[it] = rightIdx[itR];
			itR++;
		}
		it++;
	}
	while (itL < size_l) {
		tab1[it] = left[itL];
		indices[it] = leftIdx[itL];
		it++;
		itL++;
	}
	while (itR < size_r) {
		tab1[it] = right[itR];
		indices[it] = rightIdx[itR];
		it++;
		itR++;
	}
	delete[] left;
	delete[] right;
	delete[] leftIdx;
	delete[] rightIdx;
}

void Graph::mergeSort(long long* tab, long long* indices, long long l, long long r) {
	if (l < r) {
		long long middle = (l + r) / 2;
		mergeSort(tab, indices, l, middle);
		mergeSort(tab, indices, middle + 1, r);
		merge(tab, indices, l, middle, r);
	}
}


void Graph::LFColoring() {
	long long* newListSizes = new long long[this->graphOrder];
	long long* indices = new long long[this->graphOrder];
	for (long long i = 0; i < this->graphOrder; i++) {
		newListSizes[i] = this->listSizes[i];
		indices[i] = i;
	}

	mergeSort(newListSizes, indices, 0, this->graphOrder - 1);

	long long* colors = new long long[this->graphOrder];
	bool* isTaken = new bool[this->graphOrder];
	for (long long i = 0; i < this->graphOrder; i++) {
		colors[i] = 0;
		isTaken[i] = false;
	}
	for (long long i = 0; i < this->graphOrder; i++) {
		long long idx = indices[i];
		for (long long j = 0; j < this->listSizes[idx]; j++) {
			long long help = this->adjList[idx][j] - 1;
			long long u = colors[help];
			if (u != 0) {
				isTaken[u - 1] = true;
			}
		}
		for (long long j = 0; j < this->graphOrder; j++) {
			if (!isTaken[j]) {
				colors[idx] = j + 1;
				break;
			}
		}
		for (long long j = 0; j < this->listSizes[idx]; j++) {
			long long help = this->adjList[idx][j] - 1;
			long long u = colors[help];
			if (u != 0) {
				isTaken[u - 1] = false;
			}
		}
	}

	for (long long i = 0; i < this->graphOrder; i++) {
		cout << colors[i] << " ";
	}
	cout << endl;

	delete[] colors;
	delete[] isTaken;
	delete[] newListSizes;
	delete[] indices;
}


Graph::~Graph() {
	for (long long j = 0; j < graphOrder; j++) {
		delete[] adjList[j];
	}
	delete[] adjList;
	delete[] listSizes;
	delete[] degrees;
}
