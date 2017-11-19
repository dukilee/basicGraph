#include <bits/stdc++.h>

using namespace std;

class Prim{
	
public:
	static double run(map<string, vector<pair<string, double> > >& graph){
		string start = graph.begin()->first;
		double sum = 0;
		priority_queue<pair<double, string>, 
						vector< pair<double, string> >,
						greater< pair<double, string> > > pq;

		map<string, double> dist;

		dist[start] = 0;
		pq.push(make_pair(0, start));
		while(!pq.empty()){
			double z = pq.top().first;
			string x = pq.top().second;
			pq.pop();
			if(dist[x]!=z){
				continue;
			}

			for(vector<pair<string, double> >::iterator it = graph[x].begin(); it!=graph[x].end(); it++){
				if(it->first==start) continue;
				if(dist.find(it->first)==dist.end() || dist[it->first]>it->second){
					sum = sum - dist[it->first] + it->second;
					dist[it->first] = it->second;
					pq.push(make_pair(dist[it->first], it->first));
				}
			}

		}
		return sum;
	}
private:
	Prim(){};


};