#include <iostream>
#include "inout.h"
#include "SegmentTree.h"

using namespace std;

void testSegmentTree(){
	SegmentTree<int> st(5);
	print(st.getValues());
	cout << "2,5\t" << st.query(2, 5) << endl;
	st.update(3, 7);
	print(st.getValues());
	cout << "3,4\t" << st.query(3, 4) << endl;
	cout << "0,2\t" << st.query(0, 2) << endl;
	st.update(6, 7);
	print(st.getValues());
	cout << "0,8\t" << st.query(0, 8) << endl;
	cout << "3:\t" << st.query(3) << endl;
	cout << "4:\t" << st.query(4) << endl;
	print(st.getValues());
	vector<int> v;
	st.leftCombine(3, 5, 3);
	v = st.getValues();
	print(v);
	st.update(2, v);
	print(st.getValues());

	cout << "Testing iterative implementation" << endl;

	vector<int> inputVector = { 3,4,5,7,2,4,1,6,5,5,4,1,8,6,3,9,4,6,7,5,2 };
	SegmentTree<int> tree(inputVector);
	print(tree.getValues());
	tree.leftCombine(4, 5, 7);
	print(tree.getValues());
	cout << "2,5\t" << tree.query(2, 5) << endl;
	tree.update(3, 7);
	print(tree.getValues());
	cout << "3,4\t" << tree.query(3, 4) << endl;
	cout << "0,2\t" << tree.query(0, 2) << endl;
	tree.update(6, 7);
	print(tree.getValues());
	cout << "0,8\t" << tree.query(0, 8) << endl;
	cout << "3:\t" << tree.query(3) << endl;
	cout << "4:\t" << tree.query(4) << endl;

}
