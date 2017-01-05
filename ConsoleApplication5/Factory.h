#pragma once
#include "Elements.h"

#include <iostream> 
#include <fstream>
#include <string>

class factory //singleton
{
private:
	factory() {}
	factory(const factory&);
	factory& operator=(factory&);

	element parseElement(std::string nameFile);

	
public:
	static factory& getInstance() {
		static factory instance;
		return instance;
	}

	void init();
	
	

	element & getNew();

	element & getByName(std::string name);
};