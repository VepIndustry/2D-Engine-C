#pragma once
#include <cstring>
#include <iostream>
#include "Element.h"
#include "Collisioner.h"
#include "Functions.h"

class happening // Это события из файла event.txt
{
private:
	int first_o = 0, second_o = 0;
	int number_fun = 0;
	elements& elems = elements::getInstance();
public:
	happening(int first_o, int second_o, std::string name_fun) : first_o(first_o), second_o(second_o) {
		number_fun = functions::getInstance().getByName(name_fun);
	}

	void solve(int frame)
	{
		element* f_o = elems.getPoint(first_o), *s_o = elems.getPoint(second_o);
		if (f_o != nullptr && s_o != nullptr)
			if (f_o->Valid && s_o->Valid)
				if (collizioner::getInstance().isCollision(f_o, s_o))
					functions::getInstance().call(number_fun, f_o, s_o, frame);
	}

	pair get_elem() { return pair(first_o, second_o); }

	int get_fun() { return number_fun; }

	void set(int first, int second, int fun) {
		first_o = first < 0 ? first_o : first;
		second_o = second < 0 ? second_o : second;
		number_fun = fun < 0 ? number_fun : fun;
	}

	happening() {}
};