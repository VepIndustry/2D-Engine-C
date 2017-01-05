#include "Sprites.h"
#include <iostream> 
#include <fstream>

sf::Sprite sprites::getSprite(s_element & current)
{
	for (picture * x : images)
	{
		if (x->name == current.name_sprite)
			return x->getSp(current);
	}
}

void sprites::init()
{
	std::ifstream fin("Sprites/list.txt"); // файл где лежат названия всех файлов объектов
	size_t count;
	std::string name, line, line2;

	getline(fin, name);
	count = atoi(name.c_str());
	
	for (int i = 0; i < count; i++)
	{
		getline(fin, name);
		s_sprite * temp = new s_sprite(name);
				
		getline(fin, name);

		int count_s = atoi(name.c_str()); //количество спрайтов

		for (int j = 0; j < count_s; j++) {

			getline(fin, line);
			getline(fin, line2);
			pair first = pair(atof(line.c_str()), atof(line2.c_str()));

			getline(fin, line);
			getline(fin, line2);
			pair second = pair(atof(line.c_str()), atof(line2.c_str()));

			temp->addNewSprite(first, second);
		}
		images.push_back(temp);
	}


	fin = std::ifstream("Sprites/anim.txt"); // файл где лежат анимации
	count;
	name, line, line2;

	getline(fin, name);
	count = atoi(name.c_str());

	for (int i = 0; i < count; i++)
	{
		getline(fin, name);

		animation * temp = new animation(name);

		getline(fin, name);

		temp->set_speed(atof(name.c_str()));

		getline(fin, name);

		int count_s = atoi(name.c_str()); //количество спрайтов

		for (int j = 0; j < count_s; j++) {

			getline(fin, line);
			getline(fin, line2);

			for (picture * x : images)
			{
				if (x->name == line)
				{
					temp->addNewSprite(x, atoi(line2.c_str()));
					break;
				}
			}
		}
		images.push_back(temp);
	}
}
