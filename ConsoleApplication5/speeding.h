#pragma once
#include "event.h"

class speeding : public eventing
{
public:
	speeding(element* order, pair target) : eventing(order, target) {}

	bool do_it()
	{
		element * ord = elements::getInstance().getPoint(order);
		if (ord == nullptr) return true;
		ord->speed += target;
		return true;
	}
};