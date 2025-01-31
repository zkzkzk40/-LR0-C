#include "I.h"

I::I()
{
	
}

void I::addNewProduction(production pro)
{
    auto first = vectorProduction.begin();
    auto end = vectorProduction.end();
    while (first != end)
    {
        if (*first == pro) {
            cout << "存在相同的句型,不予添加\n";
            return;
        }
        ++first;
    }
    vectorProduction.push_back(pro);
}

void I::show()
{
    for (int i = 0; i < vectorProduction.size(); i++) {
        cout << vectorProduction[i].toString() << endl;
    }
}

bool I::operator==(I& right)
{
    if (right.vectorProduction.size() != this->vectorProduction.size()) {
        return false;
    }
    for (int i = 0; i < right.vectorProduction.size(); i++) {
        if (!(right.vectorProduction[i] == this->vectorProduction[i])) {
            return false;
        }
    }
    return true;
}

void I::fill(string nonTerminators, vector<production> primaryGrammerProductionVector)
{//根据小圆点后是否为非终结符来循环填充I
    for (int j = 0; j < vectorProduction.size(); j++) {
        //next是小圆点符号'.'后面的那个字母,为终结符或非终结符
        string right = vectorProduction[j].getRight();
        int index = vectorProduction[j].getIndex();
        string next = right.substr(index, 1);
        if (nonTerminators.find(next)!=-1) {//如果是非终结符,则执行如下算法
            for (int i = 0; i < primaryGrammerProductionVector.size(); i++) {//遍历原文法
                if (contain(primaryGrammerProductionVector[i])) {//如果I中的句子已经有该句子,则跳过
                    continue;
                }
                if (primaryGrammerProductionVector[i].getLeft() == next) {//如果句子左边是和next相同的则加入I
                    this->vectorProduction.push_back(primaryGrammerProductionVector[i]);
                }
            }
        }
    } 
}

vector<production> I::getVectorProduction()
{
    return vectorProduction;
}

I I::makeNewI(string nextStr)//根据转移字符生成下一个I
{
    I result;
    for (int i = 0; i < vectorProduction.size(); i++) {//遍历I下的所有句子
        if (vectorProduction[i].getSymbolNext() == nextStr) {//如果该句子小圆点后面的字符与传入的字符相同
            production newProduction = vectorProduction[i];//生成新句子
            newProduction.indexIncrease();//句子小圆点右移
            result.addNewProduction(newProduction);//则返回的新I中加入该句子
            //break;
        }
    }
    return result;
}

void I::productionIncrease()
{
    for (int i = 0; i < vectorProduction.size(); i++) {
        vectorProduction[i].indexIncrease();
    }
}

bool I::contain(production pro)
{
    for (int i = 0; i < vectorProduction.size(); i++) {
        if (vectorProduction[i].toString() == pro.toString()) {
            return true;
        }
    }
    return false;
}



