#include "NodeGraph.h"
#include <string>
using namespace std;

void testNodeGraph() {
	NodeGraph<string> strGraph;
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
}