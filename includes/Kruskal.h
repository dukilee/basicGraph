#include <bits/stdc++.h>

using namespace std;

class Kruskal{
	
public:
	static double run(map<string, vector<pair<string, double> > >& graph, string start, string finish){


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
				if(dist.find(it->first)==dist.end() || dist[it->first]>z + it->second){
					dist[it->first] = z + it->second;
					pq.push(make_pair(dist[it->first], it->first));
				}
			}

		}
		if(dist.find(finish)==dist.end()) return -1;//not connected
		return dist[finish];
	}
private:
	Dijikstra(){};


}