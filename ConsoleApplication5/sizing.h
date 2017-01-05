#pragma once
#include "event.h"
#include "Collisioner.h"

class sizing : public eventing
{
private:
	double angle;

	pair oldsize = pair(0, 0);

	void size(element* ord, int index_point) {
		pair position_point = ord->points[index_point];
		angle = ord->getAngle();
		ord->setAngle(0);

		pair offset_1 = pair(0, 0) - ord->points[index_point];

		ord->move(offset_1);
		
		pair temp = ord->lu_square - ord->rd_square;
		oldsize = pair(-temp.getA(), temp.getB());

		for (pair & x : ord->points)
		{
			x = pair(x.getA() * target.getA() / oldsize.getA(), x.getB() * target.getB() / oldsize.getB());
		}

		ord->setAngle(angle);

		position_point -= ord->points[index_point];
		ord->move(position_point);
	}

	void return_size(element * ord, int index_point) {
		pair save = target;
		target = oldsize;
		size(ord, index_point);
		target = save;
		ord->fresh_size();
	}
public:

	sizing(element* order, pair target) : eventing(order, target) {}

	bool do_it()
	{
		element * ord = elements::getInstance().getPoint(order);
		if (ord == nullptr) return true;

		bool change = false;

		for (int i = 0; i < ord->points.size(); i++) {
			size(ord, i);

			map::getInstance().fresh(ord);
			ord->fresh_size();

			if (collizioner::getInstance().isCollision(ord)) {
				return_size(ord, i);
			}
			else {
				change = true;
				ord->size = target;
				break;
			}
		}
		ord->position = ord->center();
		map::getInstance().fresh(ord);
		return change;
	}
};