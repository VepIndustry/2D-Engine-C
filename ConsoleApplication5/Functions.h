#pragma once
#include <vector>
#include "Elements.h"
#include "View.h"
#include "SFML/Graphics.hpp"
#include "Controller.h"

class functions
{
private:
	//friend class function;
	controller * control = controller::getInstance();

	//functions
	void vieww(element * caller, element * second);
	void move_mario(element * caller, element * second);
	void move_rocket(element * caller, element * second);
	void kill(element * caller, element * other);
	void kill_m(element * caller, element * other);
	void del_bull(element * caller, element * second);
	void invis(element * caller, element * second);

	void del_object(element * caller, element * second);

	void close_door(element * caller, element * second);

	void open_door(element * caller, element * second);

	void shoot_1(element * caller, element * second);

	void shoot_2(element * caller, element * second);

	void shoot_3(element * caller, element * second);

	void stop_plat(element * caller, element * second);

	void end_tank(element * caller, element * second);

	void grav(element * caller, element * second);

	void up_up_mario(element * caller, element * second);

	void meet_enemy(element * caller, element * second);
	void kick_muth(element * caller, element * second);
	void meet_muth(element * caller, element * second);
	void grav_to_mouse(element * caller, element * second);
	void time_for_mouse(element * caller, element * second);

	void move_to_cosmic(element * caller, element * second);

	void mutant_tank(element * caller, element * second);

	//переменные для функций

	int last_shoot = 0;
	int last_shoot_1 = 0;
	int last_shoot_2 = 0;
	int last_shoot_3 = 0;
	int count_bull = 0;
	int life = 3;
	int pl_index_1 = elements::getInstance().getByName("planet_1")->index_elem,
		pl_index_2 = elements::getInstance().getByName("planet_2")->index_elem,
		pl_index_3 = elements::getInstance().getByName("planet_3")->index_elem;
	clock_t begin = 0;


	void dead_mario(element * caller);
	void up_mario(element * caller);

	functions() {
		arr_name.push_back("move_cam");
		arr.push_back(&functions::vieww);

		arr_name.push_back("moving_mario");
		arr.push_back(&functions::move_mario);

		arr_name.push_back("kick_coin");
		arr.push_back(&functions::invis);


		arr_name.push_back("del_object");
		arr.push_back(&functions::del_object);

		arr_name.push_back("meet_enemy");
		arr.push_back(&functions::meet_enemy);


		arr_name.push_back("kick_muth");
		arr.push_back(&functions::kick_muth);

		arr_name.push_back("end_tank");
		arr.push_back(&functions::end_tank);

		arr_name.push_back("meet_muth");
		arr.push_back(&functions::meet_muth);

		arr_name.push_back("move_rocket");
		arr.push_back(&functions::move_rocket);

		arr_name.push_back("up_up_mario");
		arr.push_back(&functions::up_up_mario);

		arr_name.push_back("stop_plat");
		arr.push_back(&functions::stop_plat);

		arr_name.push_back("close_door");
		arr.push_back(&functions::close_door);

		arr_name.push_back("open_door");
		arr.push_back(&functions::open_door);

		arr_name.push_back("mutant_tank");
		arr.push_back(&functions::mutant_tank);

		arr_name.push_back("shoot_1");
		arr.push_back(&functions::shoot_1);

		arr_name.push_back("shoot_2");
		arr.push_back(&functions::shoot_2);

		arr_name.push_back("shoot_3");
		arr.push_back(&functions::shoot_3);

		arr_name.push_back("kill");
		arr.push_back(&functions::kill);

		arr_name.push_back("kill_m");
		arr.push_back(&functions::kill_m);

		arr_name.push_back("del_bull");
		arr.push_back(&functions::del_bull);

		arr_name.push_back("move_to_cosmic");
		arr.push_back(&functions::move_to_cosmic);

		arr_name.push_back("grav");
		arr.push_back(&functions::grav);

		arr_name.push_back("grav_to_mouse");
		arr.push_back(&functions::grav);


		arr_name.push_back("time_for_mouse");
		arr.push_back(&functions::time_for_mouse);
		//10

	}
	functions(const functions&);
	functions& operator=(functions&);
	std::vector<void(functions::*)(element *, element *)> arr = std::vector<void(functions::*)(element *, element *)>();
	std::vector<std::string> arr_name = std::vector<std::string>();

	elements & elems = elements::getInstance();
public:
	static functions& getInstance() {
		static functions instance;
		return instance;
	}
	int frame_model;

	void call(int index, element* caller, element* second, int frame);

	int getByName(std::string name) {
		int i = 0;
		for (std::string & x : arr_name)
		{
			if (x == name) return i;
			i++;
		}
		return -1;
	}
};
