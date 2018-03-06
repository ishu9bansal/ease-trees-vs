#ifndef square_vector_h
#define square_vector_h

#include <vector>
#include <iostream>
// #include "SizeException.h"

using namespace std;

template <class T>
class vectorSquare {
	vector<vector<T> > data;
public:
	vectorSquare() {
	}
	vectorSquare(int n) {
		for (int i = 0; i<n; i++)	data.push_back(vector<T>(2 * i + 1));
	}
	vectorSquare(const vector<vector<T> >& idata) {
		int n = idata.size();
		//for (int i = 0; i<n; i++)
			//if (idata[i].size() != n)
				//throw new SizeNotMatchException("Data is not square.");
		for (int i = 0; i<n; i++) {
			vector<T> temp;
			for (int j = 0; j<2 * i + 1; j++) {
				if (i<j)	temp.push_back(idata[2 * i - j][i]);
				else	temp.push_back(idata[i][j]);
			}
			data.push_back(temp);
		}
	}
	vector<vector<T> > getInternalStructure() const {
		//	It gives the raw structure being used to store the data
		return data;
	}
	int size() const {
		return data.size();
	}
	vector<vector<T> > getData() const {
		// gives the data in plain 2d vector format
		int n = data.size();
		vector<vector<T> > converted(n, vector<T>(n));
		for (int i = 0; i<n; i++) {
			for (int j = 0; j <= i; j++) {	// when writing j<i uncomment the following for loop
				converted[i][j] = data[i][j];
				converted[j][i] = data[i][2 * i - j];
			}
		}
		//	for(int i=0; i<n; i++)	converted[i][i] = data[i][i];
		return converted;
	}
	void clear() {
		for (int i = 0; i<data.size(); i++)	data[i].clear();
		data.clear();
	}
	vectorSquare& addOne() {
		data.push_back(vector<T>(2 * data.size() + 1));
		return *this;
	}
	vectorSquare& addOne(vector<T> line) {
		int n = data.size();
		//if (line.size() != 2 * n + 1)
			//throw new SizeNotMatchException("Data length should match existing data i.e. " + (2 * n + 1));
		data.push_back(line);
		return *this;
	}
	vectorSquare& addOne(vector<T> newToOld, const T& newToNew, const vector<T>& oldToNew) {
		int n = data.size();
		//if (newToOld.size() != n || oldToNew.size() != n)
			//throw new SizeNotMatchException("Data length should match existing data i.e. " + n);
		newToOld.push_back(newToNew);
		newToOld.insert(newToOld.end(), oldToNew.rbegin(), oldToNew.rend());
		data.push_back(newToOld);
		return *this;
	}
	vectorSquare& remove(int t) {
		vectorSquare& vs = *this;
		int n = vs.size();
		for (int i = 0; i<n; i++) {
			vs(t, i) = vs(n - 1, i);
			vs(i, t) = vs(i, n - 1);
		}
		vs(t, t) = vs(n - 1, n - 1);
		data.pop_back();
		return vs;
	}
	T& operator()(int r, int c) {
		if (r<c)	return data[c][2 * c - r];
		else	return data[r][c];
	}
	T get(int r, int c) const {
		if (r<c)	return data[c][2 * c - r];
		else	return data[r][c];
	}

};

template <class T>
ostream& operator<<(ostream& out, const vectorSquare<T>& vs) {
	for (int i = 0; i<vs.size(); i++) {
		for (int j = 0; j<vs.size(); j++) {
			if (j)	out << '\t';
			out << vs.get(i, j);
		}
		out << endl;
	}
	out << endl;
	return out;
}

void testSquareVector();

#endif // !square_vector_h