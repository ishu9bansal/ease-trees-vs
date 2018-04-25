#ifndef vertex_h
#define vertex_h


#include "Edge.h"
#include <vector>
#include <unordered_map>
using namespace std;

template <class V, class E>
class Vertex{
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
		if (isChild(nodeRef))	return to[nodeRef];
		Edge<V, E>* edge = new Edge<V, E>(this, nodeRef);
		this->to[nodeRef] = edge;
		nodeRef->from[this] = edge;
		return edge;
	}
	Edge<V, E>* addChild(Vertex<V, E>* nodeRef, E weight) {
		Edge<V, E>* edge = addChild(nodeRef);
		edge->setValue(weight);
		return edge;
	}
	void removeChild(Vertex<V, E>* nodeRef) {
		if (isChild(nodeRef)) {
			delete to[nodeRef];
			nodeRef->from.erase(this);
			to.erase(nodeRef);
		}
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
		return nodeRef->addChild(this);
	}
	Edge<V, E>* addParent(Vertex<V, E>* nodeRef, E weight) {
		return nodeRef->addChild(this, weight);
	}
	void removeParent(Vertex<V, E>* nodeRef) {
		nodeRef->removeChild(this);
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
