#ifndef node_h
#define node_h


#include <vector>
#include <unordered_set>
using namespace std;


template <class T>
class Node {
private:
	T value;
	unordered_set<Node*> parents;
	unordered_set<Node*> children;
public:
	Node(T t) : value(t) {}
	T getValue() {
		return value;
	}
	void setValue(T t) {
		value = t;
		return;
	}
	vector<Node*> getChildren() {// both Node* and Node<T>* will work
		vector<Node*> v;
		for (const auto& childRef : children) {
			v.push_back(childRef);
		}
		return v;
	}
	bool isChild(Node* nodeRef) {
		return children.find(nodeRef) != children.end();
	}
	void addChild(Node* nodeRef) {
		children.insert(nodeRef);
	}
	bool removeChild(Node* nodeRef) {	// returns true if remove was successful 
		return children.erase(nodeRef);
	}
	void addChildren(const vector<Node*>& v) {
		children.insert(v.begin(), v.end());
	}
	vector<Node*> getParents() {// both Node* and Node<T>* will work
		vector<Node*> v;
		for (const auto& parentRef : parents) {
			v.push_back(parentRef);
		}
		return v;
	}
	bool isParent(Node* nodeRef) {
		return parents.find(nodeRef) != parents.end();
	}
	void addParent(Node* nodeRef) {
		parents.insert(nodeRef);
	}
	bool removeParent(Node* nodeRef) {	// returns true if remove was successful 
		return parents.erase(nodeRef);
	}
	void addParents(const vector<Node*>& v) {
		parents.insert(v.begin(), v.end());
	}
	operator T() {
		return value;
	}
};

void testNode();

#endif
