#include "Animation.h"

void animation::addNewSprite(picture * new_sp, int number)
{
	sprits.push_back({ new_sp, number });
}

sf::Sprite animation::getSp(s_element & current)
{
	if (speed == 0) elements::getInstance().getPoint(current.index_elem)->isDraw = false;
	CurrentFrame = (int)(speed* (clock() - start_time));
	if (CurrentFrame >= sprits.size()) {
		start_time = clock();
		CurrentFrame = 0;
	}

	anim drawed = sprits[CurrentFrame];
	current.number_sprite = drawed.numb;
	return drawed.pic->getSp(current);
}

