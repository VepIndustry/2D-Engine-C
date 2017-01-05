#include "Elements.h"

#include <iostream> 
#include <fstream>
#include <string>

void elements::save(element & current)
{
	remove(("Obj/" + current.NameID + ".txt").c_str());
	std::ofstream fout;
	fout.open(("Obj/" + current.NameID + ".txt"));

	fout << current.recoil << std::endl;

	fout << current.friction << std::endl;

	fout << current.isDraw << std::endl;

	fout << current.isThis << std::endl;


	fout << current.Valid << std::endl;


	fout << current.tempColis << std::endl;


	fout << current.Massa << std::endl;


	fout << current.NameID << std::endl;


	fout << current.position.getA() << std::endl;
	fout << current.position.getB() << std::endl;

	fout << current.speed.getA() << std::endl;
	fout << current.speed.getB() << std::endl;

	fout << current.gravitation.getA() << std::endl;
	fout << current.gravitation.getB() << std::endl;

	fout << current.points.size() << std::endl;

	for (int i = 0; i < current.points.size(); i++)
	{
		fout << current.points[i].getA() << std::endl;
		fout << current.points[i].getB() << std::endl;
	}

	fout << current.getAngle() << std::endl;


	fout << current.name_sprite << std::endl;

	fout << current.number_sprite << std::endl;

	//current.set_sprite();
	fout.close();
}

element elements::parseElement(std::string name)
{
	element result = element();
	
	std::ifstream fin(name);

	std::string line, line2;

	//парсим по порядку задания переменных в element.h, но angle предпоследний, и в конце функции 

	getline(fin, line);
	result.recoil = atof(line.c_str());

	getline(fin, line);
	result.friction = atof(line.c_str());

	getline(fin, line);
	result.isDraw = line == "0" ? false : true;

	getline(fin, line);
	result.isThis = line == "0" ? false : true;

	getline(fin, line);
	result.Valid = line == "0" ? false : true;

	getline(fin, line);
	result.tempColis = line == "0" ? false : true;

	getline(fin, line);
	result.Massa = atof(line.c_str());

	getline(fin, line);
	result.setNameID(line);


	getline(fin, line);
	getline(fin, line2);
	result.position = pair(atof(line.c_str()), atof(line2.c_str()));

	getline(fin, line);
	getline(fin, line2);
	result.speed = pair(atof(line.c_str()), atof(line2.c_str()));

	getline(fin, line);
	getline(fin, line2);
	result.gravitation = pair(atof(line.c_str()), atof(line2.c_str()));

	size_t count;
	getline(fin, line);
	count = atoi(line.c_str());
	for (int i = 0; i < count; i++)
	{
		getline(fin, line);
		getline(fin, line2);
		result.addPoint(pair(atof(line.c_str()), atof(line2.c_str())));
	}

	getline(fin, line);
	result.setAngle(atof(line.c_str()));

	



	result.setAngle(result.getAngle());

	getline(fin, line);
	result.name_sprite = line;

	getline(fin, line);
	result.number_sprite = atof(line.c_str());
	

	fin.close();

	return result;
}

bool elements::addElement(element & new_elem)
{
	if (getByName(new_elem.NameID) != nullptr) return false;
	Array.push_back(new_elem);
	size++;
	first = &Array[0];
	last = &Array[size - 1];
	last->index_elem = size - 1;
	return true;
}

element * elements::getByName(std::string name)
{
	for (element &  x : Array)
	{
		if (x.NameID == name) return &x;
	}
	return nullptr;
}

int elements::IgetByName(std::string name)
{
for (int i =0; i< size; i++)
	{
	if (Array[i].NameID == name) return i;
	}
	return 0;
}

void elements::save_all()
{
	foreach(save);

	std::ofstream fout;
	remove("Obj/mainO.txt");
	fout.open("Obj/mainO.txt");

	fout << size << std::endl;

	for (auto x : Array)
	{
		fout << "Obj/" + x.NameID + ".txt" << std::endl;
	}

	fout.close();
}

void elements::init()
{
	std::ifstream fin("Obj/mainO.txt"); // файл где лежат названия всех файлов объектов
	size_t count;
	std::string nameFile;

	getline(fin, nameFile);

	count = atoi(nameFile.c_str());

	for (int i = 0; i < count; i++)
	{
		getline(fin, nameFile);
		addElement(parseElement(nameFile));
	}

	for (element & x : Array) {
		map::getInstance().fresh(&x);
	}
}

bool elements::next_point(element * &current, bool isDraw, bool isThis, bool Valid, bool tempColis)
{
	if (current == last) return false;
	if (current == nullptr) current = first;
	else
		current++;
	if ((!isDraw || current->isDraw) && (!isThis || current->isThis) && (!Valid || current->Valid) && (!tempColis || current->tempColis)) return true;
	else
		return next_point(current, isDraw, isThis, Valid, tempColis);
}


void elements::foreach(void (*fun)(element &x))
{
	for (element & x : Array)
	{
		fun(x);
	}
}
/*
void elements::foreach(element & h, void(*fun)(element &x, element &y))
{
	for (element & x : Array)
	{
		fun(h, x);
	}
}
*/