#ifndef node_h
#define node_h


#include <vector>
#include <unordered_set>
using namespace std;


template <class T>
class Node {
private:
	T value;
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
	int addChildren(const vector<Node*>& v) {
		int count = 0;
		for (int i = 0; i<v.size(); i++) {
			if (!isChild(v[i])) {
				addChild(v[i]);
				count++;
			}
		}
		return count;
	}
	operator T() {
		return value;
	}
};

void testNode();

#endif
