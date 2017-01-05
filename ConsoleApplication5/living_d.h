#pragma once
#include "event.h"

class living_d : public eventing
{
public:
	living_d(element* order, pair target) : eventing(order, target) {}

	bool do_it()
	{
		element * ord = elements::getInstance().getPoint(order);
		if (ord == nullptr) return true;
		ord->isDraw = true;
		return true;
	}
};