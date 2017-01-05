#pragma once
#include "pair.h"
#include "picture.h"
#include <iostream> 
#include <windows.h>
#include "Elements.h"

class animation : public picture
{
	struct anim {
		picture * pic;
		int numb;
	};

	std::vector<anim> sprits = std::vector<anim>();

	sf::Image image;
	unsigned int CurrentFrame = 0;
	double speed = 0.0005;
	double start_time = clock();
public:

	void addNewSprite(picture * new_sp, int number);

	sf::Sprite getSp(s_element & current);

	animation(std::string name) : picture(name) {}

	void set_speed(double new_speed) { speed = new_speed; }
};