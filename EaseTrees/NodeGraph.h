#ifndef node_graph_h
#define node_graph_h

#include "graph.h"
#include "Node.h"
#include <vector>
#include <iostream>

template <class T>
class NodeGraph : public graph<T> {
	vector<Node<T>*> nodeMap;
public:
	using graph<T>::addVertex;
	using graph<T>::removeVertex;
	bool checkEdge(int x, int y, bool direct) {
		if (!direct)	swap(x, y);
		return nodeMap[x]->isChild(nodeMap[y]);
	}
	bool addVertex(const T& node) {
		if (graph<T>::addVertex(node)) {
			nodeMap.push_back(new Node<T>(node));
			return true;
		}
		return false;
	}
	void addEdge(int x, int y, bool direct) {
		if (!direct)	swap(x, y);
		nodeMap[x]->addChild(nodeMap[y]);
		return;
	}
	void removeEdge(int x, int y, bool direct) {
		if (!direct)	swap(x, y);
		nodeMap[x]->removeChild(nodeMap[y]);
		return;
	}
	void removeVertex(int nodeIndex) {
		graph<T>::removeVertex(nodeIndex);
		nodeMap[nodeIndex] = nodeMap.back();
		nodeMap.pop_back();
		return;
	}
	void print() {
		graph<T>::print();
		cout << "Adjacency List:" << endl;
		for (int i = 0; i < nodeMap.size(); i++) {
			vector<Node<T>*> children = nodeMap[i]->getChildren();
			cout << nodeMap[i]->getValue() << "\t|\t";
			for (int j = 0; j < children.size(); j++)
				cout << children[j]->getValue() << "->";
			cout << "|" << endl;
		}
		return;
	}

};

void testNodeGraph();

#endif // !node_graph_h
