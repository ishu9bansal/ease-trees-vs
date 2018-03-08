#ifndef graph_h
#define graph_h

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

template <class T>
class graph {
protected:
	unordered_map<T, int> dataMap;
	vector<T> reverseMap;
public:
	graph() {
	}
	~graph() {
		dataMap.clear();
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
	virtual void removeVertex(int nodeIndex) {
		// it replaces the last added obj at that place
		T lastNode = reverseMap.back();
		dataMap[lastNode] = nodeIndex;
		dataMap.erase(reverseMap[nodeIndex]);
		reverseMap[nodeIndex] = lastNode;
		reverseMap.pop_back();
		return;
	}
	virtual bool checkEdge(int, int, bool) = 0;	// pure virtual function
	virtual bool checkEdge(int a, int b) {
		return checkEdge(a, b, true) || checkEdge(a, b, false);
	}
	virtual bool checkEdge(const T& nodeA, const T& nodeB, bool AtoB) {
		return checkEdge(dataMap[nodeA], dataMap[nodeB], AtoB);
	}
	virtual bool checkEdge(const T& nodeA, const T& nodeB) {
		return checkEdge( dataMap[nodeA], dataMap[nodeB]);
	}

	virtual void addEdge(int, int, bool) = 0;		// pure virtual function
	virtual void addEdge(int a, int b) {
		addEdge(a, b, true);
		addEdge(a, b, false);
	}
	virtual void addEdge(const T& nodeA, const T& nodeB, bool AtoB) {
		addEdge(dataMap[nodeA], dataMap[nodeB], AtoB);
	}
	virtual void addEdge(const T& nodeA, const T& nodeB) {
		addEdge(dataMap[nodeA], dataMap[nodeB]);
	}
	virtual void addVertex(const T& node, const vector<T>& nodeList, vector<bool> newToOld) {
		addVertex(node);
		int nodeIndex = dataMap[node];
		for (int i = 0; i<nodeList.size(); i++)
			addEdge(nodeIndex, dataMap[nodeList[i]], newToOld[i]);
	}
	virtual void addVertex(const T& node, const vector<T>& nodeList, bool newToOld) {
		addVertex(node);
		int nodeIndex = dataMap[node];
		for (int i = 0; i<nodeList.size(); i++)
			addEdge(nodeIndex, dataMap[nodeList[i]], newToOld);
	}
	virtual void addVertex(const T& node, const vector<T>& nodeList) {
		addVertex(node);
		int nodeIndex = dataMap[node];
		int s = nodeList.size();
		for (int i = 0; i<s; i++)
			addEdge(nodeIndex, dataMap[nodeList[i]]);
		return;
	}
	virtual void removeEdge(int, int, bool) = 0;		// pure virtual function
	virtual void removeEdge(int a, int b) {
		removeEdge(a, b, true);
		removeEdge(a, b, false);
	}
	virtual void removeEdge(const T& nodeA, const T& nodeB, bool AtoB) {
		removeEdge(dataMap[nodeA], dataMap[nodeB], AtoB);
	}
	virtual void removeEdge(const T& nodeA, const T& nodeB) {
		removeEdge(dataMap[nodeA], dataMap[nodeB]);
	}
	virtual vector<int> getChildren(int x) {
		vector<int> result;
		for (int i = 0; i<reverseMap.size(); i++) {
			if (checkEdge(x, i, true))	result.push_back(i);
		}
		return result;
	}
	virtual vector<int> getParents(int x) {
		vector<int> result;
		for (int i = 0; i<reverseMap.size(); i++) {
			if (checkEdge(x, i, false))	result.push_back(i);
		}
		return result;
	}
	virtual vector<int> getAdjacent(int x) {
		vector<int> result;
		for (int i = 0; i<reverseMap.size(); i++) {
			if (checkEdge(x, i, true) || checkEdge(x, i, false))	result.push_back(i);
		}
		return result;
	}
	virtual vector<int> getChildren(const T& node) {
		return getChildren(dataMap[node]);
	}
	virtual vector<int> getParents(const T& node) {
		return getParents(dataMap[node]);
	}
	virtual vector<int> getAdjacent(const T& node) {
		return getAdjacent(dataMap[node]);
	}
	virtual void removeEdgesFrom(int nodeIndex) {
		vector<int> adjacent = getChildren(nodeIndex);
		for (int i = 0; i<adjacent.size(); i++)
			removeEdge(nodeIndex, adjacent[i], true);
	}
	virtual void removeEdgesFrom(const T& node) {
		removeEdgesFrom(dataMap[node]);
	}
	virtual void removeEdgesTo(int nodeIndex) {
		vector<int> adjacent = getParents(nodeIndex);
		for (int i = 0; i<adjacent.size(); i++)
			removeEdge(nodeIndex, adjacent[i], false);
	}
	virtual void removeEdgesTo(const T& node) {
		removeEdgesTo(dataMap[node]);
	}
	virtual void removeEdgesOf(int nodeIndex) {
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
		int temp = dataMap[nodeA];
		dataMap[nodeA] = dataMap[nodeB];
		dataMap[nodeB] = temp;
		reverseMap[dataMap[nodeA]] = nodeA;
		reverseMap[dataMap[nodeB]] = nodeB;
	}
	*/
	virtual void print() {
		cout << "Total vertices in graph: " << reverseMap.size() << endl;
		cout << "Vertex Mapping:" << endl;
		for (int i = 0; i<reverseMap.size(); i++) {
			cout << i << "\t" << reverseMap[i] << endl;
		}
	}

};

#endif // !graph_h
