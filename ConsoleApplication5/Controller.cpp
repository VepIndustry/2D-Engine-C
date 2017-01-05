#include "Controller.h"
#include <Windows.h>

controller* controller::p_instance = 0;

void controller::operator()()
{
	p_instance = this;

	while (1)
	{
		if (run)
		{
			if (tasks.size() > 0)
			{
				for (eventing * x : tasks) {
					x->do_it();
					delete x;
				}
				run = false;
				tasks.clear();
			}
			run = false;
		}
	}
}

void controller::move(element * order, pair target)
{
	tasks.push_back(new moving(order, target));
}

void controller::speed(element * order, pair target)
{
	tasks.push_back(new speeding(order, target));
}

void controller::set_speed(element * order, pair target)
{
	tasks.push_back(new set_speeding(order, target));
}

void controller::scroll(element * order, pair target)
{
	tasks.push_back(new scrolling(order, target));
}

void controller::rotate(element * order, pair target)
{
	tasks.push_back(new rotating(order, target));
}

void controller::live_c(element * order)
{
	tasks.push_back(new living_c(order, pair(0, 0)));
}

void controller::live_v(element * order)
{
	tasks.push_back(new living_v(order, pair(0, 0)));
}

void controller::live_d(element * order)
{
	tasks.push_back(new living_d(order, pair(0, 0)));
}

void controller::live_t(element * order)
{
	tasks.push_back(new living_t(order, pair(0, 0)));
}

void controller::size(element * order, pair target)
{
	tasks.push_back(new sizing(order, target));
}

void controller::delete_back() {
	tasks.push_back(new deliting(nullptr, pair(0, 0)));
}
