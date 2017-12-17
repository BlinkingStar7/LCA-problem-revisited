#include "sftree.h"

// Constructor for suffix tree
SFtree::SFtree(string &_str) {
	str = _str;
	root = new Node(NULL, -1, -1, -1); 

	// Insert suffix to root node - O(N^2)
	for (int i=0; i<str.size(); ++i)
		root->insert(str, i, i);
}

// Initiate dfs from root node - O(N)
void SFtree::dfs(vector<Node*> &E, vector<int> &L) {
	root->dfs(str, 0, E, L);
}
