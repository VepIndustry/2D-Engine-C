#pragma once
#include "event.h"
#include "Collisioner.h"
class living_v : public eventing
{
public:
	living_v(element* order, pair target) : eventing(order, target) {}

	bool do_it()
	{		
		element * ord = elements::getInstance().getPoint(order);
		if (ord == nullptr) return true;
		ord->Valid = true;
		return true;
	}
};