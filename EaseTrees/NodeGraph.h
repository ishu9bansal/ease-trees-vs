#ifndef node_graph_h
#define node_graph_h

#include "graph.h"
#include "Node.h"
#include <vector>
#include <iostream>

template <class T>
class NodeGraph : public graph<T> {
	vector<Node<T>*> nodeMap;
	bool strong;
public:
	using graph<T>::addVertex;
	using graph<T>::addEdge;
	using graph<T>::removeVertex;
	NodeGraph() : strong(false) {
		// this boolean tells that wether it will stick to its implementation strongly or not.
		// if strong is true,
		// then if user changes the graph in a form that it changes the directional structure it will react abruptly
		// e.g. if user removes the child relation and didn't remove the parent relation and strong is on, 
		// then it will check the relation both sides, because it is not complete hence will return false
		// whereas if strong is off, only the partial relation like in this case will return true

		// by default it is NOT strong; i.e. strong = false;

		// keeping it default false, will make it usefull in case when we are not using this node as parent child node
		// when we use it regarding only children and not use parent, 
		// there will not be any concept of strong and hence should give true results.
	}

	NodeGraph(bool bul) :strong(bul) {}
  
	bool checkEdge(Index x, Index y, bool direct) {
		if (!direct)	swap(x, y);
		if (strong)
			return nodeMap[x]->isChild(nodeMap[y]) && nodeMap[y]->isParent(nodeMap[x]);
		else
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
