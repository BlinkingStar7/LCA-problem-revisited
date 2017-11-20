#include <cstdio>
#include <vector>
#include "rmq.h"
using namespace std;

rmq::rmq() : N(0), logN(0) {
	data.clear();
}

rmq::rmq(vector<int> &_data) {
	data = _data;
	N = data.size();
	logN = 0;

	int t = N;
	while (t) {
		++logN;
		t>>=1;
	}
}

int rmq::query(int left, int right) {
	return 0;
}

int rmq::size() {
	return N;
}

void rmq::print() {
	for (int i=0; i<N; ++i)
		printf("%04d - %d", i, data[i]);
}
