#include "Game.h"

#include <thread>

void game::run()
{
	model * Model = model::getInstance();
	view * View = view::getInstance();
	controller * Controller = controller::getInstance();

	std::thread thV(*View);
	std::thread thC(*Controller);	
	std::thread thM(*Model);	

	thM.detach();
	thV.detach();
	thC.detach();

	while (1)
	{
		Sleep(10);
	}
}
