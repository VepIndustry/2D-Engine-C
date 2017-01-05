#pragma once
class pair
{
private:
	double a, b;

public:
	pair(const pair& s) : a(s.a), b(s.b) {}
	pair(pair& s) : a(s.a), b(s.b) {}
	pair(double x, double y) : a(x), b(y) {}

	inline const double const getA()
	{
		return a;
	}

	inline const double const getB()
	{
		return b;
	}

	pair& operator+=(const pair& right);

	pair& operator*=(const pair& right);

	pair& operator-=(const pair& right);

	bool operator==(const pair& right);

	const pair operator+(const pair& right);

	const pair operator-(const pair& right);

	void multiply(double factor);

	void rotate(double angle); //крутит относительно начала координат

	void rotate(double angle, pair center);

	double length(pair from);
};
