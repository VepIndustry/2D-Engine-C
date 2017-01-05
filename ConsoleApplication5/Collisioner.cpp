#include "Collisioner.h"

# define M_PI           3.14159265358979323846  /* pi */
# define M_PI_2 1.57079632679

inline void calc_k(element * first, element * second, double & k, double ro, double f)
{
	double res = abs(ro / f);

	if (abs(res * f) - ro > 0.1) {
		return;
	}

	if (k > res) k = res;
}

double collizioner::projectiveAxis(pair& point, double& angle)
{
	if (angle == 0) return point.getB();
	if (angle == M_PI_2) return point.getA();
	return point.getA()*cos(M_PI_2 - angle) - point.getB()*sin(M_PI_2 - angle);
}

void collizioner::findminmax(element* PointsObj, double& Angle, double& min, double& max)
{
	min = max = projectiveAxis(PointsObj->points[0], Angle);

	for (int i = 1; i < PointsObj->points.size(); i++)
	{
		double temp = projectiveAxis(PointsObj->points[i], Angle);
		if (temp < min) { min = temp; }
		else if (temp > max) { max = temp; }
	}
}

element * collizioner::interaction(element * current, int frame)
{	
	//model * md = model::getInstance();
	element * result = nullptr;



	bool temps = current->tempColis;
	current->tempColis = false;

	double k = 0;

	int index_elem = -1;
	
	map & mapp = map::getInstance();

	while (mapp.get_elem(current, index_elem))
	{		
		second = elems.getPoint(index_elem);
		if (second->tempColis && isCollision(current, second, k, frame))
		{
			pair temp = current->speed;
			temp.multiply(-k);
			current->move(temp);

			result = second;
		}
	}
	current->tempColis = temps;
	return result;
}

int collizioner::findLine_fhelp(element * This, element * Other)
{
	if (!isCollision(This, Other)) return -1;
	pair temp = interaction_for(This, Other);
	int i_temp = findLine(This, Other);
	temp.multiply(-1);
	This->move(temp);
	return i_temp;
}

pair collizioner::interaction_for(element * current, element * second)
{
	double k = 0;
	if (isCollision(current, second, k, 0))
	{
		pair temp = current->speed;
		temp.multiply(-k);
		current->move(temp);
		return temp;
	}
}

bool collizioner::pre_colliz(element * first, element * second)
{	
	if (second->lu_square.getA() >=first->rd_square.getA()) return false;
	if (second->rd_square.getA() <= first->lu_square.getA()) return false;

	if (second->lu_square.getB() <= first->rd_square.getB()) return false;
	if (second->rd_square.getB() >= first->lu_square.getB()) return false;
	return true;
}

bool collizioner::isCollision(element * first, element * second, double & k, int frame)
{	
	if (first->NameID == second->NameID) return false;
	if (!pre_colliz(first, second)) return false;
	
	k = 1.01;
	double min, max;
	double a, b;
	
	for (int j = 0; j < second->points.size(); j++)
	{
		findminmax(second, second->angles[j], a, b);
		findminmax(first, second->angles[j], min, max);

		if ((((min <= a) && (max <= a)) || ((min >= b) && (max >= b)))) { return false; }

		double f = projectiveAxis(first->speed , second->angles[j]), ro = 0;

		if (f < 0)
		{
			ro = b - min;
			calc_k(first, second, k, ro, f);
		}
		else if (f > 0)
		{
			ro = max - a;
			calc_k(first, second, k, ro, f);
		}
	}

	for (int j = 0; j < first->points.size(); j++)
	{
		findminmax(first, first->angles[j], a, b);
		findminmax(second, first->angles[j], min, max);

		if ((((min <= a) && (max <= a)) || ((min >= b) && (max >= b)))) { return false; }

		double f = projectiveAxis(first->speed, first->angles[j]), ro=0;

		if (f > 0)
		{
			ro = b - min;
			calc_k(first, second,  k, ro, f);
		}
		else if (f < 0)
		{
			ro = max - a;
			calc_k(first,second, k, ro, f);
		}
	}
	if (k > 1.0 / frame + 0.1) {
		k = 0;
		return false;
	}

	return true;
}

bool collizioner::isCollision(element * first, element * second)
{
	if (first->NameID == second->NameID) return false;

	if (!pre_colliz(first, second)) return false;

	double min, max;
	double a, b;
	for (int j = 0; j < second->points.size(); j++)
	{
		findminmax(second, second->angles[j], a, b);
		findminmax(first, second->angles[j], min, max);

		if ((((min <= a) && (max <= a)) || ((min >= b) && (max >= b)))) { return false; }
	}

	for (int j = 0; j < first->points.size(); j++)
	{
		findminmax(first, first->angles[j], a, b);
		findminmax(second, first->angles[j], min, max);

		if ((((min <= a) && (max <= a)) || ((min >= b) && (max >= b)))) { return false; }
	}

	return true;
}

bool collizioner::isCollision(element * first)
{
	int index_elem = -1;

	map & mapp = map::getInstance();
	
	bool oldColis = first->tempColis;
	first->tempColis = false;

	while (mapp.get_elem(first, index_elem))
	{
		second = elems.getPoint(index_elem);
		if (second->tempColis && isCollision(first, second))
		{
			first->tempColis = oldColis;
			return true;
		}
	}
	first->tempColis = oldColis;
	return false;
}

int collizioner::findLine(element * This, element * Other)
{
	pair center = pair(0, 0);
	size_t sizeThis = This->points.size(), sizeOther = Other->points.size();
	
	for (int i = 0; i < sizeThis; i++)
	{
		for (int j = 0; j < sizeOther - 1; j++)
		{
			pair temp1 = (Other->points[j + 1] - Other->points[j]);
			pair temp2 = This->points[i] - Other->points[j];
			double tempd = temp1.getA() * temp2.getB();
			double tempd2 = temp1.getB() *temp2.getA();

			if ((abs(tempd - tempd2) < 0.1) && temp1.length(center) > temp2.length(center))
			{
				return j;
			}
		}
		pair temp1 = (Other->points[0] - Other->points[sizeOther - 1]);
		pair temp2 = This->points[i] - Other->points[sizeOther - 1];

		double tempd = temp1.getA() * temp2.getB();
		double tempd2 = temp1.getB() * temp2.getA();
	
		if ((abs((tempd - tempd2)) < 0.1) && temp1.length(pair(0, 0)) > temp2.length(pair(0, 0)))
		{
			return sizeOther - 1;
		}
	}
	return -1;
}


