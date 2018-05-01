#include <iostream>
#include <string>
#include "TreeNode.h"
using namespace std;

template <class T>
void printTree(TreeNode<T>* root, int depth = 0) {
	// careful if it is not tree, it will go in an infinite loop.
	string empty = "";
	empty.append(depth, '\t');
	cout << empty << root->getValue() << endl;
	vector<TreeNode<T>*> v = root->getChildren();
	for (int i = 0; i < v.size(); i++)
		printTree(v[i], depth + 1);
	return;
}

template <class T>
bool areParentsCorrect(TreeNode<T>* root, TreeNode<T>* parent = NULL) {
	if (!root->hasParent(parent))	return false;
	vector<TreeNode<T>*> children = root->getChildren();
	for (TreeNode<T>* child : children)
		if (!areParentsCorrect(child, root))	return false;
	return true;
}

void testTreeNode() {
	// tree structure is as following
	//
	//  0
	// 	|--	1
	// 	---	2
	// 		|--	3
	// 		|--	4
	// 		|--	5
	// 		|	|--	6
	// 		|	---	65
	// 		|--	66
	// 		|	|--	7
	// 		|	|--	8
	// 		|	---	9
	//		--- 67

	// Constructors
	vector<TreeNode<long>*> node(10);
	for (int i = 0; i < 10; i++) {
		node[i] = new TreeNode<long>(i);
	}
	TreeNode<long>* sixfiv = new TreeNode<long>(65,node[5]);
	TreeNode<long>* sixsix = new TreeNode<long>(66);
	TreeNode<long>* sixsvn = new TreeNode<long>(node[2]);
	sixsix->setParent(node[2]);
	sixsvn->setValue(67);
	
	vector<TreeNode<long>*> lastNodes = { node[7],node[8],node[9] };
	sixsix->addChildren(lastNodes);
	for (TreeNode<long>* last : lastNodes) {
		last->setParent(sixsix);
	}
	TreeNode<long>* two = sixsix->getParent();
	two->addChild(sixfiv);
	two->addChild(sixsix);
	two->addChild(sixsvn);
	two->removeChild(sixfiv);
	node[5]->addChild(sixfiv);

	if(!two->hasChild(sixfiv))
		cout << "sixty five is not a child of two. it was a mistake." << endl;

	node[0]->addChild(node[1]);
	node[0]->addChild(node[2]);
	node[2]->addChild(node[3]);
	node[2]->addChild(node[4]);
	node[2]->addChild(node[5]);
	node[5]->addChild(node[6]);

	node[1]->setParent(node[0]);
	node[2]->setParent(node[0]);
	node[3]->setParent(node[2]);
	node[4]->setParent(node[2]);
	node[5]->setParent(node[2]);
	node[6]->setParent(node[5]);

	if (areParentsCorrect(node[0]))
		cout << "The tree is constructed gracefully." << endl;

	printTree(node[0]);

}