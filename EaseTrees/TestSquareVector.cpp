#include "SquareVector.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;


void print(const vector<vector<char> > &v) {
	for (int i = 0; i<v.size(); i++) {
		for (int j = 0; j<v[i].size(); j++) {
			if (j)	cout << '\t';
			cout << v[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void testSquareVector() {
	vector<vector<char> > demo(4, vector<char>(4));
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			demo[i][j] = 'a' + 4 * i + j;
	cout << "demo:" << endl;
	print(demo);

	vectorSquare<char> square1(demo);
	cout << "square1" << endl;
	cout << square1 << endl;

	vectorSquare<char> square2(4);
	vectorSquare<char> square3;
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			square2(i, j) = 'a' + 4 * i + j;
	cout << "square2" << endl;
	cout << square2 << endl;

	vector<vector<char> > internal = square1.getInternalStructure();
	cout << "square1 internal:" << endl;
	print(internal);

	vector<vector<char> > external = square2.getData();
	cout << "square2 external:" << endl;
	print(external);

	square3.addOne();
	square3(0, 0) = 'a';

	square3.addOne(internal[1]);
	square3.addOne(internal[2]);
	square3.addOne(internal[3]);

	cout << "square3 " << endl;
	cout << square3 << endl;

	square3.remove(1);
	cout << "square3 removed1" << endl;
	cout << square3 << endl;

	square3.addOne(vector<char>(internal[3].begin(), internal[3].begin() + 3), internal[3][3], vector<char>(internal[3].rbegin(), internal[3].rbegin() + 3));
	cout << "square3 added more" << endl;
	cout << square3 << endl;
	return;
}