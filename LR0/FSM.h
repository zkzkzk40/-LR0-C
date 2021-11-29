#pragma once
#include "GO.h"
#include "I.h"
#include <map>
#include <iomanip>
#include <fstream>
using namespace std;
class FSM
{
private:
	string nonTerminators;//非终结符集合EAB
	string terminators;//终结符集合abcd
	vector<production> productionVector;//原文法
	vector<production> augmentedGrammarProduction;//增广文法
	map<int, map<string, string>> mapACTION;
	map<int, map<string, string>> mapGOTO;
	vector<GO> vectorGO;
	vector<I> vectorI;
	void fill(int indexI);
	int findSameI(I i);
public:
	FSM(string str[], int strLen, string nonterminator, string Terminators);
	void show();//展示ACTION和GOTO
	void outPutToFile(string path);//输出到文本
	void buildFSM();//构建FSM
	void buildACTIONandGOTO();//构建ACTION和GOTO
};

