#ifndef edge_h
#define edge_h


#include "Vertex.h"
using namespace std;
class VertexBase;

class EdgeBase {
protected:
	VertexBase* from;
	VertexBase* to;
public:
	virtual ~EdgeBase() {};
	EdgeBase(){}
	EdgeBase(VertexBase* fromNode, VertexBase* toNode) : from(fromNode), to(toNode) {}
	VertexBase* getFrom() {
		return from;
	}
	void setFrom(VertexBase* node) {
		from = node;
		return;
	}
	VertexBase* getTo() {
		return to;
	}
	void setTo(VertexBase* node) {
		to = node;
		return;
	}
};

template <class T>
class Edge : public EdgeBase{
private:
	T value;
public:
	Edge(){}
	Edge(T t) : value(t) {}
	Edge(VertexBase* fromNode, VertexBase* toNode) : EdgeBase(fromNode, toNode) {}
	Edge(T t, VertexBase* fromNode, VertexBase* toNode) : value(t), EdgeBase(fromNode,toNode) {}
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

#endif	// !edge_h
