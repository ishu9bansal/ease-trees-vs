#ifndef segment_tree_h
#define segment_tree_h

#include <vector>
#include <functional>
#include <unordered_set>
using namespace std;

template <class T>
struct SegmentNode {
	T value;
	int l;
	int r;
	SegmentNode* parent;
	SegmentNode* lchild;
	SegmentNode* rchild;
	SegmentNode(int leftIndex,
		int rightIndex,
		T nodeValue,
		SegmentNode* leftNode = NULL,
		SegmentNode* rightNode = NULL)
		: l(leftIndex), r(rightIndex), value(nodeValue),
		lchild(leftNode), rchild(rightNode), parent(NULL) {
		if (leftNode)	leftNode->parent = this;
		if (rightNode)	rightNode->parent = this;
	}
};

template <class T, T zero=NULL, class BinaryFunction = plus<T>>
class SegmentTree {
	// Tree structure is in a format that a segment node stores info for the index range [l,r)
	// l : inclusive, r : exclusive. So individual elements are stored in nodes like [2,3), [5,6) etc.
	// tree is maintained in such a way that all leaf nodes are in order [0,1), [1,2), [2,3) and so on.
	// then their parents are all even numbers [0,2), [2,4), [4,6) and so on.
	// then their parents are all multiples of 4 [0,4), [4,8), and so on.
	// like wise upto the top
private:
	SegmentNode<T> * root;
	vector<SegmentNode<T>*> leaf;
	BinaryFunction combine;
	SegmentNode<T>* makeTree(int l, int r, const vector<T> &v) {
		//	recursive solution
		//	TODO: make it iterative
		if (l + 1 == r)	return leaf[l] = new SegmentNode<T>(l, r, (l<v.size() ? v[l] : zero));
		int m = (l + r) / 2;
		SegmentNode<T>* left = makeTree(l, m, v);
		SegmentNode<T>* right = makeTree(m, r, v);
		T value = combine(left->value, right->value);
		return new SegmentNode<T>(l, r, value, left, right);
	}
	SegmentNode<T>* makeTree(int size, const vector<T> &v) {
		leaf.assign(size, NULL);
		return makeTree(0, size, v);
	}
	T query(SegmentNode<T>* node, int i, int j) {
		//	i: inclusive, j: exclusive
		if (!node)	return zero;
		if (i >= j || j <= node->l || i >= node->r)	return zero;
		if (j >= node->r&&i <= node->l)	return node->value;
		return query(node->lchild, i, j) + query(node->rchild, i, j);
	}
	void update(SegmentNode<T>* node) {
		if (!node)	return;
		if (!(node->lchild))	return;
		if (!(node->rchild))	node->value = node->lchild->value;
		else	node->value = combine(node->lchild->value, node->rchild->value);
	}
	void update(unordered_set<SegmentNode<T>* > &childSet) {
		unordered_set<SegmentNode<T>* > parentSet;
		while (!childSet.empty()) {
			parentSet.clear();
			for (auto node : childSet) {
				if (!node)	continue;
				parentSet.insert(node->parent);
				update(node);
			}
			swap(childSet, parentSet);
		}
		return;
	}
public:
	SegmentTree(const vector<T> &v) {
		int two = 2;
		int n = v.size();
		while (n / two)	two *= 2;
		root = makeTree(two, v);
	}
	SegmentTree(unsigned int n) {
		vector<T> v;	// empty vector, with size = 0
		int two = 2;
		while (n / two)	two *= 2;
		root = makeTree(two, v);
	}
	void update(int i, T value, int l = 1) {
		unordered_set<SegmentNode<T>* > h;
		for (int k = i; k < i + l && k < leaf.size(); k++) {
			leaf[k]->value = value;
			h.insert(leaf[k]->parent);
		}
		update(h);
	}
	void update(int i, const vector<T> &v) {
		unordered_set<SegmentNode<T>* > h;
		for (int k = 0; k < v.size() && k + i < leaf.size(); k++) {
			leaf[i + k]->value = v[k];
			h.insert(leaf[i + k]->parent);
		}
		update(h);
	}
	void leftCombine(int i, T value, int l = 1) {
		unordered_set<SegmentNode<T>* > h;
		for (int k = i; k < i + l && k < leaf.size(); k++) {
			leaf[k]->value = combine(value,leaf[k]->value);
			h.insert(leaf[k]->parent);
		}
		update(h);
	}
	void rightCombine(int i, T value, int l = 1) {
		unordered_set<SegmentNode<T>* > h;
		for (int k = i; k < i + l && k < leaf.size(); k++) {
			leaf[k]->value = combine(leaf[k]->value, value);
			h.insert(leaf[k]->parent);
		}
		update(h);
	}
	T query(int i, int j) {
		//	i: inclusive, j: exclusive
		return query(root, i, j);
	}
	T query(int i) {
		return leaf[i]->value;
	}
	vector<T> getValues() {
		vector<T> v(leaf.size());
		for (int i = 0; i < leaf.size(); i++) {
			v[i] = leaf[i]->value;
		}
		return v;
	}
};

void testSegmentTree();

#endif
