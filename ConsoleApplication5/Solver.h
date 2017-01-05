#pragma once
#include "Elements.h"
class solver {
protected:
	bool isDraw, isThis, Valid, tempColis;
	elements & elems = elements::getInstance();
	element * current = nullptr;

public:
	void solve(unsigned int frame) {
		current = elems.get_first();

		while (current <= elems.get_last())
		{
			if (current->isThis)
				solve_for(*current, frame);
			current++;
		}
	}

	virtual void solve_for(element & current, unsigned int frame) = 0;
};