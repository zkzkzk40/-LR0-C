#include "FSM.h"
#include <iostream>
using namespace std;
int main()
{
	string G[] = {
		"S->E",
		"E->aA",
		"E->bB",
		"A->cA",
		"A->d",
		"B->cB",
		"B->d"
	};
	string EAB ="SEAB";//非终结符集合
	string abcd ="abcd#";//终结符集合
	FSM fsm(G, sizeof(G) / sizeof(string), EAB, abcd);
	fsm.buildFSM();
	fsm.buildACTIONandGOTO();
	fsm.show();
	fsm.outPutToFile("output.txt");
}


