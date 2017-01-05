#include "FunctionHelper.h"
#include "Functions.h"


void fHelper::solve_for(element & current, unsigned int frame)
{
	//elements& elems = elements::getInstance();
	//collizioner& colliz = collizioner::getInstance();
	//functions & func = functions::getInstance();
	//if (!current.Valid) return;
	/*for ( function & x : current.CallerObjects)
	{
		if (elems[x.index].Valid && colliz.isCollision(&current, elems.getPoint(x.index)))
		{
			for (int nFun : x.numbersFun)
			{
				func.call(nFun, &current, elems.getPoint(x.index), frame);
			}
		}
	}*/
}

void fHelper::addHappen(happening new_hap)
{
	pre_hap.push_back(new_hap);
}

void fHelper::delete_element(int index)
{
	int i = 0;
	for (i = 0; i < els.size(); i++) {
		if (els[i] == index) break;
	}

	for (; i < els.size() - 1; i++) {
		els[i] = els[i + 1];
	}
	els.resize(els.size() - 1);

	pair temp = pair(0, 0);

	for (int i = 0; i < happends.size(); i++) {
		temp = happends[i].get_elem();
		if (temp.getA() == index || temp.getB() == index) {
			for (int j = i; j < happends.size() - 1; j++) {
				happends[j].set(happends[j + 1].get_elem().getA(), happends[j + 1].get_elem().getB(), happends[j + 1].get_fun());
			}
			happends.resize(happends.size() - 1);
			i--;
		}
	}
}

void fHelper::optimize(pair hap)
{
	bool inter_a = false, inter_b = false;
	for (int x : els) {
		if (x == hap.getA()) {
			inter_a = true;
		}
		if (x == hap.getB()) {
			inter_b = true;
		}
	}
	if (!inter_a) els.push_back(hap.getA());
	if (!inter_b) els.push_back(hap.getB());
}

void fHelper::solve(unsigned int frame)
{
	elements & elems = elements::getInstance();

	for (int x : els) {
		element * el = elems.getPoint(x);
		if (el == nullptr)
			del_hap.push_back(x);
		else if (el->isThis && el->Valid) el->move(frame);
	}

	for (happening & x : happends) {
		x.solve(frame);
	}

	for (int x : els) {
		element * ptr = elems.getPoint(x);
		if (ptr != nullptr && ptr->isThis && ptr->Valid) {
			elems.getPoint(x)->speed.multiply(-1);
			elems.getPoint(x)->move(frame);
			elems.getPoint(x)->speed.multiply(-1);
		}
	}

	if (del_hap.size() > 0) {
		for (int x : del_hap) {
			delete_element(x);
		}
		del_hap.clear();
	}

	if (pre_hap.size() > 0) {
		bool inter = false;
		for (happening x : pre_hap) {
			for (happening & y : happends)
			{
				if (x.get_elem() == y.get_elem() && x.get_fun() == y.get_fun()) {
					inter = true;
					break;
				}
			}
			if (!inter) {
				happends.push_back(x);
				optimize(x.get_elem());
			}
		}

		pre_hap.clear();
	}
}