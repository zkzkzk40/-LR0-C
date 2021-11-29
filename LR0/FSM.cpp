#include "FSM.h"

void FSM::fill(int indexI)
{
	vectorI[indexI].fill(nonTerminators, productionVector);
}

int FSM::findSameI(I i)
{
	for (int j = 0; j < vectorI.size(); j++) {
		if (i == vectorI[j]) return j;
	}
	return -1;
}

FSM::FSM(string str[],int strLen, string nonterminator, string Terminators)
{
	nonTerminators = nonterminator;
	terminators = Terminators;
	production tempPro(str[0]);
	tempPro.toAugmentedGrammar();
	augmentedGrammarProduction.push_back(tempPro);//初始化增广文法
	for (int i = 0; i < strLen;i++) {
		production tempProduction(str[i]);
		productionVector.push_back(tempProduction);
		augmentedGrammarProduction.push_back(tempProduction);
	}
}

void FSM::show()
{
	cout << "原文法:" << endl;
	for (int i = 0; i < productionVector.size(); i++) {
		cout << "(" << i+1 << ")"<< productionVector[i].toPrimaryString() << endl;
	}
	cout << "增广文法:" << endl;
	for (int i = 0; i < augmentedGrammarProduction.size(); i++) {
		cout << "(" << i << ")" << augmentedGrammarProduction[i].toPrimaryString() << endl;
	}
	cout << "I:" << endl;
	for (int i = 0; i < vectorI.size(); i++) {
		cout << "I:" << i << endl;
		vectorI[i].show();
	}
	cout << "GO:" << endl;
	for (int i = 0; i < vectorGO.size(); i++) {
		cout << "GO:" << i << endl;
		vectorGO[i].show();
	}
	//输出ACTION和GOTO表
	int standardLen = 4;
	cout << setw(standardLen) << "状|" <<setw(terminators.size()* standardLen)<< "ACTION" << "|"<< setw(nonTerminators.size() * standardLen) << "GOTO" << endl;
	cout << setw(standardLen) << "态|";
	for (int i = 0; i < terminators.size(); i++) {
		cout << setw(standardLen) << terminators.substr(i, 1);
	}
	cout << "|";
	for (int i = 0; i < nonTerminators.size(); i++) {
		cout << setw(standardLen) << nonTerminators.substr(i, 1);
	}
	cout << endl;
	for (int i = 0; i < vectorI.size(); i++) {
		cout << setw(standardLen) << to_string(i )+ "|";
		for (int j = 0; j < terminators.size(); j++) {
			string terminator = terminators.substr(j, 1);
			string str= mapACTION[i][terminator];
			cout << setw(standardLen) << str;
		}
		cout << "|";
		for (int j = 0; j < nonTerminators.size(); j++) {
			string nonTerminator = nonTerminators.substr(j, 1);
			string str = mapGOTO[i][nonTerminator];
			cout << setw(standardLen) << str;
		}
		cout << endl;
	}
}

void FSM::outPutToFile(string path)
{
	ofstream outFile;
	outFile.open(path);
	//输出ACTION和GOTO表
	int standardLen = 4;
	outFile << setw(standardLen) << "状|" << setw(terminators.size() * standardLen) << "ACTION" << "|" << setw(nonTerminators.size() * standardLen) << "GOTO" << endl;
	outFile << setw(standardLen) << "态|";
	for (int i = 0; i < terminators.size(); i++) {
		outFile << setw(standardLen) << terminators.substr(i, 1);
	}
	outFile << "|";
	for (int i = 0; i < nonTerminators.size(); i++) {
		outFile << setw(standardLen) << nonTerminators.substr(i, 1);
	}
	outFile << endl;
	for (int i = 0; i < vectorI.size(); i++) {
		outFile << setw(standardLen) << to_string(i) + "|";
		for (int j = 0; j < terminators.size(); j++) {
			string terminator = terminators.substr(j, 1);
			string str = mapACTION[i][terminator];
			outFile << setw(standardLen) << str;
		}
		outFile << "|";
		for (int j = 0; j < nonTerminators.size(); j++) {
			string nonTerminator = nonTerminators.substr(j, 1);
			string str = mapGOTO[i][nonTerminator];
			outFile << setw(standardLen) << str;
		}
		outFile << endl;
	}
	outFile.close();
}

