#pragma once
#include "Model.h"
#include "View.h"
#include "Controller.h"
#include "singleton.h"

class game : public singleton
{
private:
	game() {}
	game(const game&);
	game& operator=(game&) {};
public:
	static game& getInstance() {
		static game instance;
		return instance;
	}

	void run();
};