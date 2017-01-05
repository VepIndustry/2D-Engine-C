#pragma once
#include <string.h>
#include "pair.h"
#include <iostream>

struct s_element
{
public:
	double angle;
	std::string name_sprite;
	int number_sprite;

	pair size;
	pair position;

	int index_elem;
};