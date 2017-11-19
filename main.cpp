#include <bits/stdc++.h>
#include "includes/DFS.h"
#include "includes/Dijikstra.h"
#include "includes/LineType.h"
#include "includes/Prim.h"

using namespace std;

bool bidirect = false;

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
	if(bidirect){
		graph[finish].push_back(make_pair(start, weightVal));
		cout<<"New edge: "<<start<<" -> "<<finish<<" (weight "<<weightVal<<") BID\n";	
	}else{
		cout<<"New edge: "<<start<<" -> "<<finish<<" (weight "<<weightVal<<") UNI\n";
	}
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
		if(DFS::run(graph, params[0], params[1])){
			cout<<"\'"<<params[0]<<"\' and \'"<<params[1]<<"\' are conenected\n";
		}else{
			cout<<"\'"<<params[0]<<"\' and \'"<<params[1]<<"\' are NOT conenected\n";
		}
	}else if(functionName=="distance"){
		if(params.size()!=2){
			cout<<"Check params for distance call\n";
			return false;	
		}
		double dist = Dijikstra::run(graph, params[0], params[1]);
		cout<<"Distance \'"<<params[0]<<"\' and \'"<<params[1]<<"\' equals to "<<dist<<"\n";		
	}else if(functionName == "mst"){
		if(params.size()!=0){
			cout<<"Check params for mst call\n";
			return false;	
		}
		if(!bidirect){
			cout<<"WARNING, the graph is unidirect\n";
		}
		double dist = Prim::run(graph);
		cout<<"The cost of the Minimum Spanning Tree equals to "<<dist<<"\n";		
	
	}else if(functionName == "setBidirect"){
		if(params.size()!=0){
			cout<<"Check params for setBidirect call\n";
			return false;	
		}
		bidirect = true;
		cout<<"Considering bidirect\n";
	}else if(functionName == "setUnidirect"){
		if(params.size()!=0){
			cout<<"Check params for setUnidirect call\n";
			return false;	
		}
		bidirect = false;
		cout<<"Considering unidirect\n";

	}else{
		cout<<"Unknown function\n";
		return false;
	}
	return true;
}


int main(){
	bidirect =false;
	std::map<std::string, std::vector<std::pair<std::string, double> > > graph;

	string currLine;
	int lineCount = 1;
	cout<<lineCount<<"> ";
	while(getline(cin, currLine)){
		LineTypeId lineType = LineType::decideLineType(currLine);
		
		if(lineType == LineTypeId::IS_NOTHING){
			cout<<"Line "<<currLine<<": \'"<<currLine<<"\'\n";
		}else if(lineType==LineTypeId::IS_EDGE){
			if(!addEdge(currLine, graph)){
				cout<<lineCount<<": \'"<<currLine<<"\'\n";
			}else
				lineCount++;
		}else if(lineType==LineTypeId::IS_FUNCTION){
			if(!resolveFunction(currLine, graph)){
				cout<<lineCount<<": \'"<<currLine<<"\'\n";				
			}else
				lineCount++;
		}
		cout<<lineCount<<"> ";
	}
	cout<<endl;
}