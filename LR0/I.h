#pragma once
#include "production.h"
#include <vector>
class I
{
private:
	vector<production> vectorProduction;
public:
	I();//构建一个初始的I
	void addNewProduction(production pro);//加入新句子
	void show();//展示
	bool operator==(I& right);//匹配I下的句子是否相同
	void fill(string Terminators, vector<production> productionVector);//根据小圆点后是否为非终结符来循环填充I
	vector<production> getVectorProduction();
	I makeNewI(string nextStr);//根据转移字符生成下一个I
	void productionIncrease();//I下的所有句子小圆点无条件右移一位,用于初始化I
};

