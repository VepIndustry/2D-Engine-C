#pragma once
#include "event.h"

class living_t : public eventing
{
public:
	living_t(element* order, pair target) : eventing(order, target) {}

	bool do_it()
	{
		element * ord = elements::getInstance().getPoint(order);
		if (ord == nullptr) return true;
		ord->isThis = true;
		return true;
	}
};