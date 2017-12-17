#ifndef SFTREE_H
#define SFTREE_H

#include <string>
#include "node.h"
using namespace std;

struct SFtree {
	Node* root;
	string str;

	SFtree(string &_str);

	void dfs(vector<Node*> &E, vector<int> &L);
};

#endif