void FSM::buildFSM()
{
	I I0;
	I0.addNewProduction(augmentedGrammarProduction[0]);
	vectorI.push_back(I0);//初始化I0
	fill(0);
	for (int i = 0; i < vectorI.size(); i++) {
		for (int j = 0; j < vectorI[i].getVectorProduction().size(); j++) {
			//获取小圆点后的字符
			string strAfterSymbpol = vectorI[i].getVectorProduction()[j].getSymbolNext();
			if (strAfterSymbpol == "") {//当index值和句子右端长度相同即小圆点在最末尾时返回空串
				break;//说明是规约项目,不再继续往下做
			}
			
			I newI=vectorI[i].makeNewI(strAfterSymbpol);//获取通过转移符号获得的新的I
			//newI.productionIncrease();//新I的第一个句子小圆点右移一位
			newI.fill(nonTerminators, productionVector);//若小圆点右边为终结符则将以该终结符为左端的句子加入I
			int to= findSameI(newI);//to为GO的to,在这里暂定为查找相同的I的下标值

			if (to ==-1) {//如果这个新I是集合I里面有的,则不再加入,否则,则加入
				vectorI.push_back(newI);
				to = vectorI.size()-1;
			}
			
			GO go(i, strAfterSymbpol, to);
			vectorGO.push_back(go);
		}
	}
	//初始化ACTION和GOTO表
	for (int i = 0; i < vectorI.size(); i++) {
		map<string, string> t1;
		map<string, string> t2;
		for (int i = 0; i < terminators.size(); i++) {
			t1.emplace(terminators.substr(i, 1), "");
		}
		for (int i = 0; i < nonTerminators.size(); i++) {
			t2.emplace(nonTerminators.substr(i, 1), "");
		}
		mapACTION.emplace(i, t1);
		mapGOTO.emplace(i, t2);
	}
}

void FSM::buildACTIONandGOTO()
{
	int from;
	int next;
	string X;
	for (int i = 0; i < vectorGO.size(); i++) {//遍历每个GO
		from = vectorGO[i].from;
		next = vectorGO[i].next;
		X = vectorGO[i].X;
		I Inext = vectorI[next];
		I Ifrom = vectorI[from];
		/*vector<production> InextProduction = Inext.getVectorProduction();*/
		for (int j = 0; j < Ifrom.getVectorProduction().size(); j++) {
			//遍历每个Ifrom下的句子,查询对应的句子,如A->.aE,而GO为0--a-->1
			//则表示对应,即小圆点后的字符相同
			production productionFrom = Ifrom.getVectorProduction()[j];
			if (productionFrom.getSymbolNext() != X) {
				continue;
			}
			if (productionFrom.getIndex() == productionFrom.getRight().size() - 1) {
				//若小圆点为倒数第二个,则表示的对应下一个I的句子为归约或接受项目
				if (productionFrom.getLeft().back() == '\'') {
					//左端为S',即增广文法新添的,则为接受项目
					mapACTION[next]["#"] = "acc";
					//mapGOTO[from][productionFrom.getLeft().substr(0,1)]= to_string(next);
				}
				//左端不为S',则为归约项目或移进项目
				if (terminators.find(X) != -1) {//为终结符的一种,置Sx
					mapACTION[from][X] = "s" + to_string(next);
				}
				else if (nonTerminators.find(X) != -1) {//为非终结符的一种,置GOTO
					mapGOTO[from][X] = to_string(next);
				}
			}
			else if (productionFrom.getIndex() == productionFrom.getRight().size()) {
				//小圆点在末尾,跳过
				continue;
			}
			else {
				//小圆点不在倒数第二个和末尾
				if (terminators.find(X) != -1) {//为终结符的一种,置Sx
					mapACTION[from][X] = "s" + to_string(next);
				}

			}
		}
	}
	for (int i = 0; i < vectorI.size(); i++) {
		if (vectorI[i].getVectorProduction().size() != 1) {
			continue;
		}
		production prod = vectorI[i].getVectorProduction()[0];
		if (prod.getLeft().back() != '\''
			&& prod.getIndex() != prod.getRight().size()) {
			continue;
		}
		//设置rx的值
		for (int g = 0; g < productionVector.size(); g++) {
			if (prod.toPrimaryString() == productionVector[g].toPrimaryString()) {
				for (int gg = 0; gg < terminators.size(); gg++) {
					//循环设置r的值
					mapACTION[i][terminators.substr(gg, 1)] = "r" + to_string(g+1);
				}
				break;
			}
		}
	}
}

