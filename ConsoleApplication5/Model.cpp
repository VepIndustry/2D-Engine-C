#include "Model.h"
#include "windows.h"

model* model::p_instance = 0;

void model::initialize()
{
	elements::getInstance().init();
}

void model::operator()()
{
	p_instance = this;

	god & God = god::getInstance();
	helper & HelperGod = helper::getInstance();

	initialize();
	HelperGod.setFrame(frame);
	while (true)
	{
		HelperGod.begin();
		
		fHelper::getInstance().solve(frame);
		
		God.solve(frame);			
		
		frame = HelperGod.end();
	}
}
