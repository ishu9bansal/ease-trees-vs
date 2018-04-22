#ifndef vertex_h
#define vertex_h


#include "Edge.h"
#include <vector>
using namespace std;
class EdgeBase;

class VertexBase {
protected:
	vector<EdgeBase*> outward;
	vector<EdgeBase*> inward;
public:
	VertexBase() {}
	vector<EdgeBase*>& getOutwardEdges() {
		return outward;
	}
	void setOutwardEdges(vector<EdgeBase*> edges) {
		outward = edges;
		return;
	}
	void addOutwardEdge(EdgeBase* edge) {
		outward.push_back(edge);
		return;
	}
	vector<EdgeBase*>& getInwardEdges() {
		return inward;
	}
	void setInwardEdges(vector<EdgeBase*> edges) {
		inward = edges;
		return;
	}
	void addInwardEdge(EdgeBase* edge) {
		inward.push_back(edge);
		return;
	}
	vector<EdgeBase*> getEdges() {
		vector<EdgeBase*> edges = outward;
		edges.insert(edges.end(), inward.begin(), inward.end());
		return edges;
	}
};

template <class T>
class Vertex : public VertexBase {
private:
	T value;
public:
	Vertex() {}
	Vertex(T t) : value(t) {}
	T getValue() {
		return value;
	}
	void setValue(T t) {
		value = t;
		return;
	}
	operator T() {
		return value;
	}
};

void testEdge();

#endif	// !vertex_h
