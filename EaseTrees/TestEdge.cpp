#include "Node.h"
#include "Edge.h"
#include "Vertex.h"
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
using namespace std;

template <class V, class E>
void printEdge(Edge<V, E>* edge) {
	cout << "Distance from " << edge->getFrom()->getValue() << " to " << edge->getTo()->getValue() << " is " << edge->getValue() << "kms." << endl;
	return;
}

template <class V, class E>
void printVertex(Vertex<V, E> vertex) {
	cout << vertex.getValue() << endl;
	vector<Edge<V, E>*> edges;
	edges = vertex.getOutwardEdges();
	cout << "Out:";
	for (int i = 0; i < edges.size(); i++) {
		cout << '\t' << *edges[i];
	}
	cout << endl;
	edges = vertex.getInwardEdges();
	cout << "In:";
	for (int i = 0; i < edges.size(); i++) {
		cout << '\t' << *edges[i];
	}
	cout << endl;
}

template <class V, class E>
void roadFrom(Vertex<V, E> &v1, Vertex<V, E> &v2) {
	cout << "There is ";
	if (!v1.isChild(&v2))	cout << "not ";
	cout << "a road from " << v1.getValue() << " to " << v2.getValue() << endl;
}
template <class V, class E>
void roadTo(Vertex<V, E> &v1, Vertex<V, E> &v2) {
	cout << "There is ";
	if (!v1.isParent(&v2))	cout << "not ";
	cout << "a road to " << v1.getValue() << " from " << v2.getValue() << endl;
}

void testEdge() {

	Vertex<string, int> pune("Pune");
	Vertex<string, int> delhi("Delhi");
	Vertex<string, int> mumbai("Mumbai");
	Vertex<string, int> chandigarh("Chandigarh");

	// Pune ---150---> Mumbai
	//	^	\
	//	|	 \
	//	|	  \			Road Map refference
	// 1700	   \
	//	|		\_____1440_____
	//	|					  v
	// Chandigarh <---260--- Delhi

	Edge<string, int> ptod(1440, &pune, &delhi);
	Edge<string, int> ctop(1700);
	ctop.setFrom(&chandigarh);
	ctop.setTo(&pune);
	Edge<string, int> dtoc;
	dtoc.setValue(260);
	dtoc.setFrom(&delhi);
	dtoc.setTo(&chandigarh);
	Edge<string, int> ptom(&pune, &mumbai);
	ptom.setValue(150);
	
	cout << "Planning for Mumbai. It is just " << ptom << "kms from here!" << endl;

	printEdge(&ptod);
	printEdge(&ptom);
	printEdge(&ctop);
	printEdge(&dtoc);

	// ***************** Test Vertex **********************

	Vertex<string, int> goa;
	goa.setValue("Goa");
	cout << "Let's plan for " << string(goa) << endl;	// only this bit doesn't work, everything else did
	cout << goa.getValue() << "!!!!" << endl;

	chandigarh.addChild(&pune)->setValue(1700);
	pune.addChild(&delhi, 1440);
	chandigarh.addParent(&delhi, 260);
	mumbai.addParent(&pune)->setValue(150);

	roadFrom(mumbai, chandigarh);
	roadTo(mumbai, pune);
	roadFrom(pune, delhi);
	roadTo(chandigarh, pune);
	
	goa.addParent(&pune);
	pune.removeChild(&goa);

	cout << "Goa has " << goa.getParents().size() << " parents" << endl;
	cout << "List of pune's related cities :" << endl;
	vector<Vertex<string, int>*> cities = pune.getChildren();
	for (int i = 0; i < cities.size(); i++) {
		cout << '\t' << cities[i]->getValue() << endl;
	}
	cities = pune.getParents();
	for (int i = 0; i < cities.size(); i++) {
		cout << '\t' << cities[i]->getValue() << endl;
	}
	printVertex(pune);
	printVertex(mumbai);
	printVertex(chandigarh);
	printVertex(delhi);


	return;
}