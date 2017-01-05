#pragma once
#include <time.h>
#include "View.h"
#include "Controller.h"
#include "singleton.h"

class helper : public singleton
{
private:
	clock_t start = clock(), beginSec = 0;
	clock_t start_count = 0;
	unsigned long countFrame = 0;
	clock_t time_frame = clock();
	int frame;

	helper() {}
	helper(const helper&);
	helper& operator=(helper&);

	view * viewer = view::getInstance();

	controller * control = controller::getInstance();

	clock_t sum_sleep = 0;

public:
	static helper& getInstance() {
		static helper instance;
		return instance;
	}

	void setFrame(int nframe) { 
		frame = nframe; 
		countFrame = frame;
	}

	void begin();

	int end();
};