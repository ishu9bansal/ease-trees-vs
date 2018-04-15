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

template <class U>
class Weight {
	U x;
public:
	Weight(U i) :x(i) {}
	Weight() :x(0) {}
	operator U() {
		return x;
	}
};
template <class T, class U=bool>
class graph {
protected:
	unordered_map<T, Index> dataMap;
	vector<T> reverseMap;
	static Weight<U> zero;
	static Weight<U> one;
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
		removeEdgesOf(nodeIndex);
		T lastNode = reverseMap.back();
		dataMap[lastNode] = nodeIndex;
		dataMap.erase(reverseMap[nodeIndex]);
		reverseMap[nodeIndex] = lastNode;
		reverseMap.pop_back();
		return;
	}
	virtual bool checkEdge(Index, Index, bool) = 0;	// pure virtual function
	bool checkEdge(Index a, Index b) {
		return checkEdge(a, b, true) || checkEdge(a, b, false);
	}
	bool checkEdge(const T& nodeA, const T& nodeB, bool AtoB) {
		return checkEdge(dataMap[nodeA], dataMap[nodeB], AtoB);
	}
	bool checkEdge(const T& nodeA, const T& nodeB) {
		return checkEdge( dataMap[nodeA], dataMap[nodeB]);
	}

	virtual void vAddEdge(Index, Index, bool) = 0;		// pure virtual function
	virtual void addEdge(Index a, Index b, bool AtoB, Weight<U> w = one) {
		vAddEdge(a, b, AtoB);
	}
	void addEdge(Index a, Index b, Weight<U> w = one) {
		addEdge(a, b, true, w);
		addEdge(a, b, false, w);
	}
	void addEdge(const T& nodeA, const T& nodeB, bool AtoB, Weight<U> w = one) {
		addVertex(nodeA);
		addVertex(nodeB);
		addEdge(dataMap[nodeA], dataMap[nodeB], AtoB, w);
	}
	void addEdge(const T& nodeA, const T& nodeB, Weight<U> w = one) {
		addVertex(nodeA);
		addVertex(nodeB);
		addEdge(dataMap[nodeA], dataMap[nodeB], w);
	}
	void addVertex(const T& node, const vector<T>& nodeList, vector<bool> newToOld) {
		addVertex(node);
		Index nodeIndex = dataMap[node];
		for (int i = 0; i < nodeList.size(); i++) {
			addVertex(nodeList[i]);
			addEdge(nodeIndex, dataMap[nodeList[i]], newToOld[i]);
		}
	}
	void addVertex(const T& node, const vector<T>& nodeList, bool newToOld) {
		addVertex(node);
		Index nodeIndex = dataMap[node];
		for (int i = 0; i < nodeList.size(); i++) {
			addVertex(nodeList[i]);
			addEdge(nodeIndex, dataMap[nodeList[i]], newToOld);
		}
	}
	void addVertex(const T& node, const vector<T>& nodeList) {
		addVertex(node);
		Index nodeIndex = dataMap[node];
		int s = nodeList.size();
		for (int i = 0; i<s; i++)
			addEdge(nodeIndex, dataMap[nodeList[i]]);
		return;
	}
	virtual void removeEdge(Index, Index, bool) = 0;		// pure virtual function
	void removeEdge(Index a, Index b) {
		removeEdge(a, b, true);
		removeEdge(a, b, false);
	}
	void removeEdge(const T& nodeA, const T& nodeB, bool AtoB) {
		removeEdge(dataMap[nodeA], dataMap[nodeB], AtoB);
	}
	void removeEdge(const T& nodeA, const T& nodeB) {
		removeEdge(dataMap[nodeA], dataMap[nodeB]);
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
	vector<Index> getChildren(Index x) {
		vector<Index> result;
		for (int i = 0; i<reverseMap.size(); i++) {
			if (checkEdge(x, Index(i), true))	result.push_back(i);
		}
		return result;
	}
	vector<Index> getParents(Index x) {
		vector<Index> result;
		for (int i = 0; i<reverseMap.size(); i++) {
			if (checkEdge(x, Index(i), false))	result.push_back(i);
		}
		return result;
	}
	vector<Index> getAdjacent(Index x) {
		vector<Index> result;
		for (int i = 0; i<reverseMap.size(); i++) {
			if (checkEdge(x, Index(i)))	result.push_back(i);
		}
		return result;
	}
	vector<Index> getChildren(const T& node) {
		return getChildren(dataMap[node]);
	}
	vector<Index> getParents(const T& node) {
		return getParents(dataMap[node]);
	}
	vector<Index> getAdjacent(const T& node) {
		return getAdjacent(dataMap[node]);
	}
	void removeEdgesFrom(Index nodeIndex) {
		vector<Index> adjacent = getChildren(nodeIndex);
		for (int i = 0; i<adjacent.size(); i++)
			removeEdge(nodeIndex, adjacent[i], true);
	}
	void removeEdgesFrom(const T& node) {
		removeEdgesFrom(dataMap[node]);
	}
	void removeEdgesTo(Index nodeIndex) {
		vector<Index> adjacent = getParents(nodeIndex);
		for (int i = 0; i<adjacent.size(); i++)
			removeEdge(nodeIndex, adjacent[i], false);
	}
	void removeEdgesTo(const T& node) {
		removeEdgesTo(dataMap[node]);
	}
	void removeEdgesOf(Index nodeIndex) {
		removeEdgesFrom(nodeIndex);
		removeEdgesTo(nodeIndex);
	}
	void removeEdgesOf(const T& node) {
		return removeEdgesOf(dataMap[node]);
	}
	void removeVertex(const T& node) {
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
			cout << i << "\t";
		}
		cout << endl;
		for (int i = 0; i<reverseMap.size(); i++) {
			cout << reverseMap[i] << "\t";
		}
		cout << endl;
	}

};

template<class T>
Weight<bool> graph<T, bool>::zero = Weight<bool>(0);

#endif // !graph_h
