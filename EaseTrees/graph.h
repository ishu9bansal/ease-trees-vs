#ifndef graph_h
#define graph_h

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Index {
	int x;
public:
	Index(int i) :x(i) {}
	Index() :x(0) {}
	operator int() {
		return x;
	}

};

template <class T>
class graph {
protected:
	unordered_map<T, Index> dataMap;
	vector<T> reverseMap;
public:
	graph() {
	}
	~graph() {
		dataMap.clear();
	}
	Index indexOf(const T& node) {
		return dataMap[node];
	}
	vector<Index> indexOf(const vector<T>& nodeList) {
		vector<Index> iList;
		for (int i = 0; i < nodeList.size(); i++) {
			iList.push_back(dataMap[nodeList[i]]);
		}
		return iList;
	}
	T vertexAt(Index i) {
		return reverseMap[i];
	}
	vector<T> map(vector<Index> iList) {
		vector<T> result;
		for (int i = 0; i < iList.size(); i++) {
			result.push_back(reverseMap[iList[i]]);
		}
		return result;
	}

	virtual bool checkVertex(const T& node) {
		return dataMap.find(node) != dataMap.end();
	}
	virtual bool addVertex(const T& node) {
		if (checkVertex(node))	return false;
		dataMap[node] = reverseMap.size();
		reverseMap.push_back(node);
		return true;
	}
	virtual void removeVertex(Index nodeIndex) {
		// it replaces the last added obj at that place
		T lastNode = reverseMap.back();
		dataMap[lastNode] = nodeIndex;
		dataMap.erase(reverseMap[nodeIndex]);
		reverseMap[nodeIndex] = lastNode;
		reverseMap.pop_back();
		return;
	}
	virtual bool checkEdge(Index, Index, bool) = 0;	// pure virtual function
	virtual bool checkEdge(Index a, Index b) {
		return checkEdge(a, b, true) || checkEdge(a, b, false);
	}
	virtual bool checkEdge(const T& nodeA, const T& nodeB, bool AtoB) {
		return checkEdge(dataMap[nodeA], dataMap[nodeB], AtoB);
	}
	virtual bool checkEdge(const T& nodeA, const T& nodeB) {
		return checkEdge( dataMap[nodeA], dataMap[nodeB]);
	}

	virtual void addEdge(Index, Index, bool) = 0;		// pure virtual function
	virtual void addEdge(Index a, Index b) {
		addEdge(a, b, true);
		addEdge(a, b, false);
	}
	virtual void addEdge(const T& nodeA, const T& nodeB, bool AtoB) {
		addVertex(nodeA);
		addVertex(nodeB);
		addEdge(dataMap[nodeA], dataMap[nodeB], AtoB);
	}
	virtual void addEdge(const T& nodeA, const T& nodeB) {
		addVertex(nodeA);
		addVertex(nodeB);
		addEdge(dataMap[nodeA], dataMap[nodeB]);
	}
	virtual void addVertex(const T& node, const vector<T>& nodeList, vector<bool> newToOld) {
		addVertex(node);
		Index nodeIndex = dataMap[node];
		for (int i = 0; i < nodeList.size(); i++) {
			addVertex(nodeList[i]);
			addEdge(nodeIndex, dataMap[nodeList[i]], newToOld[i]);
		}
	}
	virtual void addVertex(const T& node, const vector<T>& nodeList, bool newToOld) {
		addVertex(node);
		Index nodeIndex = dataMap[node];
		for (int i = 0; i < nodeList.size(); i++) {
			addVertex(nodeList[i]);
			addEdge(nodeIndex, dataMap[nodeList[i]], newToOld);
		}
	}
	virtual void addVertex(const T& node, const vector<T>& nodeList) {
		addVertex(node);
		Index nodeIndex = dataMap[node];
		int s = nodeList.size();
		for (int i = 0; i<s; i++)
			addEdge(nodeIndex, dataMap[nodeList[i]]);
		return;
	}
	virtual void removeEdge(Index, Index, bool) = 0;		// pure virtual function
	virtual void removeEdge(Index a, Index b) {
		removeEdge(a, b, true);
		removeEdge(a, b, false);
	}
	virtual void removeEdge(const T& nodeA, const T& nodeB, bool AtoB) {
		removeEdge(dataMap[nodeA], dataMap[nodeB], AtoB);
	}
	virtual void removeEdge(const T& nodeA, const T& nodeB) {
		removeEdge(dataMap[nodeA], dataMap[nodeB]);
	}
	virtual vector<Index> getChildren(Index x) {
		vector<Index> result;
		for (int i = 0; i<reverseMap.size(); i++) {
			if (checkEdge(x, Index(i), true))	result.push_back(i);
		}
		return result;
	}
	virtual vector<Index> getParents(Index x) {
		vector<Index> result;
		for (int i = 0; i<reverseMap.size(); i++) {
			if (checkEdge(x, Index(i), false))	result.push_back(i);
		}
		return result;
	}
	virtual vector<Index> getAdjacent(Index x) {
		vector<Index> result;
		for (int i = 0; i<reverseMap.size(); i++) {
			if (checkEdge(x, Index(i)))	result.push_back(i);
		}
		return result;
	}
	virtual vector<Index> getChildren(const T& node) {
		return getChildren(dataMap[node]);
	}
	virtual vector<Index> getParents(const T& node) {
		return getParents(dataMap[node]);
	}
	virtual vector<Index> getAdjacent(const T& node) {
		return getAdjacent(dataMap[node]);
	}
	virtual void removeEdgesFrom(Index nodeIndex) {
		vector<Index> adjacent = getChildren(nodeIndex);
		for (int i = 0; i<adjacent.size(); i++)
			removeEdge(nodeIndex, adjacent[i], true);
	}
	virtual void removeEdgesFrom(const T& node) {
		removeEdgesFrom(dataMap[node]);
	}
	virtual void removeEdgesTo(Index nodeIndex) {
		vector<Index> adjacent = getParents(nodeIndex);
		for (int i = 0; i<adjacent.size(); i++)
			removeEdge(nodeIndex, adjacent[i], false);
	}
	virtual void removeEdgesTo(const T& node) {
		removeEdgesTo(dataMap[node]);
	}
	virtual void removeEdgesOf(Index nodeIndex) {
		removeEdgesFrom(nodeIndex);
		removeEdgesTo(nodeIndex);
	}
	virtual void removeEdgesOf(const T& node) {
		return removeEdgesOf(dataMap[node]);
	}
	virtual void removeVertex(const T& node) {
		removeVertex(dataMap[node]);
	}

	/*
	virtual void change(const T& nodeA, const T& nodeB) {
		Index temp = dataMap[nodeA];
		dataMap[nodeA] = dataMap[nodeB];
		dataMap[nodeB] = temp;
		reverseMap[dataMap[nodeA]] = nodeA;
		reverseMap[dataMap[nodeB]] = nodeB;
	}
	*/
	virtual void print() {
		cout << endl;
		cout << "Total vertices in graph: " << reverseMap.size() << endl;
		cout << "Vertex Mapping:" << endl;
		for (int i = 0; i<reverseMap.size(); i++) {
			cout << i << "\t" << reverseMap[i] << endl;
		}
	}

};

#endif // !graph_h
