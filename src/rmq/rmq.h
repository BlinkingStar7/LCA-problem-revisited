#ifndef RMQ_H
#define RMQ_H

#include <vector>
using namespace std;

struct rmq {
	vector<int> data;
	int N, logN;
	
	rmq();
	rmq(vector<int> &);

	int query(int, int);
	int size();
	void print();
	
};

#endif 

