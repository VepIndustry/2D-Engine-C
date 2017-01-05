#pragma once
#include <SFML\Graphics.hpp>
#include "picture.h"
#include "Sprite.h"
#include "Animation.h"
#include "SimpleElem.h"

class sprites
{
	sprites() {}
	sprites(const sprites&);
	sprites& operator=(sprites&);

	std::vector<picture *> images = std::vector<picture *>();
public:
	static sprites& getInstance() {
		static sprites instance;
		return instance;
	}

	sf::Sprite getSprite(s_element & current);

	void init();
};