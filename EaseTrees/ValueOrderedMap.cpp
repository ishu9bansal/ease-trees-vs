#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

template <class T, class Compare >
class ref_compare{
private:
	static Compare compare;
public:
  bool operator() (const T* lhs, const T* rhs) const
  {return compare(*lhs,*rhs);}
};

template<class V, class K, class Compare = less<pair<V,K> > >
class value_ordered_map{
	typedef pair<V,K> pair_type;
	private:
		set<pair_type*, ref_compare<pair_type,Compare> > ordered_set;
		unordered_map<K,pair_type*> h;
	public:
		void erase(const K &key){
			if(h.find(key)!=h.end()){
				ordered_set.erase(h[key]);
				delete h[key];
				h.erase(key);
			}
		}
		void insert(const K &key,const V &value){
			erase(key);
			pair_type* pt = new pair_type(value,key);
			h[key] = pt;
			ordered_set.insert(pt);
		}
		V get(const K &key){
			return h[key]->first;
		}
		pair_type getFirst(){
			return *ordered_set.begin();
		}
		pair_type getLast(){
			return *ordered_set.rbegin();
		}
		void clear(){
			for(pair_type *pt: ordered_set){
				delete pt;
			}
			ordered_set.clear();
			h.clear();
		}
		void status_print(){
			for(pair_type* pt: ordered_set){
				cout<<pt<<'\t'<<pt->first<<'\t'<<pt->second<<'\t'<<h[pt->second]<<endl;
			}
			cout<<endl;
		}
};

int main(){
	value_ordered_map<int, string> vom;
	vom.insert("ishu", 5);
	vom.status_print();
	vom.insert("sarkar", 3);
	vom.status_print();
	vom.insert("prabhu", 4);
	vom.status_print();
	vom.insert("dev",7);
	vom.status_print();
	vom.insert("patil",6);
	vom.status_print();
	vom.insert("sarkar",5);
	vom.status_print();
	
	return 0;
}
