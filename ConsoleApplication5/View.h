#pragma once
#include <SFML/Graphics.hpp>
#include "SimpleElem.h"
#include "Elements.h"
#include "pair.h"
#include "windows.h"
#include "Sprites.h"

class view //singleton
{
private:
	view() {}
	view& operator=(view&) {}
	static view * p_instance;

	sf::RenderWindow *window;
	pair size = pair(1300, 650);

	pair center_camera = pair(size.getA() / 2 , size.getB() / 2);
	double scroll = 1;
	pair LU = pair((center_camera.getA() - size.getA() / 2) * 1.0 / scroll, (center_camera.getB() + size.getB() / 2) * 1.0 / scroll),
		RD = pair((center_camera.getA() + size.getA() / 2) * 1.0 / scroll, (center_camera.getB() - size.getB() / 2) * 1.0 / scroll);

	bool ready = false;
	bool run = false;
	std::string addition = "";

	inline void load(std::string);

	std::vector<s_sprite> arr_sprite = std::vector<s_sprite>();
	std::vector<s_element> elems = std::vector<s_element>();	
	sprites & Sprits = sprites::getInstance();
public:
	static view * getInstance() {
		if (!p_instance)
			p_instance = new view();
		return p_instance;
	}

	void operator()();

	int frame = 50;

	void draw();

	bool prepare(std::string);

	bool busy() { return run; }

	bool is_ready() { return ready; }

	void setCenter_Camera(pair new_center) {
		center_camera = new_center;
		LU = pair((center_camera.getA() - size.getA() / 2) * 1.0 / scroll, (center_camera.getB() + size.getB() / 2) * 1.0 / scroll);
		RD = pair((center_camera.getA() + size.getA() / 2) * 1.0 / scroll, (center_camera.getB() - size.getB() / 2) * 1.0 / scroll);
	}

	void set_scroll(double new_scroll) {
		scroll = new_scroll < 0 ? scroll : new_scroll;
		LU = pair((center_camera.getA() - size.getA() / 2) * 1.0 / scroll, (center_camera.getB() + size.getB() / 2) * 1.0 / scroll);
		RD = pair((center_camera.getA() + size.getA() / 2) * 1.0 / scroll, (center_camera.getB() - size.getB() / 2) * 1.0 / scroll);
	}

	double get_scroll() { return scroll; }

	pair getCenter_Camera() { return center_camera; }

	pair model_FPS = pair(0, 0);

	pair get_size() { return size; }

	pair get_mouse() {
		sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);//забираем коорд курсора
		sf::Vector2f pos = window->mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
		return pair(pos.x, size.getB() - pos.y);
	}

	~view() {
		delete p_instance;
	}
};


