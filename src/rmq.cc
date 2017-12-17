#include <cstdio>
#include <vector>
#include "rmq.h"
using namespace std;


// RMQ constructor
// 1. Compute K - O(1)
// 2. Divide a data vector into a K size block - O(N)
// 3. Compute a sparse table for a block query - O(N)
// 4. Precompute hash functions (pre) - O(N)
RMQ::RMQ(vector<int> &_data) {
	data = _data;
	N = data.size();
	K = 0;

	// 1. Compute K - O(1)
	int temp = N;
	while (temp) {
		++K;
		temp>>=1;
	}

	// 2. Divide a data vector into a K size block - O(N)
	int minPos = -1, hashVal = 0;
	for (int i=0; i<data.size(); ++i) {
		if (minPos == -1 || data[i] < data[minPos])
			minPos = i;

		if (i%K != 0) {
			hashVal <<= 1;
			if (data[i-1] < data[i])
				hashVal |= 1;
		}

		if ((i+1)%K == 0) {
			block.push_back(minPos);
			hash.push_back(hashVal);
			minPos = -1;
			hashVal = 0;
		}
	}

	if (minPos != -1) {
		block.push_back(minPos);
		for (int i=data.size(); (i+1)%K != 0; ++i) {
			hashVal = ((hashVal<<1)|1);
		}
		hash.push_back(hashVal);
	}

	// 3. Compute a sparse table for a block query - O(N)
	st.push_back(block);
	for (int i=1; (1<<i)<=block.size(); ++i) {
		vector<int> line;
		for (int j=0; j+(1<<i)-1<block.size(); ++j) {
			int cur = st[i-1][j];
			int opp = st[i-1][j+(1<<(i-1))];
			
			line.push_back(data[cur] < data[opp] ? cur : opp);
		}
		st.push_back(line);
	}

	// 4. Precompute hash functions (pre) - O(N)
	for (int h=0; h<(1<<K); ++h) {
		vector<vector<int> > t;
		vector<int> ex;
		
		ex.push_back(0);
		for (int i=K-2; i>=0; --i) {
			int diff = (h&(1<<i)) ? 1 : -1;
			ex.push_back(ex.back() + diff);
		}

		for (int i=0; i<K; ++i) {
			vector<int> tt;
			int minPos = i;
			for (int j=0; j<K; ++j) {
				if (j < i) {
					tt.push_back(-1);
					continue;
				}

				if (ex[j] < ex[minPos])
					minPos = j;
				tt.push_back(minPos);
			}
			t.push_back(tt);
		}
		pre.push_back(t);
	} 
}


// Compute RMQ query - O(1)
int RMQ::query(int left, int right) {
	int b = left/K, bb = right/K;
	
	// Case 1. Same block query
	if (b == bb) {
		int ret = K*b + pre[hash[b]][left%K][right%K]; 
		return ret;
	}
	// Case 2. Different block query
	else {
		int ll = K*b + pre[hash[b]][left%K][K-1];
		int rr = K*bb + pre[hash[bb]][0][right%K];
		int ret = data[ll] < data[rr] ? ll : rr;

		// Now should query b+1 ~ bb-1 in sparse table
		if (b+1 <= bb-1) {
			int num = (bb-1) - (b+1) + 1;
			int sz = 0;
			while (1<<(sz+1) < num) {
				sz++;
			}
			
			int t = st[sz][b+1];
			int tt= st[sz][bb-(1<<sz)];
			int mid = data[t] < data[tt] ? t : tt;
			ret = data[ret] < data[mid] ? ret : mid;
		}
		return ret;
	}
}

// For debugging :)
void RMQ::print() {
	printf("N    : %d\n", N);
	printf("K : %d\n", K);
	for (int i=0; i<N; ++i)
		printf("%04d - %d", i, data[i]);
}
