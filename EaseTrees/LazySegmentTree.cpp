#include <iostream>
#include "LazySegmentTree.h"

void testLazySegmentTree()
{
	LazySegmentTree<int> lazyTree(5);
	//	0 0 0 0 0
	cout << lazyTree.query(2, 4) << endl;	// 0
	lazyTree.update(2, 5, 3);
	//	0 0 3 3 3
	cout << lazyTree.query(1, 3) << endl;	// 3
	lazyTree.update(3, 4, 7);
	//	0 0 3 10 3
	cout << lazyTree.query(2, 5) << endl;	// 16
	lazyTree.update(1, 4, 2);
	//	0 2 5 12 3
	cout << lazyTree.query(0, 3) << endl;	// 7
	cout << lazyTree.query(1, 4) << endl;	// 19
	lazyTree.update(2, 5, 3);
	//	0 2 8 15 6
	cout << lazyTree.query(0, 5) << endl;	// 31

}
