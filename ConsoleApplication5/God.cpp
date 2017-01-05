#include "God.h"

void god::solve_for(element & current, unsigned int frame)
{	
	current.move(frame);
	
	physical::getInstance().solve_for(current, frame);
}


