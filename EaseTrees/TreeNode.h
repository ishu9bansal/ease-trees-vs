#ifndef tree_node_h
#define tree_node_h


#include <vector>
#include <unordered_set>
using namespace std;


template <class T>
class TreeNode {
private:
	T value;
	TreeNode* parent;
	unordered_set<TreeNode*> children;
public:
	TreeNode(T t) : value(t) {}
	TreeNode(TreeNode* node) : parent(node) {}
	TreeNode(T t, TreeNode* node) : value(t), parent(node) {}
	T getValue() {
		return value;
	}
	void setValue(T t) {
		value = t;
		return;
	}
	vector<TreeNode*> getChildren() {// both TreeNode* and TreeNode<T>* will work
		vector<TreeNode*> v;
		for (const auto& childRef : children) {
			v.push_back(childRef);
		}
		return v;
	}
	bool hasChild(TreeNode* nodeRef) {
		return children.find(nodeRef) != children.end();
	}
	void addChild(TreeNode* nodeRef) {
		children.insert(nodeRef);
	}
	bool removeChild(TreeNode* nodeRef) {	// returns true if remove was successful 
		return children.erase(nodeRef);
	}
	void addChildren(const vector<TreeNode*>& v) {
		children.insert(v.begin(), v.end());
	}
	TreeNode* getParent() {
		return parent;
	}
	bool hasParent(TreeNode* nodeRef) {
		return nodeRef == parent;
	}
	void setParent(TreeNode* nodeRef) {
		parent = nodeRef;
	}
	bool removeParent(TreeNode* nodeRef) {	// returns true if remove was successful 
		if (!parent)	return false;
		parent = NULL;
		return true;
	}
	operator T() {
		return value;
	}
};

void testTreeNode();

#endif
