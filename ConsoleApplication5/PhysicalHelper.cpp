#include "PhysicalHelper.h"
#include <cmath>

# define M_PI           3.14159265358979323846

void physical::rebound(double angle, element* object, double recoil, double friction, int frame)
{
	double X, Y;
	X = pow(friction, 1.0 / frame) * (object->speed.getA()*cos(angle) + object->speed.getB()*sin(angle));
	Y = -1 * (recoil + 0.01) * (-object->speed.getA()*sin(angle) + object->speed.getB()*cos(angle));
	object->setSpeed(pair(X, Y));
	object->speed.rotate(angle);
}

void physical::reboundGravity(double angle, element* object, double friction, int frame)
{
	double X = friction * (object->gravitation.getA() *object->Massa*cos(angle) + object->gravitation.getB() *object->Massa*sin(angle));
	pair temp(X, 0);
	temp.multiply(1.0 / frame);
	temp.rotate(angle);
	object->speed += temp;
}

void physical::gravity(element* object, int frame)
{
	pair temp = pair(object->gravitation.getA() *object->Massa / frame, object->gravitation.getB() *object->Massa / frame);
	object->speed += temp;
}

void physical::solve_for(element & current, unsigned int frame)
{
	if (current.tempColis) {
		element * second = colliz.interaction(&current, frame);

		if (second != nullptr)
		{
			int number = colliz.findLine(&current, second);
			double angle = 0;

			if (number != -1) {
				angle = second->angles[number];
			}
			else
			{
				number = colliz.findLine(second, &current);
				angle = current.angles[number];
			}
			rebound(angle, &current, current.recoil, current.friction, frame);
			reboundGravity(angle, &current, current.friction, frame);
		}
		else
		{
			gravity(&current, frame);
		}
	}
	else
		gravity(&current, frame);
}
