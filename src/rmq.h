#ifndef RMQ_H
#define RMQ_H

#include <vector>
using namespace std;


struct RMQ {
	vector<int> data, block, hash;
	vector<vector<int> > st;
	vector<vector<vector<int> > > pre;
	int N, K;
	
	RMQ(vector<int> &_data);

	int query(int left, int right);
	void print();
	
};

#endif 

