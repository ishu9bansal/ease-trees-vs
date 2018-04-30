#include <iostream>
#include <string>
#include "LoEGraph.h"
using namespace std;

void testLoEGraph() {
	// Pune ---150---> Mumbai
	//	^	\
	//	|	 \
	//	|	  \			Road Map refference
	// 1700	   \
	//	|		\_____1440_____
	//	|					  v
	// Chandigarh <---260--- Delhi

	string pune = "Pune";
	string deli = "Delhi";
	string mubi = "Mumbai";
	string chnd = "Chandigarh";

	LoEGraph<string, int> citygraph(0, 0);

	citygraph.addVertex(chnd);
	citygraph.addVertex(deli);
	citygraph.addEdge(deli, chnd, true, 260);
	citygraph.addChild(chnd, pune);
	citygraph.setWeight(chnd, pune, 1700);
	citygraph.addEdge(pune, deli, true, 1440);
	citygraph.addEdge(mubi, pune, false, 150);

	citygraph.print();
}