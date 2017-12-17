#include "node.h"

// Constructors for Node
Node::Node() : start(0), end(0), terminal(-1) {
	child.clear();
	par = NULL;
}

// Constructors for Node
Node::Node(Node* _par, int _start, int _end, int _terminal) : start(_start), end(_end), terminal(_terminal) {
	child.clear();
	par = _par;
}

// Insert suf(ori) into suffix tree - worst case O(N) each time
void Node::insert(string &str, int ori, int cur) {

	// Look through child nodes and find a node 
	// that strats with a same character
	for (auto it = child.begin(); it != child.end(); ++it) {
		Node* c = *it;
		int aa = c->start, bb = cur;
		if (str[aa] == str[bb]) {
			while (aa <= c->end && str[aa] == str[bb]) {
				++aa, ++bb;
			}

			// When you can go down to next child
			if (aa > c->end) {
				return c->insert(str, ori, bb);
			}
			// Split current node
			else {
				Node *mid = new Node(this, c->start, aa-1, -1);
				Node *fin = new Node(mid, bb, str.size()-1, ori);
				
				mid->child.push_back(c);
				mid->child.push_back(fin);

				c->start = aa;
				c->par = mid;
				
				this->child.erase(it);
				this->child.push_back(mid);
				return;
			}
		}
	}


	// When you can't find a existing node,
	// make a new one
	Node *fin = new Node(this, cur, str.size()-1, ori);

	this->child.push_back(fin);
}

// Do a dfs that starts from this node - O(N)
void Node::dfs(string &str, int tab, vector<Node*> &E, vector<int> &L) {
	// If it is not a root node than print string
	if (par != NULL)
		cout << string(tab*2, ' ') << str.substr(start, end-start+1) << endl;

	// Fill out E ans L tables
	E.push_back(this);
	L.push_back(tab);

	// DFS to next strings
	for (auto next : child) {
		next->dfs(str, tab+1, E, L);
		E.push_back(this);
		L.push_back(tab);
	}
}



