#include "Node.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <class J>
void printTree(Node<J>* root, int depth = 0) {
	string head = "";
	head.append(depth, '\t');
	cout << head << root->getValue() << endl;
	vector<Node<J>*> v = root->getChildren();
	for (int i = 0; i<v.size(); i++)
		printTree(v[i], depth + 1);
	return;
}

template <class J>
void printUpsideDown(Node<J>* root, int depth = 0) {
	string head = "";
	head.append(depth, '\t');
	cout << head << root->getValue() << endl;
	vector<Node<J>*> v = root->getParents();
	for (int i = 0; i<v.size(); i++)
		printUpsideDown(v[i], depth + 1);
	return;
}

void testNode() {

	//      0		creating this tree structure
	//    / | \_
	//   1  2    6
	//  /|  /|  /|\
	// 3 4 5 7 8 9 10

	Node<int>* zero = new Node<int>(0);
	Node<int>* one = new Node<int>(1);
	Node<int>* two = new Node<int>(2);
	Node<int>* three = new Node<int>(3);
	Node<int>* four = new Node<int>(4);
	Node<int>* five = new Node<int>(5);
	Node<int>* six = new Node<int>(6);
	Node<int>* seven = new Node<int>(7);
	Node<int>* eight = new Node<int>(8);
	Node<int>* nine = new Node<int>(9);
	Node<int>* ten = new Node<int>(1);
	ten->setValue(10);
	cout << "Ten " << ten->getValue() << endl;
	cout << "Node print five " << *five << endl;

	vector<Node<int>*> v = { three,four };
	one->addChildren(v);
	v[0] = eight;
	v[1] = nine;
	v.push_back(ten);
	six->addChildren(v);
	v[0] = five;
	v[1] = seven;
	two->addChildren(v);
	cout << "is child ten in two " << two->isChild(ten) << endl;
	cout << "removed? " << two->removeChild(ten) << endl;

	(*zero).addChild(one);
	(*zero).addChild(two);
	(*zero).addChild(six);

	printTree(zero);

	cout << "To test the parents part, we can just repeat the same putting parent instead of child." << endl;
	cout << "This will also make the tree a bidirectional graph." << endl;

	v = { three,four };
	one->addParents(v);
	v[0] = eight;
	v[1] = nine;
	v.push_back(ten);
	six->addParents(v);
	v[0] = five;
	v[1] = seven;
	two->addParents(v);
	cout << "is parent ten in two " << two->isParent(ten) << endl;
	cout << "removed? " << two->removeParent(ten) << endl;

	(*zero).addParent(one);
	(*zero).addParent(two);
	(*zero).addParent(six);

	printUpsideDown(zero);

	return;
}