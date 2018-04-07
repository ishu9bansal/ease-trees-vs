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
	using graph<T>::addEdge;
	using graph<T>::removeVertex;
	using graph<T>::removeEdge;
	using graph<T>::checkEdge;

	bool checkEdge(Index x, Index y, bool direct) {
		if (!direct)	swap(x, y);
		return nodeMap[x]->isChild(nodeMap[y]) || nodeMap[y]->isParent(nodeMap[x]);
	}
	bool addVertex(const T& node) {
		if (graph<T>::addVertex(node)) {
			nodeMap.push_back(new Node<T>(node));
			return true;
		}
		return false;
	}
	void addEdge(Index x, Index y, bool direct) {
		if (!direct)	swap(x, y);
		nodeMap[x]->addChild(nodeMap[y]);
		nodeMap[y]->addParent(nodeMap[x]);
		return;
	}
	void removeEdge(Index x, Index y, bool direct) {
		if (!direct)	swap(x, y);
		nodeMap[x]->removeChild(nodeMap[y]);
		nodeMap[y]->removeParent(nodeMap[x]);
		return;
	}
	void removeVertex(Index nodeIndex) {
		graph<T>::removeVertex(nodeIndex);
		nodeMap[nodeIndex] = nodeMap.back();
		nodeMap.pop_back();
		return;
	}
	void addChild(const T& node, const T& child) {
		addEdge(node, child, true);
	}
	void addParent(const T& node, const T& child) {
		addEdge(node, child, false);
	}
	void addChildren(const T& node, const vector<T>& nodeList) {
		addVertex(node, nodeList, true);
	}
	void addParents(const T& node, const vector<T>& nodeList) {
		addVertex(node, nodeList, false);
	}
	void print() {
		graph<T>::print();
		cout << endl;
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
