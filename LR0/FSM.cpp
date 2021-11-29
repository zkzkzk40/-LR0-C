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
	augmentedGrammarProduction.push_back(tempPro);//��ʼ�������ķ�
	for (int i = 0; i < strLen;i++) {
		production tempProduction(str[i]);
		productionVector.push_back(tempProduction);
		augmentedGrammarProduction.push_back(tempProduction);
	}
}

void FSM::show()
{
	cout << "ԭ�ķ�:" << endl;
	for (int i = 0; i < productionVector.size(); i++) {
		cout << "(" << i+1 << ")"<< productionVector[i].toPrimaryString() << endl;
	}
	cout << "�����ķ�:" << endl;
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
	//���ACTION��GOTO��
	int standardLen = 4;
	cout << setw(standardLen) << "״|" <<setw(terminators.size()* standardLen)<< "ACTION" << "|"<< setw(nonTerminators.size() * standardLen) << "GOTO" << endl;
	cout << setw(standardLen) << "̬|";
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
	//���ACTION��GOTO��
	int standardLen = 4;
	outFile << setw(standardLen) << "״|" << setw(terminators.size() * standardLen) << "ACTION" << "|" << setw(nonTerminators.size() * standardLen) << "GOTO" << endl;
	outFile << setw(standardLen) << "̬|";
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
	vectorI.push_back(I0);//��ʼ��I0
	fill(0);
	for (int i = 0; i < vectorI.size(); i++) {
		for (int j = 0; j < vectorI[i].getVectorProduction().size(); j++) {
			//��ȡСԲ�����ַ�
			string strAfterSymbpol = vectorI[i].getVectorProduction()[j].getSymbolNext();
			if (strAfterSymbpol == "") {//��indexֵ�;����Ҷ˳�����ͬ��СԲ������ĩβʱ���ؿմ�
				break;//˵���ǹ�Լ��Ŀ,���ټ���������
			}
			
			I newI=vectorI[i].makeNewI(strAfterSymbpol);//��ȡͨ��ת�Ʒ��Ż�õ��µ�I
			//newI.productionIncrease();//��I�ĵ�һ������СԲ������һλ
			newI.fill(nonTerminators, productionVector);//��СԲ���ұ�Ϊ�ս�����Ը��ս��Ϊ��˵ľ��Ӽ���I
			int to= findSameI(newI);//toΪGO��to,�������ݶ�Ϊ������ͬ��I���±�ֵ

			if (to ==-1) {//��������I�Ǽ���I�����е�,���ټ���,����,�����
				vectorI.push_back(newI);
				to = vectorI.size()-1;
			}
			
			GO go(i, strAfterSymbpol, to);
			vectorGO.push_back(go);
		}
	}
	//��ʼ��ACTION��GOTO��
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
	for (int i = 0; i < vectorGO.size(); i++) {//����ÿ��GO
		from = vectorGO[i].from;
		next = vectorGO[i].next;
		X = vectorGO[i].X;
		I Inext = vectorI[next];
		I Ifrom = vectorI[from];
		/*vector<production> InextProduction = Inext.getVectorProduction();*/
		for (int j = 0; j < Ifrom.getVectorProduction().size(); j++) {
			//����ÿ��Ifrom�µľ���,��ѯ��Ӧ�ľ���,��A->.aE,��GOΪ0--a-->1
			//���ʾ��Ӧ,��СԲ�����ַ���ͬ
			production productionFrom = Ifrom.getVectorProduction()[j];
			if (productionFrom.getSymbolNext() != X) {
				continue;
			}
			if (productionFrom.getIndex() == productionFrom.getRight().size() - 1) {
				//��СԲ��Ϊ�����ڶ���,���ʾ�Ķ�Ӧ��һ��I�ľ���Ϊ��Լ�������Ŀ
				if (productionFrom.getLeft().back() == '\'') {
					//���ΪS',�������ķ������,��Ϊ������Ŀ
					mapACTION[next]["#"] = "acc";
					//mapGOTO[from][productionFrom.getLeft().substr(0,1)]= to_string(next);
				}
				//��˲�ΪS',��Ϊ��Լ��Ŀ���ƽ���Ŀ
				if (terminators.find(X) != -1) {//Ϊ�ս����һ��,��Sx
					mapACTION[from][X] = "s" + to_string(next);
				}
				else if (nonTerminators.find(X) != -1) {//Ϊ���ս����һ��,��GOTO
					mapGOTO[from][X] = to_string(next);
				}
			}
			else if (productionFrom.getIndex() == productionFrom.getRight().size()) {
				//СԲ����ĩβ,����
				continue;
			}
			else {
				//СԲ�㲻�ڵ����ڶ�����ĩβ
				if (terminators.find(X) != -1) {//Ϊ�ս����һ��,��Sx
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
		//����rx��ֵ
		for (int g = 0; g < productionVector.size(); g++) {
			if (prod.toPrimaryString() == productionVector[g].toPrimaryString()) {
				for (int gg = 0; gg < terminators.size(); gg++) {
					//ѭ������r��ֵ
					mapACTION[i][terminators.substr(gg, 1)] = "r" + to_string(g+1);
				}
				break;
			}
		}
	}
}

