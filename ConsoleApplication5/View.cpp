#include "windows.h"
#include "View.h"
#include <time.h>
#include <iostream>
#include "conio.h"

# define M_PI           3.14159265358979323846  /* pi */

view* view::p_instance = 0;

inline void view::load(std::string line)
{
	window->clear();

	sf::Sprite temp;

	for (s_element & x : elems) {
		temp = Sprits.getSprite(x);

		temp.setPosition(scroll*(x.position.getA() - center_camera.getA()) + size.getA() / 2, size.getB() / 2 - scroll*(x.position.getB() - center_camera.getB()));

		temp.setRotation(-180 * x.angle / M_PI);
		temp.setScale(scroll, scroll);

		window->draw(temp);
	}

	sf::Font font;
	font.loadFromFile("CyrilicOld.ttf");

	sf::Text text(line, font, 13);
	text.setColor(sf::Color::Red);

	text.setPosition(10, 10);
	window->draw(text);
}


void view::operator()()
{
	p_instance = this;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window = new sf::RenderWindow(sf::VideoMode(size.getA(), size.getB()), "Mario", sf::Style::Default, settings);
	//window->setVerticalSyncEnabled(true);

	sf::Event event;
	sprites::getInstance().init();

	long count_frames = 0;

	long last_frames = 0;
	long last_sum_sleep = 0;
	long sum_sleep = 0;

	long begin_time = 0;

	while (window->isOpen()) {
		if (clock() - begin_time > 1000)
		{
			begin_time = clock();
			last_frames = count_frames;
			last_sum_sleep = sum_sleep;
			sum_sleep = 0;
			count_frames = 0;
		}

		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window->close();
		}

		ready = true;

		if (run)
		{
			ready = false;
			load("View FPS: " + std::to_string(last_frames) + '\n'
				+ "View MAX FPS: " + std::to_string(last_frames * 1000.0 / (1000.0 - last_sum_sleep)) + '\n'
				+ "Model FPS: " + std::to_string(model_FPS.getA()) + '\n'
				+ "Model MAX FPS: " + std::to_string(model_FPS.getA() * 1000.0 / (1000.0 - model_FPS.getB())) + '\n' + addition);

			run = false;

			window->display();
			count_frames++;

			long timeToSleep = (count_frames * 1000 / frame) - (clock() - begin_time);
			sum_sleep += timeToSleep < 0 ? 0 : timeToSleep;
			Sleep(timeToSleep < 0 ? 0 : timeToSleep);
		}
	}
}


void view::draw()
{
	if (ready)
		run = true;
}

bool view::prepare(std::string line)
{
	if (ready && !run) {
		addition = line;
		elems.clear();
		elements & els = elements::getInstance();
		element * el;
		for (int i = 0; i < els.get_size(); i++) {
			el = els.getPoint(i);
			if (el->isDraw
				&& (el->lu_square.getA() < RD.getA()
					&& (el->lu_square.getB() > RD.getB() || el->rd_square.getB() < LU.getB())
					|| el->rd_square.getA() > LU.getA()
					&& (el->lu_square.getB() > RD.getB() || el->rd_square.getB() < LU.getB())))
			{
				elems.push_back({ el->angle, el->name_sprite, el->number_sprite, el->size, el->position, el->index_elem });
			}
		}
		return true;
	}
	return false;
}
