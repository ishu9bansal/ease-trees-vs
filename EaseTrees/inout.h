#ifndef inout_h
#define inout_h

#include <iostream>
#include <vector>
using namespace std;

template <class T>
void print(const vector<T> &v) {
	for (int i = 0; i < v.size(); i++) {
		if (i)	cout << '\t';
		cout << v[i];
	}
	cout << endl;
}

template <class T>
void inputVector(vector<T> &v) {
	v.clear();
	int n,x;
	cin >> n;
	while (n--) {
		cin >> x;
		v.push_back(x);
	}
	return;
}

template <class T>
vector<T> inputVector() {
	vector<T> v;
	inputVector(v);
	return v;
}

void testInout();

#endif
