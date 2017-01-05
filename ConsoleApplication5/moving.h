#pragma once
#include "event.h"
#include "Collisioner.h"
class moving : public eventing
{
public:
	moving(element* order, pair target) : eventing(order, target) {}

	bool do_it()
	{
		element * ord = elements::getInstance().getPoint(order);
		if (ord == nullptr) return true;

		pair old_pos = ord->position;
		ord->move(pair(target - ord->position));

		if (ord->tempColis && collizioner::getInstance().isCollision(ord)) {
			ord->move(pair(old_pos - ord->position));
			return false;
		}
		return true;
	}
};