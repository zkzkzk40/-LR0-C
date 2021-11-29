#include "GO.h"

GO::GO(int _from, string _X, int _next)
{
	this->from = _from;
	this->X = _X;
	this->next = _next;
}

void GO::show()
{
	cout << "I" << from << "--" << X << "-->" << "I" << next << endl;
}

