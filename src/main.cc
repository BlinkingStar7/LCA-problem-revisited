#include <cstdio>
#include <map>
#include <algorithm>
#include "rmq.h"
#include "sftree.h"

int main(int argc, char *argv []) {
	if (argc != 2) {
		printf("[ERROR] argument count must be exactly one\n");
		return 1;
	}

	// Building a suffix tree with given string - O(N^2)
	printf("\n[Step 1] Building a suffix tree with %s\n", argv[1]);
	string temp(argv[1]);
	SFtree sftree(temp);
	
	// Do a DFS on a suffix tree and fill out E and L arrays - O(N)
	printf("\n[Step 2] DFS a suffix tree and save info\n");
	vector<Node*> E;
	vector<int> L;
	sftree.dfs(E, L);

	// Build a Sparse table and a hash table for O(1) LCA algorithm - O(N) 
	printf("\n[Step 3] Build sparse table and preprocessing hash table\n");
	RMQ rmq(L);
	map<int, int> m;

	for (int i=0; i<E.size(); ++i)
		if (E[i]->terminal != -1) 
			m[E[i]->terminal] = i;

	// Inside a while loop, prcoess queries
	while (1) {
		int q, qq;
		printf("Query suffix? (-1 -1 to quit) : \n");
		scanf("%d %d", &q, &qq);
		if (q == -1) break;

		int ret = rmq.query(min(m[q], m[qq]), max(m[q], m[qq]));
		printf("Query 1 : %s\n", argv[1] + q); 
		printf("Query 2 : %s\n", argv[1] + qq); 
		printf("Ans     : ");

		string ans;
		Node *cur = E[ret];
		while (cur->par) {
			ans = temp.substr(cur->start, cur->end - cur->start + 1) + ans;
			cur = cur->par;
		}

		cout << ans << endl;
	}

	return 0;
}
