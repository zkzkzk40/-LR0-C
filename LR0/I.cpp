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
            cout << "������ͬ�ľ���,�������\n";
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

void I::fill(string Terminators, vector<production> productionVector)
{//����СԲ����Ƿ�Ϊ���ս����ѭ�����I
    int size = vectorProduction.size();//size��Ҫ�̶�,���������¾��Ӽ��������
    for (int j = 0; j < size; j++) {
        //next��СԲ�����'.'������Ǹ���ĸ,Ϊ�ս������ս��
        string right = vectorProduction[0].getRight();
        int index = vectorProduction[0].getIndex();
        string next = right.substr(index, 1);
        if (Terminators.find(next)!=-1) {//����Ƿ��ս��,��ִ�������㷨
            for (int i = 0; i < productionVector.size(); i++) {//����ԭ�ķ�
                if (productionVector[i].getLeft() == next) {//�����������Ǻ�next��ͬ�������I
                    this->vectorProduction.push_back(productionVector[i]);
                }
            }
        }
    } 
}

vector<production> I::getVectorProduction()
{
    return vectorProduction;
}

I I::makeNewI(string nextStr)//����ת���ַ�������һ��I
{
    I result;
    for (int i = 0; i < vectorProduction.size(); i++) {//����I�µ����о���
        if (vectorProduction[i].getSymbolNext() == nextStr) {//����þ���СԲ�������ַ��봫����ַ���ͬ
            production newProduction = vectorProduction[i];//�����¾���
            newProduction.indexIncrease();//����СԲ������
            result.addNewProduction(newProduction);//�򷵻ص���I�м���þ���
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



