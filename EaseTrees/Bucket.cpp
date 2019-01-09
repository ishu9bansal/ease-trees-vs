#include <iostream>
#include <ctime>
#include "Bucket.h"

using namespace std;

struct B {
	int min;
	int max;
	int ans;
	bool isValid;
	B(int x) : min(x), max(x), ans(x), isValid(true) {}
	B() : min(0), max(0), ans(0), isValid(false) {}
	operator bool() {
		return isValid;
	}
};

struct createBucket {
	B operator() (int i, int j,const vector<int> &v){
		if (j > v.size())	j = v.size();
		if (i >= j || i < 0)	return B();
		B b(v[i]);
		if (i)	b.ans -= v[i - 1];
		int k = i + 1;
		while (k < j){
			if (v[k] - b.min > b.ans)	b.ans = v[k] - b.min;
			if (v[k] > b.max)	b.max = v[k];
			if (v[k] < b.min)	b.min = v[k];
			k++;
		}
		return b;
	}
};

struct bucketAnswer {
	int operator()(B b) {
		return b.ans;
	}
};

struct merge {
	B operator()(B a, B b) {
		if (!a)	return b;
		if (!b)	return a;
		if (b.max - a.min > a.ans)	a.ans = b.max - a.min;
		if (b.max > a.max)	a.max = b.max;
		if (b.min < a.min)	a.min = b.min;
		if (b.ans > a.ans)	a.ans = b.ans;
		return a;
	}
};



void aggressiveTest(unsigned int t) {
	srand(t);
	cout << "Seed: " << t << endl;
	int n, x, y, q;
	vector<int> v(1, 0);
	// n = rand()%50000;
	n = 500;
	while (n--) {
		x = (rand() % 2 ? 1 : -1)*(rand() % 15007);
		// if(x>0)	x = -1*x;
		x += v.back();
		v.push_back(x);
	}

	Bucket<int,B,int,createBucket,bucketAnswer,merge> bucket(v);
	createBucket referenceFunction;

	n = v.size();
	// cout<<"Size "<<n<<endl<<endl;
	for (int i = 0; i<n; i++) {
		x = i + 1;
		// if(!(x%100))	cout<<"x = "<<x<<endl;
		for (int j = i; j<n; j++) {
			y = j + 1;
			if (bucket(x, y) != referenceFunction(x, y, v).ans) {
				cout << "Error for " << x << '\t' << y << "\tseed: " << t << endl;
			}
		}
	}
	cout << endl;
}

void test(int q) {
	unsigned int t = time(NULL);
	srand(t);
	cout << "Seed: " << t << endl;
	int n, x, y;
	vector<int> v(1, 0);
	n = rand()%50000;
	// n = 1000;
	while (n--) {
		x = (rand() % 2 ? 1 : -1)*(rand() % 15007);
		// if(x>0)	x = -1*x;
		x += v.back();
		v.push_back(x);
	}
	n = v.size();
	Bucket<int, B, int, createBucket, bucketAnswer, merge> bucket(v);
	createBucket referenceFunction;

	while (q--) {
		x = rand() % n;
		y = rand() % n;
		if (x>y)	swap(x, y);
		// x = 0;
		// y = n-1;
		if (bucket(x, y) != referenceFunction(x, y, v).ans) {
			cout << q << " Error for " << x << '\t' << y << "\tseed: " << t << endl;
		}
	}
}

void testBucket(){
	/*int n = 10;
	while (n--)	test(100);
	n = 1;
	while (n--)	aggressiveTest(time(NULL));*/
	int n = 100;
	vector<int> v;
	while (n--) {
		v.push_back(rand() % 5000000);
	}

	Bucket<int> bucket(v);
	
	cout << endl;
	cout << "Bucket 3 is " << bucket(3) << endl;
	n = v.size();
	cout << "Range queries:" << endl;
	int x, y;
	for (int i = 0; i < 10; i++) {
		x = rand() % n;
		y = rand() % n;
		if (x > y)	swap(x, y);
		cout << x << ' ' << y << '\t' << bucket(x, y) << endl;
	}
	vector<int> buckets = bucket();
	for (int i = 0; i < buckets.size(); i++) {
		cout << buckets[i] << '\t';
	}
}
