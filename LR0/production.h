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
	string const toString();//返回带小圆点的字符串
	string const toPrimaryString();//返回不带小圆点的字符串
	bool operator==(production& right);//判断是否相同
	void toAugmentedGrammar();//将一个句型设置为增广文法的句型
	string getLeft();
	string getRight();
	int getIndex();
	void indexIncrease();//小圆点右移一位
	string getSymbolNext();//或许小圆点后面的字符
};

