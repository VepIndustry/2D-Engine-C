#pragma once
#include "Elements.h"
#include "Map.h"
//#include "Model.h"

class collizioner
{
	collizioner() {}
	collizioner(const collizioner&);
	collizioner& operator=(collizioner&);

	double projectiveAxis(pair & point, double & angle);

	pair interaction_for(element * current, element * second);

	bool pre_colliz(element * first, element * second);

	elements & elems = elements::getInstance();
	element * second = nullptr;
public:
	static collizioner& getInstance() {
		static collizioner instance;
		return instance;
	}
	void findminmax(element * PointsObj, double & Angle, double & min, double & max);

	
	element* interaction(element * current, int frame); //решает коллизию, хотя по идее и не должен, но хз как исправить

	int findLine_fhelp(element * This, element * Other);
	
	bool isCollision(element * first, element * second, double & k, int frame);

	bool isCollision(element * first, element * second);

	bool isCollision(element * first);

	int findLine(element * This, element * Other);
	
};