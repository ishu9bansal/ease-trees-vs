#ifndef matrix_graph_h
#define matrix_graph_h

#include <iostream>
#include <vector>
#include <string>
#include "graph.h"
#include "SquareVector.h"

template <class T>
class matrixGraph : public graph<T> {
	vectorSquare<int> edgeMap;
public:
	using graph<T>::addVertex;
	using graph<T>::removeVertex;
	bool checkEdge(Index x, Index y, bool direct) {
		if (!direct)	swap(x, y);
		return edgeMap(x, y);
	}
	bool addVertex(const T& node) {
		if (graph<T>::addVertex(node)) {
			edgeMap.addOne();
			return true;
		}
		return false;
	}
	void addEdge(Index x, Index y, bool direct) {
		if (!direct)	swap(x, y);
		edgeMap(x, y) = 1;
		return;
	}
	void removeEdge(Index x, Index y, bool direct) {
		if (!direct)	swap(x, y);
		edgeMap(x, y) = 0;
		return;
	}
	void removeVertex(Index nodeIndex) {
		graph<T>::removeVertex(nodeIndex);
		edgeMap.remove(nodeIndex);
		return;
	}
	void print() {
		graph<T>::print();
		cout << "Edge mapping:" << endl;
		cout << edgeMap << endl;
		return;
	}

};

void testMatrixGraph();

#endif // !matrix_graph_h
