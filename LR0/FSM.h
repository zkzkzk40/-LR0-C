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
	string nonTerminators;//���ս������EAB
	string terminators;//�ս������abcd
	vector<production> productionVector;//ԭ�ķ�
	vector<production> augmentedGrammarProduction;//�����ķ�
	map<int, map<string, string>> mapACTION;
	map<int, map<string, string>> mapGOTO;
	vector<GO> vectorGO;
	vector<I> vectorI;
	void fill(int indexI);
	int findSameI(I i);
public:
	FSM(string str[], int strLen, string nonterminator, string Terminators);
	void show();//չʾACTION��GOTO
	void outPutToFile(string path);//������ı�
	void buildFSM();//����FSM
	void buildACTIONandGOTO();//����ACTION��GOTO
};

