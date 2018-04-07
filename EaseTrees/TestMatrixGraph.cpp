#include "matrixGraph.h"
#include <string>
using namespace std;

template <class T>
void printTree(matrixGraph<T> tree, T root, int depth = 0) {
	// careful if it is not tree, it will go in an infinite loop.
	string empty = "";
	empty.append(depth, '\t');
	cout << empty << root << endl;
	vector<T> v = tree.map(tree.getChildren(root));
	for (int i = 0; i < v.size(); i++)
		printTree(tree, v[i], depth + 1);
	return;
}

void testMatrixGraph(){
	matrixGraph<string> strGraph;
	strGraph.addVertex("square");
	strGraph.addVertex("rectangle");
	strGraph.addVertex("2D array", { "square","rectangle" });
	strGraph.addVertex("nD array");
	strGraph.addVertex("matrix", { "2D array","nD array" });
	strGraph.addVertex("LOE");
	strGraph.addVertex("nodes edges");
	strGraph.addVertex("graph", { "matrix","nodes edges","LOE" });
	strGraph.print();
	string twoD = "2D array";
	string matrix = "matrix";
	vector<string> adj1 = strGraph.map(strGraph.getAdjacent(twoD));
	vector<string> adj2 = strGraph.map(strGraph.getAdjacent(matrix));
	for (int i = 0; i<adj1.size(); i++)	cout << '\t' << adj1[i];
	cout << endl;
	for (int i = 0; i<adj2.size(); i++)	cout << '\t' << adj2[i];
	cout << endl;
	string nD = "nD array";
	strGraph.removeVertex(nD);
	strGraph.print();

	cout << endl;
	cout << "Checking directed graph..............." << endl;
	cout << endl;

	matrixGraph<string> directed;
	directed.addChildren("abc", { "lmn","xyz" });
	directed.addParents("abc", { "uvw","lmn" });
	directed.addChild("xyz", "lmn");
	directed.print();

	cout << endl << "Testing graph<int>..............." << endl;
	// graph structure is as following
	//
	// 59
	// 	|--	70
	// 	---	63
	// 		|--	69
	// 		|--	71
	// 		|--	58
	// 		|	|--	64
	// 		|	---	65
	// 		---	66
	// 			|--	67
	// 			|--	68
	// 			---	72



	matrixGraph<int> intGraph;
	intGraph.addVertex(63, { 69,66,71 }, true);
	intGraph.addVertex(66, { 67,68,72 }, true);
	intGraph.addVertex(58, { 64,65 }, true);
	intGraph.addVertex(59, { 63,70 }, true);
	intGraph.addEdge(58, 63, false);
	//intGraph.print();
	printTree(intGraph, 59);

}
