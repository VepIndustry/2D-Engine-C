#pragma once
#include <cstring>
#include <SFML/Graphics.hpp>
#include "SimpleElem.h"

class picture
{
public:
	const std::string name;

	picture(std::string name) : name(name) {}

	virtual sf::Sprite getSp(s_element & current) = 0;
};