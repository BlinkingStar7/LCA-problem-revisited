#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node {
	int start, end;
	int terminal;
	
	vector<Node*> child;
	Node* par;

	Node();
	Node(Node* _par, int _start, int _end, int _terminal);

	void insert(string &str, int ori, int cur);
	void dfs(string &str, int tab, vector<Node*> &E, vector<int> &L);
};

#endif

