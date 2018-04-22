#ifndef edge_h
#define edge_h


using namespace std;
template <class V, class E>
class Vertex;

template <class V, class E>
class Edge{
private:
	E value;
	Vertex<V, E>* from;
	Vertex<V, E>* to;
public:
	Edge(){}
	Edge(E t) : value(t) {}
	Edge(Vertex<V, E>* fromNode, Vertex<V, E>* toNode) : from(fromNode), to(toNode) {}
	Edge(E t, Vertex<V, E>* fromNode, Vertex<V, E>* toNode) : value(t), from(fromNode), to(toNode) {}
	Vertex<V, E>* getFrom() {
		return from;
	}
	void setFrom(Vertex<V, E>* node) {
		from = node;
		return;
	}
	Vertex<V, E>* getTo() {
		return to;
	}
	void setTo(Vertex<V, E>* node) {
		to = node;
		return;
	}
	E getValue() {
		return value;
	}
	void setValue(E t) {
		value = t;
		return;
	}
	operator E() {
		return value;
	}
};

void testEdge();

#endif	// !edge_h
