#pragma once

#include "Element.h"
#include "Map.h"
#include <iostream>


class elements
{
	elements() {}
	elements(const elements&);
	elements& operator=(elements&);

	element* first, *last;	

	static void save(element& current);

	element parseElement(std::string nameFile);

	size_t size = 0;
public:
	
	std::vector<element> Array = std::vector<element>();

	static elements& getInstance() {
		static elements instance;
		return instance;
	}

	element& operator[](const int index) {
		if (index < size)
			return Array[index];
	}

	element* getPoint(const int index) {
		if (index < size)
			return &Array[index];
		else
			return nullptr;
	}

	bool addElement(element& new_elem); 

	inline element * get_last() { return last; }
	inline element * get_first() { return first; }

	void foreach(void (*fun)(element & x));

	element * getByName(std::string name);

	int IgetByName(std::string name);

	void save_all();

	void init();

	bool next_point(element * &current, bool isDraw, bool isThis, bool Valid, bool tempColis);

	void pop_back()
	{
		Array.pop_back();
		size--;
		last = &Array[size - 1];
	}

	inline 	int get_size() const { return size; }
};