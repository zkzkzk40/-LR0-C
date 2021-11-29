#include "production.h"

production::production(string str)
{
	index = 0;
	left = str.substr(0, 1);
	right = str.substr(3);
}

 string const production::toString()
{
	return string(left + fromToNext + right).insert(left.size()+fromToNext.size() +index, symbol);
}

 string const production::toPrimaryString()
 {
	 return string(left + fromToNext + right);
 }

bool production::operator==(production& right)
{
	return this->index==right.index
		&& this->left==right.left
		&& this->right== right.right;
}

void production::toAugmentedGrammar()
{
	right = left;
	left = left + "'";
}

string production::getLeft()
{
	return left;
}
string production::getRight()
{
	return right;
}

int production::getIndex()
{
	return index;
}

void production::indexIncrease()
{
	index++;
}

string production::getSymbolNext()
{
	if (index == right.size()) {
		return "";
	}
	return right.substr(index,1);
}
