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

void testEdge() {

	Vertex<string, int> pune("Pune");
	Vertex<string, int> delhi("Delhi");
	Vertex<string, int> mumbai("Mumbai");
	Vertex<string, int> chandigarh("Chandigarh");

	Vertex<string, int> goa;
	goa.setValue("Goa");
	cout << "Let's plan for " << string(goa) << endl;	// only this bit doesn't work, everything else did
	cout << goa.getValue() << "!!!!" << endl;


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
	
	cout << "Plan never succeeds. Not from atleast last " << ptom << " times." << endl;

	vector<Edge<string, int>*> puneEdges = { &ptod,&ptom };
	//pune.setOutwardEdges(puneEdges);
	vector<Edge<string, int>*> refEdges = pune.getInwardEdges();
	refEdges.push_back(&ctop);

	puneEdges = pune.getEdges();

	for (int i = 0; i < puneEdges.size(); i++) {
		printEdge(puneEdges[i]);
	}

	printEdge(&ptod);
	printEdge(&ptom);
	printEdge(&ctop);
	printEdge(&dtoc);

	/*s
	chandigarh.addOutwardEdge(&ctop);
	chandigarh.addInwardEdge(&dtoc);
	delhi.addOutwardEdge(&dtoc);
	delhi.addInwardEdge(&ptod);
	mumbai.addInwardEdge(&ptom);
	*/
	printVertex(pune);

	return;
}