#pragma once
#include "Elements.h"

class eventing
{
protected:
	eventing(element* n_order, pair target) : target(target) {
		order = elements::getInstance().IgetByName(n_order->NameID);
	}
	eventing() : target(pair(0, 0)) {}

	int order;
	pair target;
public:

	virtual bool do_it() = 0;
};