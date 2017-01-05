#pragma once
#include "event.h"
#include "Collisioner.h"

class rotating : public eventing
{
private:
	double angle;	

	void rotate(element* ord, int index_point) {
		pair position_point = ord->points[index_point];

		angle = ord->getAngle();
		ord->setAngle(target.getA());

		pair offset_1 = position_point - ord->points[index_point];

		ord->move(offset_1);
	}

	void return_rotate(element* ord, int index_point) {
		target = pair(angle, index_point);
		rotate(ord, index_point);
	}
public:
	rotating(element* order, pair target) : eventing(order, target) {}

	bool do_it()
	{		
		element * ord = elements::getInstance().getPoint(order);
		if (ord == nullptr) return true;

		int numb_point = target.getB();

		if (target.getB() == -1) {
			angle = ord->getAngle();
			ord->setAngle(target.getA());

			if (collizioner::getInstance().isCollision(ord)) {
				ord->setAngle(angle);	
				return false;
			}
			return true;			
		}
				
		rotate(ord, numb_point);	
		map::getInstance().fresh(ord);

		if (collizioner::getInstance().isCollision(ord)) {
			return_rotate(ord, numb_point);
			map::getInstance().fresh(ord);
			return false;
		}
		return true;
	}
};