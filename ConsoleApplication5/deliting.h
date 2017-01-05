#pragma once
#include "event.h"

class deliting : public eventing
{
public:
	deliting(element* order, pair target) : eventing() {}

	bool do_it()
	{
		elements& elems = elements::getInstance();
		map & mapp = map::getInstance();
		element * deleted = elems.getPoint(elems.get_size() - 1);
		
		mapp.remove(deleted);
		elems.pop_back();
		return true;
	}
};