#pragma once
#include "event.h"
#include "Collisioner.h"

class scrolling : public eventing
{
private:
	double angle;

	void scroll(element * ord, int index_point) {
		pair position_point = ord->points[index_point];

		angle = ord->getAngle();
		ord->setAngle(0);

		pair offset_1 = pair(0, 0) - ord->points[index_point];

		ord->move(offset_1);

		for (pair & x : ord->points)
		{
			x = pair(x.getA() * target.getA(), x.getB() * target.getB());
		}

		ord->setAngle(angle);
		position_point -= ord->points[index_point];
		ord->move(position_point);
	}

	void return_scroll(element * ord, int index_point) {
		pair save = target;
		target = pair(1.0 / target.getA(), 1.0 / target.getB());
		scroll(ord, index_point);
		target = save;
	}
public:

	scrolling(element* order, pair target) : eventing(order, target) {}

	bool do_it()
	{
		element * ord = elements::getInstance().getPoint(order);
		if (ord == nullptr) return true;

		bool change = false;

		for (int i = 0; i < ord->points.size(); i++) {
			scroll(ord, i);

			map::getInstance().fresh(ord);
			ord->fresh_size();

			if (collizioner::getInstance().isCollision(ord)) {
				return_scroll(ord, i);
			}
			else {
				change = true;
				ord->size = pair(ord->size.getA() * target.getA(), ord->size.getB() * target.getB());
				break;
			}
		}
		ord->fresh_size();
		ord->position = ord->center();
		map::getInstance().fresh(ord);
		return change;
	}
};