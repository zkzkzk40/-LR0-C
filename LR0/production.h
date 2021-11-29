#pragma once
#include <iostream>
#include <string>
using namespace std;
class production
{
private:
	const string symbol=".";
	const string fromToNext = "->";
	string left;
	int index;
	string right;
public:
	production(string str);
	string const toString();//���ش�СԲ����ַ���
	string const toPrimaryString();//���ز���СԲ����ַ���
	bool operator==(production& right);//�ж��Ƿ���ͬ
	void toAugmentedGrammar();//��һ����������Ϊ�����ķ��ľ���
	string getLeft();
	string getRight();
	int getIndex();
	void indexIncrease();//СԲ������һλ
	string getSymbolNext();//����СԲ�������ַ�
};

