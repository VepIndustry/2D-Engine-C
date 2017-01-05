#include "Factory.h"

#include "Element.h"
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <fstream>

element & factory::getNew()
{
	elements & ell = elements::getInstance();
	ell.addElement();
	element& temp = ell[ell.size - 1];
	std::cout << "in getNew " << &temp << std::endl;
	return temp;
}

element & factory::getByName(std::string name)
{
	for (int i = 0; i < elements::getInstance().size; i++)
	{
		if (elements::getInstance()[i].NameID == name)
			return elements::getInstance()[i];
	}
}






