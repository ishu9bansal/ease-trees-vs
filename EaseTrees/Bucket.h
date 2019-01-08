#ifndef bucket_h
#define bucket_h


#include <vector>
#include <cmath>
using namespace std;


template <class T, class B, class R,class rangeToBucket, class bucketToResult, class combineBuckets, unsigned int bucket_size = 0>
class Bucket {
private:
	// size of a single block
	// sqrt(n) if not defined
	// n: total size of values
	int block;
	B nullBucket;

	vector<T> valueList;
	vector<B> bucketList;

	// should take care of array out of bound
	// arguments: start_index, end_index, vector_of_values
	rangeToBucket makeBucket;
	// arguments: bucket
	bucketToResult getResult;
	// should take care of null pointer
	// arguments: first_bucket, second_bucket
	combineBuckets mergeBuckets;

	B getBucket(int i, int j) {
		if (i >= j)	return nullBucket;
		int l = i / block;
		int r = (j - 1) / block;
		if (i%block == 0 && j == i + block && l < bucketList.size()) {
			if(bucketList[l])	return bucketList[l];
			else return bucketList[l] = makeBucket(i, j, valueList);
		}
		if (l == r)	return makeBucket(i, j, valueList);
		l++;
		B b = getBucket(i, l*block);
		for (int k = l; k < r; k++) {
			b = mergeBuckets(b, getBucket(k));
		}
		b = mergeBuckets(b, getBucket(r*block, j));
		return b;
	}
	B getBucket(int i) {
		return getBucket(i*block, (i + 1)*block);
	}
	void updateBucketList() {
		int n = valueList.size();
		block = bucket_size;
		if (!block)	block = sqrt(n);
		n = ((n - 1) / block) + 1;
		bucketList.assign(n, nullBucket);
		// removed this for optimization
		// preprocessing is not required
		// can be produced on demand, used memoization
		/*for (int i = 0; i < n; i++) {
			bucketList[i] = getBucket(i);
		}*/
	}
public:
	Bucket(vector<T> v){
		nullBucket = makeBucket(-1, -1, v);
		assign(v);
	}
	void assign(vector<T> v) {
		valueList = v;
		updateBucketList();
	}
	R operator()(int i, int j) {
		return getResult(getBucket(i,j));
	}
	B operator()(int i) {
		return getBucket(i);
	}
	vector<B> operator()() {
		return bucketList;
	}
};

void testBucket();

#endif
