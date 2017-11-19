#include <bits/stdc++.h>

using namespace std;

enum{
	IS_EDGE,
	IS_FUNCTION,
	IS_NOTHING,
	IS_WHITELINE
};


struct Line{
	string orig, dest;
	char op;
	int val;
};

double stringToDouble(string s){
	double val = 0;
	int pos = 0;
	while(pos<s.length() && s[pos]!='.'){
		val = 10*val + s[pos] - 48;
		pos++;
	}
	if(s[pos]=='.'){
		double decimal = 0;
		double pot = 0.1;
		pos++;
		while(pos<s.length()){
			decimal = decimal + pot*(s[pos] - 48);
			pot/=10;
			pos++;
		}
		val = val + decimal;
	}
	return val;
}

bool DFS(map<string, vector<pair<string, double> > >& graph, map<string, bool>& flag, string curr, string finish){
	if(curr == finish) return true;
	if(flag[curr]) return false;
	flag[curr] = true;
	for(vector<pair<string, double> >::iterator it = graph[curr].begin(); it!=graph[curr].end(); it++){
		if(DFS(graph, flag, it->first, finish)) return true;
	}
	return false;
}

bool DFS(map<string, vector<pair<string, double> > >& graph, string start, string finish){
	map<string, bool> flag;
	return DFS(graph, flag, start, finish);
}

double dijikstra(map<string, vector<pair<string, double> > >& graph, string start, string finish){


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



int decideLineType(string currLine){
	int openCount = 0;
	bool thereIsBracket = false;
	bool edgeDefinition = false;
	//check if is an empty line

	bool isEmptyLine = true;
	for(int i = 0; i<currLine.size(); i++){
		if(currLine[i]!=' ' && currLine[i]!='\n' && currLine[i]!='\t'){
			isEmptyLine = false;
		}
	}
	if(isEmptyLine)
		return IS_WHITELINE;


	for(int i = 0; i<currLine.size(); i++){
		if(currLine[i]=='('){
			thereIsBracket = true;
			openCount++;
		}else if(currLine[i]==')'){
			openCount--;
			if(openCount<0){
				std::cout<<"There are too many close brackets"<<std::endl;
				return IS_NOTHING;
			}
		}else if(currLine[i]=='-'){
			if(thereIsBracket){
				std::cout<<"There is a bracket edge definition, something is strange\n";
				return IS_NOTHING;
			}

			i++;
			if(i<currLine.size() && currLine[i]=='>'){
				edgeDefinition = true;
			}else{
				std::cout<<"Error in edge definition\n";
				return IS_NOTHING;
			}
		}else if(!isalnum(currLine[i]) && currLine[i]!=' ' &&
					currLine[i]!='\n' && currLine[i]!='\t' && currLine[i]!='.'){
			if(currLine[i]==','){
				if(openCount==0){
					cout<<"There is \',\' outside function call\n";
					return IS_NOTHING;
				}
			}else{
				std::cout<<"There is a non-alfaNumeric character \'"<<currLine[i]<<"\'"<<std::endl;
				return IS_NOTHING;
			}
		}
	}
	if(openCount>0){
		std::cout<<"There are too few bracket closers\n";
		return IS_NOTHING;
	}
	if(edgeDefinition){
		if(thereIsBracket){
			cout<<"There are brackets and edge definition\n";
			return IS_NOTHING;
		}else{
			return IS_EDGE;
		}
	}
	if(thereIsBracket)
		return IS_FUNCTION;

	return IS_EDGE;

}

bool addEdge(string currLine, std::map<std::string, std::vector<std::pair<std::string, double> > >& graph){
	string start, finish, weight;
	int pos = 0;

	//start
	while(currLine[pos]==' ' || currLine[pos]=='\t') pos++;
	while(isalnum(currLine[pos])) start.push_back(currLine[pos++]);
	while(currLine[pos]==' ' || currLine[pos]=='\t') pos++;
	//check semantic
	if(currLine[pos]!='-' && !isalnum(currLine[pos]) ){
		cout<<"Error in edge definition, character missplaced \'"<<currLine[pos]<<"\'\n";
		return false;//error
	}
	if(currLine[pos]=='-') pos+=2;//skipping ->
	while(currLine[pos]==' ' || currLine[pos]=='\t') pos++;
	

	//finish
	while(isalnum(currLine[pos])) finish.push_back(currLine[pos++]);
	while(currLine[pos]==' ' || currLine[pos]=='\t') pos++;

	//check semantic
	if(!isdigit(currLine[pos]) && currLine[pos]!='\n' && currLine[pos]!='\0'){
		cout<<"Error in edge definition, character missplaced \'"<<currLine[pos]<<"\'\n";
		return false;//error
	}
	//weight
	if(currLine[pos]=='\n' || currLine[pos]=='\0') weight="1";
	else{
		while(isalnum(currLine[pos]) || currLine[pos]=='.') weight.push_back(currLine[pos++]);
		while(currLine[pos]==' ' || currLine[pos]=='\t') pos++;
	}
	//check semantic
	if(currLine[pos]!='\n' && currLine[pos]!='\0'){
		cout<<"Error in edge definition, too many parameters\n";
		return false;//error
	}

	double weightVal = stringToDouble(weight);

	graph[start].push_back(make_pair(finish, weightVal));
	return true;

}
bool resolveFunction(string currLine, std::map<std::string, std::vector<std::pair<std::string, double> > >& graph){
	string functionName;
	vector<string> params;
	int pos = 0;

	while(currLine[pos]==' ' || currLine[pos]=='\t') pos++;
	while(currLine[pos]!='('){
		functionName.push_back(currLine[pos]);
		pos++;
	}

	pos++;
	while(currLine[pos]!=')'){
		string aux = "";
		while(currLine[pos]==' ' || currLine[pos]=='\t') pos++;
		while(currLine[pos]!=',' && currLine[pos]!=')'){
			aux += currLine[pos];
			pos++;
		}
		while(currLine[pos]==' ' || currLine[pos]=='\t') pos++;
		if(currLine[pos]!=')')
			pos++;
		params.push_back(aux);
	}
	if(functionName=="isConnected"){
		if(params.size()!=2){
			cout<<"Check params for DFS call\n";
			return false;
		}
		if(DFS(graph, params[0], params[1])){
			cout<<"\'"<<params[0]<<"\' and \'"<<params[1]<<"\' are conenected\n";
		}else{
			cout<<"\'"<<params[0]<<"\' and \'"<<params[1]<<"\' are NOT conenected\n";
		}
	}else if(functionName=="distance"){
		if(params.size()!=2){
			cout<<"Check params for distance call\n";
			return false;	
		}
		double dist = dijikstra(graph, params[0], params[1]);
		cout<<"Distance \'"<<params[0]<<"\' and \'"<<params[1]<<"\' equals to "<<dist<<"\n";		
	}else{
		cout<<"Unknown function\n";
		return false;
	}
	return true;
}


int main(){
	std::map<std::string, std::vector<std::pair<std::string, double> > > graph;

	string currLine;
	int lineCount = 0;
	while(getline(cin, currLine)){
		lineCount++;
		int lineType = decideLineType(currLine);
		
		if(lineType == IS_NOTHING){
			cout<<"Line "<<currLine<<": \'"<<currLine<<"\'\n";
		}else if(lineType==IS_EDGE){
			if(!addEdge(currLine, graph)){
				cout<<lineCount<<": \'"<<currLine<<"\'\n";
			}
		}else if(lineType==IS_FUNCTION){
			if(!resolveFunction(currLine, graph)){
				cout<<lineCount<<": \'"<<currLine<<"\'\n";				
			}
		}
	}
}