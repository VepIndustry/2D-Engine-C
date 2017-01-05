#include "HelperGod.h"
#include <cstdlib>
#include <time.h>

void helper::begin()
{
	if (clock() - beginSec > 1000) {
		beginSec = clock();
		view::getInstance()->model_FPS = pair(countFrame - start_count, sum_sleep);
		
		start_count = countFrame;
		sum_sleep = 0;
	}
	countFrame++;
}

int helper::end()
{
	if (viewer->prepare(std::to_string(elements::getInstance().get_size()) + " = count elems" ))
		viewer->draw();

	control->do_it();
		

	double timeToSleep = (countFrame) * (1000.0 / frame) + start - clock();
	if (timeToSleep > 0) {
		Sleep(timeToSleep);
		sum_sleep += timeToSleep;
	}
		
	
	time_frame = clock() - time_frame;
	int frames = (1000.0 / time_frame) < 30 ? 30 : (1000.0 / time_frame);
	time_frame = clock();

	if (clock() - beginSec > 1000)
		std::cout << "frame " << frames << std::endl;

	
	while (control->busy()) {}
	return frames;
}
