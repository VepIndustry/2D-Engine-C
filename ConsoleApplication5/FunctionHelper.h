#pragma once
#include "Elements.h"
#include "Controller.h"
#include "Collisioner.h"

#include <iostream> 
#include <fstream>

#include "happening.h"

class fHelper
{
private:
	fHelper() {
		elements & elems = elements::getInstance();
	

		std::ifstream fin("Obj/event.txt");

		std::string line, line2, line3;

		getline(fin, line);
		int count = atoi(line.c_str()); //количество событий

		for (int i = 0; i < count; i++)
		{
			getline(fin, line);
			getline(fin, line2);
			getline(fin, line3);

			optimize(pair(elems.IgetByName(line), elems.IgetByName(line2)));

			happends.push_back(happening(elems.IgetByName(line), elems.IgetByName(line2), line3));
			getline(fin, line);
		}
	}
	fHelper(const fHelper&);
	fHelper& operator=(fHelper&);


	controller * control = controller::getInstance();

	std::vector<happening> happends = std::vector<happening>();

	std::vector<int> els = std::vector<int>();

	std::vector<happening> pre_hap = std::vector<happening>();

	std::vector<int> del_hap = std::vector<int>();

	void optimize(pair);

	void delete_element(int index);

public:
	static fHelper& getInstance() {
		static fHelper instance;
		return instance;
	}

	void solve(unsigned int frame);

	void solve_for(element & current, unsigned int frame);

	void addHappen(happening new_hap);
};