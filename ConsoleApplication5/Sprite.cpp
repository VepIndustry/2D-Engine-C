#include "Sprite.h"

void s_sprite::addNewSprite(pair first, pair second)
{
	textures.push_back(sf::Texture());
	int size = textures.size();

	sf::Texture * temp = &textures[size - 1];
	temp->loadFromImage(image, sf::IntRect(first.getA(), first.getB(), second.getA(), second.getB()));

	temp->setRepeated(true);
}

sf::Sprite s_sprite::getSp(s_element & current)
{
	sf::Texture * temp = &textures[current.number_sprite];
	sf::Sprite sprite;

	sprite.setTexture(*temp);

	double weight = current.size.getA(), height = current.size.getB();

	sprite.setTextureRect(sf::IntRect(0, 0, weight, height));

	sprite.setOrigin(weight / 2, height / 2);
	return sprite;
}

s_sprite::s_sprite(std::string name) : picture(name)
{
	image.loadFromFile("Sprites/" + name + ".png");
	image.createMaskFromColor(sf::Color(1, 1, 1));
}
