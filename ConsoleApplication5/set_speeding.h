#pragma once
#include "event.h"

class set_speeding : public eventing
{
public:
	set_speeding(element* order, pair target) : eventing(order, target) {}

	bool do_it()
	{
		element * ord = elements::getInstance().getPoint(order);
		if (ord == nullptr) return true;
		ord->speed = target;
		return true;
	}
};