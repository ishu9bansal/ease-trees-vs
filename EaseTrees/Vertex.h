#ifndef vertex_h
#define vertex_h


#include "Edge.h"
#include <vector>
using namespace std;

template <class V, class E>
class Vertex{
private:
	V value;
	vector<Edge<V, E>*> outward;
	vector<Edge<V, E>*> inward;
public:
	Vertex() {}
	Vertex(V t) : value(t) {}
	V getValue() {
		return value;
	}
	void setValue(V t) {
		value = t;
		return;
	}
	vector<Edge<V, E>*>& getOutwardEdges() {
		return outward;
	}
	void setOutwardEdges(vector<Edge<V, E>*> edges) {
		outward = edges;
		return;
	}
	void addOutwardEdge(Edge<V, E>* edge) {
		outward.push_back(edge);
		return;
	}
	vector<Edge<V, E>*>& getInwardEdges() {
		return inward;
	}
	void setInwardEdges(vector<Edge<V, E>*> edges) {
		inward = edges;
		return;
	}
	void addInwardEdge(Edge<V, E>* edge) {
		inward.push_back(edge);
		return;
	}
	vector<Edge<V, E>*> getEdges() {
		vector<Edge<V, E>*> edges = outward;
		edges.insert(edges.end(), inward.begin(), inward.end());
		return edges;
	}
	operator V() {
		return value;
	}
};

void testEdge();

#endif	// !vertex_h
