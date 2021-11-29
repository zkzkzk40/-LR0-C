#include "FSM.h"
#include <iostream>
using namespace std;
int main()
{
	string G[] = {
		"E->aA",
		"E->bB",
		"A->cA",
		"A->d",
		"B->cB",
		"B->d"
	};
	string EAB ="EAB";//非终结符集合
	string abcd ="abcd#";//终结符集合
	FSM fsm(G, sizeof(G) / sizeof(string), EAB, abcd);
	fsm.buildFSM();
	fsm.buildACTIONandGOTO();
	fsm.show();
}


