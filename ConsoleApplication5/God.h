#pragma once
#include "Solver.h"
#include "PhysicalHelper.h"
#include "FunctionHelper.h"
#include <vector>

class god : public solver
{
	god() {
		isThis = true;
	}
	god(const god&);
	god& operator=(god&);
public:
	static god& getInstance() {
		static god instance;
		return instance;
	}

	void solve_for(element & current, unsigned int frame);
};