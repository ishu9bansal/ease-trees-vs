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
		int k = i + 1;
		while (k < j){
			if (v[k] > b.max)	b.max = v[k];
			if (b.max - b.min > b.ans)	b.ans = b.max - b.min;
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
		if (b.max > a.max)	a.max = b.max;
		if (a.max - a.min > a.ans)	a.ans = a.max - a.min;
		if (b.min < a.min)	a.min = b.min;
		if (b.ans > a.ans)	a.ans = b.ans;
		return a;
	}
};

int refrenceAns(int i, int j, vector<int> &v) {
	int min, ans;
	min = ans = v[i];
	if(i)	ans -= v[i - 1];
	int k = i + 1;
	while (k < j) {
		if (v[k] - min>ans)	ans = v[k] - min;
		if (v[k]<min)	min = v[k];
		k++;
	}
	return ans;
}

void aggressiveTest(unsigned int t) {
	srand(t);
	cout << "Seed: " << t << endl;
	int n, x, y, q;
	vector<int> v(1, 0);
	// n = rand()%50000;
	n = 1000;
	while (n--) {
		x = (rand() % 2 ? 1 : -1)*(rand() % 15007);
		// if(x>0)	x = -1*x;
		x += v.back();
		v.push_back(x);
	}

	Bucket<int,B,int,createBucket,bucketAnswer,merge> bucket(v);

	n = v.size();
	// cout<<"Size "<<n<<endl<<endl;
	for (int i = 0; i<n; i++) {
		x = i + 1;
		// if(!(x%100))	cout<<"x = "<<x<<endl;
		for (int j = i; j<n; j++) {
			y = j + 1;
			if (bucket(x, y) != refrenceAns(x, y, v)) {
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
	//	n = 1000;
	while (n--) {
		x = (rand() % 2 ? 1 : -1)*(rand() % 15007);
		// if(x>0)	x = -1*x;
		x += v.back();
		v.push_back(x);
	}

	Bucket<int, B, int, createBucket, bucketAnswer, merge> bucket(v);

	n = v.size();
	while (q--) {
		x = rand() % n;
		y = rand() % n;
		if (x>y)	swap(x, y);
		// x = 0;
		// y = n-1;
		if (bucket(x, y) != refrenceAns(x, y, v)) {
			cout << "Error for " << x << '\t' << y << "\tseed: " << t << endl;
		}
	}
}

void testBucket(){
	int n = 10;
	while (n--) {
		test(100);
	}
}
