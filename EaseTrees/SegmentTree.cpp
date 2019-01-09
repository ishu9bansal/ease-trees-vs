#include <iostream>
#include "inout.h"
#include "SegmentTree.h"

using namespace std;

void testSegmentTree(){
	SegmentTree<int> st(5);
	cout<<st.query(2, 5)<<endl;
	st.update(3, 7);
	cout << st.query(3, 4) << endl;
	cout << st.query(0, 2) << endl;
	st.update(6, 7);
	cout << st.query(0, 8) << endl;
	cout << st.query(3) << endl;
	cout << st.query(4) << endl;
	print(st.getValues());
	vector<int> v;
	st.update(4, 2, 5);
	v = st.getValues();
	print(v);
	st.update(2, v);
	print(st.getValues());
}
