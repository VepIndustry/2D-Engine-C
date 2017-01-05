#pragma once
#include "Elements.h"
#include "Collisioner.h"
#include "Solver.h"

class physical : public solver
{
private:
	physical() {
		isThis = true;
		tempColis = true;
	}
	physical(const physical&);
	physical& operator=(physical&);

	void rebound(double angle, element * object, double recoil, double friction, int frame);
	void reboundGravity(double angle, element * object, double friction, int frame);
	void gravity(element * object, int frame);

	collizioner & colliz = collizioner::getInstance();

public:
	static physical& getInstance() {
		static physical instance;
		return instance;
	}

	double time = 0;
	
	void solve_for(element& current, unsigned int frame);
};