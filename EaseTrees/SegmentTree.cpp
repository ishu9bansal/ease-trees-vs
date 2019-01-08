#include <iostream>
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
	vector<int> v = st.getValues();
	for (int i = 0; i < v.size(); i++) {
		if(i)	cout << "\t";
		cout << v[i];
	}
	cout << endl;
}
