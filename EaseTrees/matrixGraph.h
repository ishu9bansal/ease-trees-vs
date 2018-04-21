#ifndef matrix_graph_h
#define matrix_graph_h

#include <iostream>
#include <vector>
#include <string>
#include "graph.h"
#include "SquareVector.h"

template <class T, class U = bool>
class matrixGraph : public graph<T, U> {
	vectorSquare<U> edgeMap;
public:
	using graph<T, U>::addVertex;
	using graph<T, U>::addEdge;
	using graph<T, U>::removeEdge;
	using graph<T, U>::removeVertex;
	using graph<T, U>::checkEdge;

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
	void vAddEdge(Index x, Index y, bool direct) {
		addEdge(x, y, direct);
	}
	void addEdge(Index x, Index y, bool direct, Weight<U> w = graph<T, U>::one) {
		if (!direct)	swap(x, y);
		edgeMap(x, y) = w;
		return;
	}
	void removeEdge(Index x, Index y, bool direct) {
		if (!direct)	swap(x, y);
		edgeMap(x, y) = graph<T,U>::zero;
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
