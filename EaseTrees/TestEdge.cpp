#include "Node.h"
#include "Edge.h"
#include "Vertex.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void printEdge(EdgeBase* edge) {
	Vertex<string> temp;
	temp = *edge->getFrom();
	cout << "Distance from " << edge->getFrom() << " to " << edge->getTo() << " is " << *edge << "kms." << endl;
	return;
}

template <class T>
void printVertex(Vertex<T> vertex) {
	cout << vertex.getValue() << endl;
	vector<EdgeBase*> edges;
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

	Vertex<string> pune("Pune");
	Vertex<string> delhi("Delhi");
	Vertex<string> mumbai("Mumbai");
	Vertex<string> chandigarh("Chandigarh");

	Vertex<string> goa;
	goa.setValue("Goa");
	cout << "Let's plan for " << string(goa) << endl;
	cout << goa.getValue() << "!!!!" << endl;


	Edge<int> ptod(1440, &pune, &delhi);
	Edge<int> ctop(1700);
	ctop.setFrom(&chandigarh);
	ctop.setTo(&pune);
	Edge<int> dtoc;
	dtoc.setValue(260);
	dtoc.setFrom(&delhi);
	dtoc.setTo(&chandigarh);
	Edge<int> ptom(&pune, &mumbai);
	ptom.setValue(150);
	
	cout << "Plan never succeeds. Not from atleast last " << ptom << " times." << endl;

	vector<EdgeBase*> puneEdges = { &ptod,&ptom };
	pune.setOutwardEdges(puneEdges);
	puneEdges = pune.getInwardEdges();
	puneEdges.push_back(&ctop);

	puneEdges = pune.getEdges();

	for (int i = 0; i < puneEdges.size(); i++) {
		printEdge(puneEdges[i]);
	}

	chandigarh.addOutwardEdge(&ctop);
	chandigarh.addInwardEdge(&dtoc);
	delhi.addOutwardEdge(&dtoc);
	delhi.addInwardEdge(&ptod);
	mumbai.addInwardEdge(&ptom);

	printVertex(pune);

	return;
}