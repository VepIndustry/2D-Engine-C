#include "Element.h"
#include "Map.h"

pair element::center()
{
	double minX, maxX, minY, maxY;
	minX = maxX = points[0].getA();
	minY = maxY = points[0].getB();
	for (int i = 0; i < points.size(); i++)
	{
		if (minX > points[i].getA()) minX = points[i].getA();
		if (maxX < points[i].getA()) maxX = points[i].getA();
		if (minY > points[i].getB()) minY = points[i].getB();
		if (maxY < points[i].getB()) maxY = points[i].getB();
	}
	pair result((maxX - minX) / 2 + minX, (maxY - minY) / 2 + minY);
	return result;
}

void element::fresh_size() {
	size_t size = points.size();
	double minX, maxX, minY, maxY;

	minX = maxX = points[0].getA();
	minY = maxY = points[0].getB();

	for (int i = 0; i < size - 1; i++)
	{
		if (minX > points[i + 1].getA()) minX = points[i + 1].getA();
		if (maxX < points[i + 1].getA()) maxX = points[i + 1].getA();
		if (minY > points[i + 1].getB()) minY = points[i + 1].getB();
		if (maxY < points[i + 1].getB()) maxY = points[i + 1].getB();
	}

	lu_square = pair(minX, maxY);
	rd_square = pair(maxX, minY);
}

void element::deactive()
{
	isDraw = false;
	isThis = false;
	tempColis = false;
	Valid = false;
}

void element::fresh()
{
	size_t size = points.size();

	for (int i = 0; i < size - 1; i++)
	{
		pair def = points[i + 1] - points[i];
		double tangens = def.getB() / def.getA();
		double ang = atan(tangens);
		angles[i] = ang;
	}

	pair def = points[0] - points[size - 1];
	double tangens = def.getB() / def.getA();
	double ang = atan(tangens);
	angles[size - 1] = ang;

	fresh_size();
}

void element::rotate(double newAngle)
{
	size_t size = points.size();
	for (int i = 0; i < size; i++)
	{
		points[i].rotate(newAngle, position);
	}
	
	fresh();
}

void element::move(unsigned int frame)
{
	speed.multiply(1.0 / frame);
	position += speed;
	size_t size = points.size();
	for (int i = 0; i < size; i++) points[i] += speed;
	lu_square += speed;
	rd_square += speed;
	speed.multiply(frame);
	map::getInstance().fresh(this);
}

void element::move(pair & tempSpeed)
{
	position += tempSpeed;
	size_t size = points.size();
	for (int i = 0; i < size; i++) points[i] += tempSpeed;
	lu_square += tempSpeed;
	rd_square += tempSpeed;
	map::getInstance().fresh(this);
}

bool element::addPoint(pair inter)
{
	points.push_back(inter);
	center();

	size_t size_p = points.size();
	angles.resize(size_p);
	position = center();
	fresh();

	double old_angle = angle;
	setAngle(0);

	double minX, maxX, minY, maxY;

	minX = maxX = points[0].getA();
	minY = maxY = points[0].getB();

	for (int i = 0; i < size_p - 1; i++)
	{
		if (minX > points[i + 1].getA()) minX = points[i + 1].getA();
		if (maxX < points[i + 1].getA()) maxX = points[i + 1].getA();
		if (minY > points[i + 1].getB()) minY = points[i + 1].getB();
		if (maxY < points[i + 1].getB()) maxY = points[i + 1].getB();
	}
	size = pair(maxX - minX, maxY - minY);
	setAngle(old_angle);
	return true;
}

void element::setAngle(double newAngle)
{
	rotate(newAngle - angle);
	angle = newAngle;
}

const double element::getAngle() const
{
	return angle;
}