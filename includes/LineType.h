#include <bits/stdc++.h>

using namespace std;

#ifndef LINETYPE_H
#define LINETYPE_H

enum class LineTypeId{
	IS_EDGE,
	IS_FUNCTION,
	IS_NOTHING,
	IS_WHITELINE
};

class LineType{
public:
	static LineTypeId decideLineType(string currLine){
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
			return LineTypeId::IS_WHITELINE;


		for(int i = 0; i<currLine.size(); i++){
			if(currLine[i]=='('){
				thereIsBracket = true;
				openCount++;
			}else if(currLine[i]==')'){
				openCount--;
				if(openCount<0){
					std::cout<<"There are too many close brackets"<<std::endl;
					return LineTypeId::IS_NOTHING;
				}
			}else if(currLine[i]=='-'){
				if(thereIsBracket){
					std::cout<<"There is a bracket edge definition, something is strange\n";
					return LineTypeId::IS_NOTHING;
				}

				i++;
				if(i<currLine.size() && currLine[i]=='>'){
					edgeDefinition = true;
				}else{
					std::cout<<"Error in edge definition\n";
					return LineTypeId::IS_NOTHING;
				}
			}else if(!isalnum(currLine[i]) && currLine[i]!=' ' &&
						currLine[i]!='\n' && currLine[i]!='\t' && currLine[i]!='.'){
				if(currLine[i]==','){
					if(openCount==0){
						cout<<"There is \',\' outside function call\n";
						return LineTypeId::IS_NOTHING;
					}
				}else{
					std::cout<<"There is a non-alfaNumeric character \'"<<currLine[i]<<"\'"<<std::endl;
					return LineTypeId::IS_NOTHING;
				}
			}
		}
		if(openCount>0){
			std::cout<<"There are too few bracket closers\n";
			return LineTypeId::IS_NOTHING;
		}
		if(edgeDefinition){
			if(thereIsBracket){
				cout<<"There are brackets and edge definition\n";
				return LineTypeId::IS_NOTHING;
			}else{
				return LineTypeId::IS_EDGE;
			}
		}
		if(thereIsBracket)
			return LineTypeId::IS_FUNCTION;

		return LineTypeId::IS_EDGE;

	}

};

#endif //LINETYPE_H