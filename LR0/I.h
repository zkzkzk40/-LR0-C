#pragma once
#include "production.h"
#include <vector>
class I
{
private:
	vector<production> vectorProduction;
public:
	I();//����һ����ʼ��I
	void addNewProduction(production pro);//�����¾���
	void show();//չʾ
	bool operator==(I& right);//ƥ��I�µľ����Ƿ���ͬ
	void fill(string Terminators, vector<production> productionVector);//����СԲ����Ƿ�Ϊ���ս����ѭ�����I
	vector<production> getVectorProduction();
	I makeNewI(string nextStr);//����ת���ַ�������һ��I
	void productionIncrease();//I�µ����о���СԲ������������һλ,���ڳ�ʼ��I
};

