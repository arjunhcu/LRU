#include <bits/stdc++.h>

using namespace std;

#define itrtr set<page *, compare>::iterator

//Assumtion: LRU key and data as same.

//page: it will have data (key) and the ref count
struct page {
	int data;
	int cnt;
	
	page(int val, int cont):data(val), cnt(cont){}
};


//sort set using ref count
struct compare{
	bool operator()(page *p1, page *p2) {
		return p1->cnt < p2->cnt;
	}
};

static int mcount = 0;
static int capacity = 3;

struct LRU {
	
	//Cache
	unordered_map<int, page*> m;
	
	//Keep track of pages in Cache as ref count
	set<page*, compare> st;
	
	//insert data
	//1. if exisitng page - update the ref count
	//2. if new page -
		//a. if Cache full - remove the first from Cache and set
		//b. if Cache is not full - insert into Cache
	void insert(int data) {
		
		mcount++;
		if(m.find(data) != m.end()) {
			
			cout<<"Existing page requested...\n";

			page *p = m[data];
			st.erase(p);
			p->cnt = mcount;
			st.insert(p);
		} else {
			
			cout<<"New page requested...\n";
			
			if(m.size() >= capacity) {
				
				cout<<"Cache full. Removing LRU..\n";
				
				itrtr it = st.begin();
				page *p = *it;
				st.erase(p);
				m.erase(p->data);
				delete p;
			}
			
			cout<<"Inserting page in Cache...\n";
			
			page *p = new page(data, mcount);
			st.insert(p);
			m[p->data] = p;
		}
	}
	
	//If availbale - update ref count
	//insert otherwise
	int get(int data) {
		insert(data);
		return m[data]->data;
	}
};


int main() {
	
	vector<int> d = {1,2,3,4,1,1,2,3};
	LRU lru;
	for(int i = 0; i < d.size(); i++) {
		cout<<lru.get(d[i])<<"\n";
	}
	
	return 0;
}
