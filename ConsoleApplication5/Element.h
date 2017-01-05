#pragma once
#include "pair.h"
#include <vector>
#include <string.h>
#include <SFML/Graphics.hpp>


class element
{	
	void fresh();

public:
	double angle = 0; //декоративное значение, только для спрайтов, в радианах
	double recoil = 0.1;
	double friction = 0.5;
	
	bool isDraw = true; //Нужно ли рисовать
	bool isThis = false; //Может ли являться элементом с которым будет отработка
	bool Valid = true; //нужно ли с ним обрабатывать что то
	bool tempColis = true; //является ли он осязаемым

	pair size = pair(0, 0);

	std::string  name_sprite = "mario";
	int number_sprite = 0;
	pair center();

	pair lu_square = pair(0,0), rd_square = pair(0,0);
	

	double Massa = 0.1;

	std::string NameID = "1";

	pair position = pair(0, 0);
	pair speed = pair(0, 0);
	pair gravitation = pair(0, 0);	

	std::vector<pair> points;
	std::vector<double> angles; // углы между точками 0 и 1, 1 и 2, ..., n и 0.


	element() {}

	int index_elem;

	int condition = 0;

	void rotate(double newAngle);

	void setSpeed(pair newSpeed) { speed = newSpeed; }

	void setNameID(std::string newName) { 
		NameID = newName; 
	}

	void move(unsigned int frame);

	void move(pair& tempSpeed);

	bool addPoint(pair inter);

	void setAngle(double newAngle);

	const double getAngle();

	std::vector<pair> cells = std::vector<pair>();

	void fresh_size();

	void deactive();

	~element() {}
};
