#pragma once
#include "event.h"
#include "Collisioner.h"

class living_c : public eventing
{
public:
	living_c(element* order, pair target) : eventing(order, target) {}

	bool do_it()
	{
		element * ord = elements::getInstance().getPoint(order);
		if (ord == nullptr) return true;

		if (collizioner::getInstance().isCollision(ord)) {
			ord->tempColis = false;
			return false;
		}
		ord->tempColis = true;
		return true;
	}
};