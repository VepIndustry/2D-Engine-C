#pragma once
#include "pair.h"
#include "Collisioner.h"
#include "picture.h"

# define M_PI           3.14159265358979323846  /* pi */

class s_sprite : public picture
{
	std::vector<sf::Texture> textures = std::vector<sf::Texture>();
	sf::Image image;

public:
	void addNewSprite(pair first, pair second);

	sf::Sprite getSp(s_element & current);

	s_sprite(std::string name);
};