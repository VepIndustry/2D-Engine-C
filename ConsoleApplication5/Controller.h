#pragma once
#include <vector>
#include "event.h"
#include "moving.h"
#include "sizing.h"
#include "scrolling.h"
#include "rotating.h"
#include "speeding.h"
#include "set_speeding.h"
#include "living_c.h"
#include "deliting.h"
#include "living_v.h"
#include "living_d.h"
#include "living_t.h"

class controller //singleton
{
private:
	controller() {}
	controller& operator=(controller&) {}

	static controller * p_instance;

	std::vector<eventing*> tasks = std::vector<eventing*>();

	bool run = false;

	elements& elems = elements::getInstance();
public:
	static controller * getInstance() {
		if (!p_instance)
			p_instance = new controller();
		return p_instance;
	}

	void operator()();

	void move(element * order, pair target);
	void speed(element * order, pair target);
	void set_speed(element * order, pair target);
	void scroll(element * order, pair target);
	void rotate(element * order, pair target); //первый это угол а вторая это точка -1 центр
	void live_c(element * order);
	void live_v(element * order);
	void live_d(element * order);
	void live_t(element * order);
	void size(element * order, pair target);
	void delete_back();
	
	
	void do_it() {
		run = true;
	}

	bool busy()	{
		return run;
	}

	~controller() {
		delete p_instance;
	}
};