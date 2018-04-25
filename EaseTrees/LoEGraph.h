#ifndef loe_graph_h
#define loe_graph_h

#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include "graph.h"
#include "Edge.h"
#include "Vertex.h"

template <class T, class U>
class LoEGraph : public graph<T, U> {
	unordered_set<Edge<T, U>*> edges;
	vector<Vertex<T, U>*> vertex;
public:
	using graph<T, U>::addVertex;
	using graph<T, U>::removeVertex;
	using graph<T, U>::checkEdge;
	using graph<T, U>::zero;
	using graph<T, U>::one;

	LoEGraph(U z, U o) : graph<T, U>(z, o) {}
	~LoEGraph() {
		for (int i = 0; i < vertex.size(); i++) {
			delete vertex[i];
		}
	}
	Edge<T, U>* getEdge(Index x, Index y, bool direct) {
		if (!direct)	swap(x, y);
		return vertex[x]->to[vertex[y]];
	}
	void setWeight(Index x, Index y, bool direct, Weight<U> w) {
		getEdge(x, y, direct)->setValue(U(w));
		return;
	}
	U getWeight(Index x, Index y, bool direct) {
		return getEdge(x, y, direct)->getValue();
	}
	bool checkEdge(Index x, Index y, bool direct) {
		if (!direct)	swap(x, y);
		return vertex[x]->isChild(vertex[y]) || vertex[y]->isParent(vertex[x]);
	}
	bool addVertex(const T& t) {
		if (graph<T, U>::addVertex(t)) {
			vertex.push_back(new Vertex<T,U>(t));
			return true;
		}
		return false;
	}
	void vAddEdge(Index x, Index y, bool direct) {
		if (!direct)	swap(x, y);
		Edge<T, U>* edge = vertex[x]->addChild(vertex[y]);
		// this if will always be true.
		if(vertex[y]->addInwardEdge(edge))	edges.insert(edge);
		return;
	}
	void vRemoveEdge(Index x, Index y, bool direct) {
		if (!direct)	swap(x, y);
		Edge<T, U>* edge = getEdge(x, y, direct);
		edges.erase(edge);
		vertex[x]->removeChild(vertex[y]);
		vertex[y]->removeParent(vertex[x]);
		delete edge;
		return;
	}
	void removeVertex(Index nodeIndex) {
		graph<T>::removeVertex(nodeIndex);
		delete vertex[nodeIndex];
		vertex[nodeIndex] = vertex.back();
		vertex.pop_back();
		return;
	}
	vector<Edge<V, E>*> getEdges() {
		vector<Edge<V, E>*> v;
		for (const auto& edge : edges) {
			v.push_back(edge);
		}
		return v;
	}
	void print() {
		graph<T>::print();
		cout << endl;
		cout << "Adjacency List:" << endl;
		for (int i = 0; i < vertex.size(); i++) {
			vector<Edge<T, U>*> &refEdges = vertex[i]->getOutwardEdges();
			cout << vertex[i]->getValue() << "\t:\t";
			for (int j = 0; j < refEdges.size(); j++)
				cout << refEdges[j]->getValue() << " -- " << refEdges[j]->getTo()->getValue() << " | ";
			cout << endl;
		}
		return;
	}

};

void testMatrixGraph();

#endif // !loe_graph_h
