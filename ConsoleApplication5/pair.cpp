#include "pair.h"
#include <cmath>

pair & pair::operator+=(const pair & right)
{
	a += right.a;
	b += right.b;
	return *this;
}

pair & pair::operator*=(const pair & right)
{
		a *= right.a;
		b *= right.b;
		return *this;
}

pair & pair::operator-=(const pair & right)
{
	a -= right.a;
	b -= right.b;
	return *this;
}

bool pair::operator==(const pair & right)
{
	return (a == right.a && b == right.b) ? true : false;
}

const pair pair::operator+(const pair & right)
{
	return pair(a + right.a, b + right.b);
}

const pair pair::operator-(const pair & right)
{
	return pair(a - right.a, b - right.b);
}

void pair::multiply(double factor)
{
	a *= factor;
	b *= factor;
}

 void pair::rotate(double angle) // не изменять
{
	double tempA = a*cos(angle) - b * sin(angle);
	b = a * sin(angle) + b * cos(angle);
	a = tempA;
}

void pair::rotate(double angle, pair center)
{
	a -= center.getA();
	b -= center.getB();
	

	double tempA = a*cos(angle) - b * sin(angle);
	b = a * sin(angle) + b * cos(angle);
	a = tempA;

	a += center.getA();
	b += center.getB();
}

double pair::length(pair from)
{
	return sqrt((a - from.getA())*(a - from.getA()) + (b - from.getB())*(b - from.getB()));
}
