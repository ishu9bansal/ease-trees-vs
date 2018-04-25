#ifndef vertex_h
#define vertex_h


#include "Edge.h"
#include <vector>
#include <unordered_map>
using namespace std;

template <class V, class E>
class Vertex{
	// this will be a raw class,
	// intermediate states may exist while using it,
	// implementor have to take care of that
	// (intermediate but not inconsistant, see return type bool)
private:
	V value;
	unordered_map<Vertex<V, E>*, Edge<V, E>*> to;
	unordered_map<Vertex<V, E>*, Edge<V, E>*> from;
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
	vector<Edge<V, E>*> getOutwardEdges() {
		vector<Edge<V, E>*> v;
		for (const auto& pair : to) {
			v.push_back(pair.second);
		}
		return v;
	}
	vector<Vertex<V, E>*> getChildren() {
		vector<Vertex<V, E>*> v;
		for (const auto& pair : to) {
			v.push_back(pair.first);
		}
		return v;
	}
	bool isChild(Vertex<V, E>* nodeRef) {
		return to.find(nodeRef) != to.end();
	}
	Edge<V, E>* addChild(Vertex<V, E>* nodeRef) {
		return to[nodeRef] = new Edge<V, E>(this, nodeRef);
	}
	Edge<V, E>* addChild(Vertex<V, E>* nodeRef, E weight) {
		return to[nodeRef] = new Edge<V, E>(weight,this, nodeRef);
	}
	void removeChild(Vertex<V, E>* nodeRef) {
		return to.erase(nodeRef);
	}
	bool addOutwardEdge(Edge<V, E>* edge) {	// returns false if edge is not defined from this vertex
		if (this != edge->getFrom())	return false;
		to[edge->getTo()] = edge;
		return true;
	}
	vector<Edge<V, E>*> getInwardEdges() {
		vector<Edge<V, E>*> v;
		for (const auto& pair : from) {
			v.push_back(pair.second);
		}
		return v;
	}
	vector<Vertex<V, E>*> getParents() {
		vector<Vertex<V, E>*> v;
		for (const auto& pair : from) {
			v.push_back(pair.first);
		}
		return v;
	}
	bool isParent(Vertex<V, E>* nodeRef) {
		return from.find(nodeRef) != from.end();
	}
	Edge<V, E>* addParent(Vertex<V, E>* nodeRef) {
		return from[nodeRef] = new Edge<V, E>(nodeRef, this);
	}
	Edge<V, E>* addParent(Vertex<V, E>* nodeRef, E weight) {
		return from[nodeRef] = new Edge<V, E>(weight, nodeRef, this);
	}
	void removeParent(Vertex<V, E>* nodeRef) {
		return from.erase(nodeRef);
	}
	bool addInwardEdge(Edge<V, E>* edge) {	// returns false if edge is not defined to this vertex
		if (this != edge->getTo())	return false;
		from[edge->getFrom()] = edge;
		return true;
	}
	vector<Edge<V, E>*> getEdges() {
		vector<Edge<V, E>*> outEdges = getOutwardEdges();
		vector<Edge<V, E>*> inEdges = getInwardEdges();
		outEdges.insert(outEdges.end(), inEdges.begin(), inEdges.end());
		return outEdges;
	}
	operator V() {
		return value;
	}
};

void testEdge();

#endif	// !vertex_h
