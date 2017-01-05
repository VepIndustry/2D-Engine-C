#pragma once

#include "God.h"
#include "HelperGod.h"


class model //singleton
{
private:
	model() {}
	model& operator=(model&) {}

	static model * p_instance;

	void initialize();

	unsigned int frame = 500;
public:
	static model * getInstance() {
		if (!p_instance)
			p_instance = new model();
		return p_instance;
	}

	void operator()();

	~model() {
		delete p_instance;
	}
};