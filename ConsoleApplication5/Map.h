#pragma once
#include "pair.h"
#include "Element.h"
#include <iostream>
#include <Windows.h>

class cell
{
private:
	std::vector<int> els = std::vector<int>();	
public:
	int size = 0;
	void add(int cur) {
		els.push_back(cur);
		size++;
	}

	int get_point(int i)
	{
		return els[i];
	}

	void remove(int cur) {		
		size--;	
	
		int i = 0;
		while (els[i] != cur)
		{
			i++;			
		}

		while (i < size) {
			els[i] = els[i+1];
			i++;
		}
		els.resize(size);	
	}
};

class map
{
private:	
	map(const map&);
	map& operator=(map&);

	pair LU = pair(0, 30000);
	pair RD = pair(30000, 0);

	pair size_cell = pair(100, 100);

	pair size = pair((RD.getA() - LU.getA()) / size_cell.getA(), (LU.getB() - RD.getB()) / size_cell.getB());

	std::vector<cell> cells = std::vector<cell>();

	std::vector<int> lists = std::vector<int>();

	map()
	{
		for (int i = 0; i < size.getA(); i++)		
			for (int j = 0; j < size.getB(); j++)			
				cells.push_back(cell());
	}
public:

	static map& getInstance() {
		static map instance;
		return instance;
	}

	bool get_elem(element * order, int& point);

	void fresh(element * order);

	void remove(element * order);

	void set_size_cell(pair new_size)//удалит все €чейки
	{
		cells = std::vector<cell>();
		size_cell = new_size;
		size = pair((RD.getA() - LU.getA()) / size_cell.getA(), (LU.getB() - RD.getB()) / size_cell.getB());
		for (int i = 0; i < size.getA(); i++)
			for (int j = 0; j < size.getB(); j++)
				cells.push_back(cell());
	}
};