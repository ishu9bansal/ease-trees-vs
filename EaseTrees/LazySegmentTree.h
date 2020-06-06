#ifndef lazy_segment_tree_h
#define lazy_segment_tree_h

#include <queue>
#include <vector>
#include <functional>
#include <unordered_set>
using namespace std;

template <class T>
struct LazySegmentNode {
	T value;
	T lazy;
	int l;
	int r;
	LazySegmentNode* parent;
	LazySegmentNode* lchild;
	LazySegmentNode* rchild;
	LazySegmentNode(int leftIndex,
		int rightIndex,
		T nodeValue,
		T lazyValue,
		LazySegmentNode* leftNode = NULL,
		LazySegmentNode* rightNode = NULL)
		: l(leftIndex), r(rightIndex), value(nodeValue), lazy(lazyValue),
		lchild(leftNode), rchild(rightNode), parent(NULL) {
		if (leftNode)	leftNode->parent = this;
		if (rightNode)	rightNode->parent = this;
	}
};

template <class T>
struct multiply {
	T operator()(int i, int j, T value) {
		return value * (j - i);
	}
};

template <class T, T zero = NULL, class BinaryFunction = plus<T>, class MultiplyFunction = multiply<T>>
class LazySegmentTree {
	// Tree structure is in a format that a segment node stores info for the index range [l,r)
	// l : inclusive, r : exclusive. So individual elements are stored in nodes like [2,3), [5,6) etc.
	// tree is maintained in such a way that all leaf nodes are in order [0,1), [1,2), [2,3) and so on.
	// then their parents are all even numbers [0,2), [2,4), [4,6) and so on.
	// then their parents are all multiples of 4 [0,4), [4,8), and so on.
	// like wise upto the top
private:
	LazySegmentNode<T>* root;

	//	both these functions should have same complexity
	BinaryFunction combine;
	MultiplyFunction bulkCombine;

	LazySegmentNode<T>* makeTree(int l, int r, const vector<T> &v) {
		if(l>=r)    return NULL;    // validation check
		//	if leaf node, create node with the values
		if (l + 1 == r)	return new LazySegmentNode<T>(l, r, (v.size()?v[l]:zero), zero);
		int m = (l + r) / 2;
		//	make child trees recursivelly
		LazySegmentNode<T>* left = makeTree(l, m, v);
		LazySegmentNode<T>* right = makeTree(m, r, v);
		//	set the current node value from newly made trees
		T value = combine(left->value, right->value);
		//	return the current tree refrence
		return new LazySegmentNode<T>(l, r, value, zero, left, right);
	}
	void makeTree(const vector<T> &v) {
		root = makeTree(0, v.size(), v);
	}
	void makeTree(int n) {
		vector<T> empty;
		root = makeTree(0, n, empty);
	}
	T combineValueOf(LazySegmentNode<T>* node) {
		if (!node)	return zero;
		//	use bulk combine operation to make the lazy value to be added to true value
		//	this bulk combine should be of same complexity as combine
		//	otherwiise this implementation is useless
		T lazyValue = bulkCombine(node->l, node->r, node->lazy);
		return combine(node->value, lazyValue);
	}
	void resolve(LazySegmentNode<T>* node) {
		//	this function resolves the given node to its true value,
		//	i.e., it passes its lazy value to its children and clear it
		if (!node)	return;
		//	if lazy value is zero no need to proceed, it is already resolved
		if (node->lazy==zero)	return;
		//	if child exist, add parent's lazy value to its own
		if (node->lchild)	node->lchild->lazy = combine(node->lchild->lazy, node->lazy);
		if (node->rchild)	node->rchild->lazy = combine(node->rchild->lazy, node->lazy);
		//	resolve node's lazy value into its true value, and set lazy zero
		node->value = combineValueOf(node);
		node->lazy = zero;
		return;
	}
	T query(LazySegmentNode<T>* node, int i, int j) {
		//	i: inclusive, j: exclusive
		if (!node)	return zero;
		//	node range do not intersect with given range, then just return zero
		if (i >= j || j <= node->l || i >= node->r)	return zero;
		//	resolve the current node to hold the true value
		resolve(node);
		//	node range is completely inside given range, blindly return the resolved node value
		if (j >= node->r&&i <= node->l)	return node->value;
		//	else recursivelly get results from children
		return combine(query(node->lchild, i, j), query(node->rchild, i, j));
	}
	void update(LazySegmentNode<T>* node, int i, int j, T value) {
		//	add given value to all nodes under given node which lies in the given range
		if (!node)	return;
		//	node range do not intersect with given range, then just return
		if (i >= j || j <= node->l || i >= node->r)	return;
		//	node range is completely inside given range, blindly update lazy
		if (j >= node->r&&i <= node->l) {
			node->lazy = combine(node->lazy, value);
			return;
		}
		//	else, resolve the current node to hold the true value and pass any lazy parameters to its children
		resolve(node);
		//	then update the children recursivelly
		update(node->lchild, i, j, value);
		update(node->rchild, i, j, value);
		//	now update the value of current node as its children are updated
		node->value = combine(combineValueOf(node->lchild), combineValueOf(node->rchild));
		node->lazy = zero;
		return;
	}
public:
	LazySegmentTree(unsigned int n) {
		makeTree(n);
	}
	LazySegmentTree(const vector<T> &v) {
		makeTree(v);
	}
	void update(int i, int j, T value) {
		// this update will combine the given value 
		// with each of the element in the given range
		update(root, i, j, value);
	}
	void update(int i, T value) {
		// this updates a single element by performing combine
		// operation of current value with the given value
		update(i, i + 1, value);
	}
	T query(int i, int j) {
		// this will return the result of query in the given range
		//	i: inclusive, j: exclusive
		return query(root, i, j);
	}
	T query(int i) {
		// this will return the current value of the ith element
		return query(root, i, i + 1);
	}
};

void testLazySegmentTree();

#endif
