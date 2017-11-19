#include <bits/stdc++.h>

using namespace std;

#ifndef DFS_H
#define DFS_H

class DFS{

private:		
	static bool run(map<string, vector<pair<string, double> > >& graph, map<string, bool>& flag, string curr, string finish){
		if(curr == finish) return true;
		if(flag[curr]) return false;
		flag[curr] = true;
		for(vector<pair<string, double> >::iterator it = graph[curr].begin(); it!=graph[curr].end(); it++){
			if(run(graph, flag, it->first, finish)) return true;
		}
		return false;
	}
public:
	static bool run(map<string, vector<pair<string, double> > >& graph, string start, string finish){
		map<string, bool> flag;
		return run(graph, flag, start, finish);
	}
	DFS(){};

};

#endif //DFS_H