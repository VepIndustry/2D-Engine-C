#include "Functions.h"
#include "FunctionHelper.h"
#include "happening.h"
#include <cmath>
# define M_PI           3.14159265358979323846

void shoot(element *, std::string);

void functions::vieww(element * caller, element * second)
{
	view * viewr = view::getInstance();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)/* && !pressL*/)
	{
		pair result = viewr->getCenter_Camera();
		result += pair(-10, 0);
		viewr->setCenter_Camera(result);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)/* && !pressR*/)
	{
		pair result = viewr->getCenter_Camera();
		result += pair(10, 0);
		viewr->setCenter_Camera(result);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) /*&& !pressU*/)
	{
		pair result = viewr->getCenter_Camera();
		result += pair(0, 10);
		viewr->setCenter_Camera(result);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) /*&& !pressD*/)
	{
		pair result = viewr->getCenter_Camera();
		result += pair(0, -10);
		viewr->setCenter_Camera(result);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
	{
		viewr->set_scroll(viewr->get_scroll() + 0.01);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
	{
		viewr->set_scroll(viewr->get_scroll() - 0.01);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		control->move(elems.getByName("mario"), view::getInstance()->getCenter_Camera());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		pair temp = elements::getInstance().getByName("mario")->position;

		viewr->setCenter_Camera(pair(temp.getA(), temp.getB()));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		for (int i = elems.get_size() - 1; i >= 80; i--)
		{
			control->delete_back();
		}
	}
	//caller->speed += result;
}

void functions::move_rocket(element * caller, element * second)
{
	/*pair vect = pair(-200, 200);


	if (clock() - last_shoot > 2 && frame_model > 15) {
		element temp = element();
		temp.recoil = 0.99;
		temp.friction = 1;
		temp.isDraw = 1;
		temp.isThis = 1;
		temp.tempColis = 1;
		temp.Valid = 1;
		temp.NameID = std::to_string(GetTickCount());
		temp.gravitation = pair(0, 0);
		temp.addPoint(pair(0, 0));
		temp.addPoint(pair(16, 0));
		temp.addPoint(pair(16, 16));
		temp.addPoint(pair(0, 16));
		temp.name_sprite = "bull_e";
		temp.condition = clock();
		temp.number_sprite = 0;
		elements::getInstance().addElement(temp);
		element * cur = elements::getInstance().get_last();

		control->move(cur, pair(17000, 17000));
		control->set_speed(cur, vect);
		last_shoot = clock();
	}*/
}

void functions::move_mario(element * caller, element * second) //движение марио
{
	view * viewr = view::getInstance();
	collizioner & colliz = collizioner::getInstance();
	map & mapp = map::getInstance();
	elements & elems = elements::getInstance();

	switch (caller->condition)
	{
	case -1:
		return;
	case 0:
		if (caller->name_sprite == "mario_j")
		{
			int index_elem = -1;

			while (mapp.get_elem(caller, index_elem))
			{
				second = elems.getPoint(index_elem);
				if (second->tempColis && colliz.isCollision(caller, second) && colliz.findLine_fhelp(caller, second) == 2)
				{
					control->size(caller, pair(26, 32));
					caller->name_sprite = "mario";
					caller->number_sprite = 0;
				}
			}
		}
		else
		{
			control->size(caller, pair(26, 32));
			caller->name_sprite = "mario";
			caller->number_sprite = 0;
		}
		break;
	case 1:
		if (caller->name_sprite == "j_b_mario")
		{
			int index_elem = -1;

			while (mapp.get_elem(caller, index_elem))
			{
				second = elems.getPoint(index_elem);
				if (second->tempColis && colliz.isCollision(caller, second) && colliz.findLine_fhelp(caller, second) == 2)
				{
					control->size(caller, pair(31, 63));
					caller->name_sprite = "b_mario";
					caller->number_sprite = 0;
				}
			}
		}
		else
		{
			control->size(caller, pair(31, 63));
			caller->name_sprite = "b_mario";
			caller->number_sprite = 0;
		}
		break;
	case 2:
		control->set_speed(caller, pair(0, 0));
		caller->name_sprite = "tank";
		caller->number_sprite = 0;
		break;
	default:
		break;
	}


	pair result = pair(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)/* && !pressL*/)
	{
		switch (caller->condition) {
		case 0:
			if (caller->speed.getA() > -150) {
				result = pair(-150 - caller->speed.getA(), 0);
			}
			if (caller->name_sprite != "mario_j") {
				control->size(caller, pair(31, 31));
				caller->name_sprite = "left_mario";
				caller->number_sprite = 0;
			}
			break;
		case 1:
			if (caller->speed.getA() > -150) {
				result = pair(-150 - caller->speed.getA(), 0);
			}
			if (caller->name_sprite != "j_b_mario") {
				control->size(caller, pair(31, 63));
				caller->name_sprite = "left_b_mario";
				caller->number_sprite = 0;
			}
			break;
		case 2:
			control->rotate(caller, pair(caller->getAngle() + (5.0 / frame_model), -1));
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)/* && !pressR*/)
	{
		//second->friction = 1;
		switch (caller->condition) {
		case 0:
			if (caller->speed.getA() < 150) {
				result = pair(150 - caller->speed.getA(), 0);
			}
			if (caller->name_sprite != "mario_j") {
				control->size(caller, pair(31, 31));
				caller->name_sprite = "right_mario";
				caller->number_sprite = 0;
			}
			break;
		case 1:
			if (caller->speed.getA() < 150) {
				result = pair(150 - caller->speed.getA(), 0);
			}
			if (caller->name_sprite != "j_b_mario") {
				control->size(caller, pair(31, 63));
				caller->name_sprite = "right_b_mario";
				caller->number_sprite = 0;
			}
			break;
		case 2:
			control->rotate(caller, pair(caller->getAngle() - (5.0 / frame_model), -1));
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)/* && !pressR*/)
	{
		int index = 0;
		int index_elem = 0;
		switch (caller->condition) {
		case 2:
			control->set_speed(caller, pair(300 * -sin(caller->getAngle()), 300 * cos(caller->getAngle())));
			caller->name_sprite = "tank_moving";
			break;
		case 0:
			index_elem = -1;

			while (mapp.get_elem(caller, index_elem))
			{
				second = elems.getPoint(index_elem);
				if (second->tempColis && colliz.isCollision(caller, second) && colliz.findLine_fhelp(caller, second) == 2)
				{
					result += pair(0, 700);
					caller->name_sprite = "mario_j";
					caller->number_sprite = 0;
					control->size(caller, pair(33, 31));
					break;
				}
			}
			break;
		case 1:
			index_elem = -1;

			while (mapp.get_elem(caller, index_elem))
			{
				second = elems.getPoint(index_elem);
				if (second->tempColis && colliz.isCollision(caller, second) && colliz.findLine_fhelp(caller, second) == 2)
				{
					result += pair(0, 700);
					caller->name_sprite = "j_b_mario";
					caller->number_sprite = 0;
					control->size(caller, pair(31, 63));
					break;
				}
			}
			break;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)/* && !pressR*/)
	{
		switch (caller->condition)
		{
		case 2:
			control->set_speed(caller, pair(300 * sin(caller->getAngle()), -300 * cos(caller->getAngle())));
			caller->name_sprite = "tank_moving";
			break;
		}

	}

	functions::control->speed(caller, result);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
	{
		if (caller->condition == 2) {
			if (clock() - last_shoot > 2000) {
				shoot(caller, "bull");
				last_shoot = clock();
			}
		}
	}
}

void functions::kill(element * caller, element * other) {
	elements & elems = elements::getInstance();

	caller->condition--;
	if (caller->condition == 0)
	{
		caller->isThis = false;
		caller->tempColis = false;
		caller->Valid = false;
		caller->name_sprite = "babah";
		caller->number_sprite = 0;
		control->size(caller, pair(72, 66));
	}
}

void functions::kill_m(element * caller, element * other)
{
	collizioner & colliz = collizioner::getInstance();
	map & mapp = map::getInstance();
	elements & elems = elements::getInstance();

	int index_elem = -1;
	element* second;

	while (mapp.get_elem(caller, index_elem))
	{
		second = elems.getPoint(index_elem);
		if (second->tempColis && colliz.isCollision(caller, second) && second->name_sprite == "bull_e")
		{
			life--;
			if (life == 0)
			{
				element * temp = elems.getByName("tank_1");
				temp->isDraw = true;
				temp->isThis = true;
				temp->tempColis = true;
				temp->Valid = true;
				control->move(temp, pair(4730, 3530));
				control->set_speed(temp, pair(0, 0));
				control->rotate(temp, pair(0, -1));
				control->size(temp, pair(64, 77));
				temp->name_sprite = "tank_enemy";
				temp->number_sprite = 0;
				temp->condition = 3;


				temp = elems.getByName("tank_2");
				temp->isDraw = true;
				temp->isThis = true;
				temp->tempColis = true;
				temp->Valid = true;
				control->move(temp, pair(3530, 4830));
				control->set_speed(temp, pair(0, 0));
				control->rotate(temp, pair(0, -1));
				control->size(temp, pair(64, 77));
				temp->name_sprite = "tank_enemy";
				temp->number_sprite = 0;
				temp->condition = 3;


				temp = elems.getByName("tank_3");
				temp->isDraw = true;
				temp->isThis = true;
				temp->tempColis = true;
				temp->Valid = true;
				control->move(temp, pair(4330, 4730));
				control->set_speed(temp, pair(0, 0));
				control->rotate(temp, pair(0, -1));
				control->size(temp, pair(64, 77));
				temp->name_sprite = "tank_enemy";
				temp->number_sprite = 0;
				temp->condition = 3;

				control->move(caller, pair(3150, 4050));
				life = 3;
				control->set_speed(caller, pair(0, 0));
			}
			break;
		}
	}
}

void functions::del_bull(element * caller, element * second) {
	elems.foreach([](element & x) {
		if ((x.name_sprite == "bull" || x.name_sprite == "bull_e") && (clock() - x.condition > 10000))
		{
			x.deactive();
		}
	});
}

void functions::invis(element * caller, element * second) //выбивание монеты
{
	if (second->name_sprite == "q_block" && collizioner::getInstance().findLine_fhelp(caller, second) == 0)
	{
		second->name_sprite = "e_block";
		element * coin = elems.getByName("coin_1");
		control->move(coin, second->position + pair(0, 50));
		pair speed = pair(0, 100);
		control->speed(coin, speed - coin->speed);
	
		control->live_v(coin);
		control->live_d(coin);
		control->live_t(coin);
	}
}

void functions::kick_muth(element * caller, element * second) //выбивание гриба
{
	if (second->name_sprite == "q_block" && collizioner::getInstance().findLine_fhelp(caller, second) == 0)
	{
		second->name_sprite = "e_block";
		element * coin = elems.getByName("muth_1");
		control->move(coin, second->position + pair(0, 33));
		pair speed = pair(40, 0);
		control->speed(coin, speed - coin->speed);
		control->live_d(coin);
		control->live_t(coin);
		control->live_v(coin);
		control->live_c(coin);
	}
}

void functions::meet_muth(element * caller, element * second)
{
	up_mario(caller);
	second->deactive();
}

void functions::grav_to_mouse(element * caller, element * second)
{
	view * viewer = view::getInstance();
	pair center_mouse =  viewer->get_size();
	center_mouse.multiply(-0.5);
	center_mouse += viewer->get_mouse();
	center_mouse.multiply(1.0 / viewer->get_scroll());
	center_mouse += viewer->getCenter_Camera();
	control->move(caller, center_mouse);
	//caller->gravitation = center_mouse - caller->position;
	//std::cout << center_mouse.getA() << "   " << center_mouse.getB() << std::endl;
	//caller->gravitation.multiply(caller->Massa);
}

void functions::time_for_mouse(element * caller, element * second)
{
	if (begin > 0 && clock() - begin > 10000) {
		int index = getByName("grav_to_mouse");
		arr[index] = &functions::grav_to_mouse;

		map & mapp = map::getInstance();

		mapp.set_size_cell(pair(800, 800));

		for (int i = 0; i < elems.get_size(); i++) {
			elems.getPoint(i)->cells = std::vector<pair>();
			mapp.fresh(elems.getPoint(i));
		}
		begin = -1;
	}
	else if (begin == 0) begin = clock();
}

void functions::move_to_cosmic(element * caller, element * second)
{
	for (int i = elems.get_size() - 1; i >= 80; i--)
	{
		control->delete_back();
	}

	for (int i = 0; i < 62; i++) {
		if (elems[i].NameID != "mario" && elems.getPoint(i)->NameID != "floar"			
			&& elems.getPoint(i)->NameID != "field") {
			elems.getPoint(i)->deactive();
		}
		else if (elems[i].NameID == "mario"){
			control->move(elems.getPoint(i), pair(18000, 18000));
			elems.getPoint(i)->condition = 2;
		}
	}	

	element * cosmic_item = elems.getByName("cosmic_field");
	control->live_v(cosmic_item);

	for (int i = 62; i < elems.get_size(); i++) {
		cosmic_item = elems.getPoint(i);
		control->live_c(cosmic_item);
		control->live_t(cosmic_item);
		control->live_d(cosmic_item);
		control->live_v(cosmic_item);
	}
}

void functions::mutant_tank(element * caller, element * second)
{
	if (second->name_sprite == "q_block" && collizioner::getInstance().findLine_fhelp(caller, second) == 0)
	{
		control->size(caller, pair(64, 77));
		second->deactive();
		caller->gravitation = pair(0, 0);
		caller->name_sprite = "tank";
		caller->number_sprite = 0;
		caller->condition = 2;
		
		elems.getByName("tank_1")->condition = 3;
		elems.getByName("tank_2")->condition = 3;
		elems.getByName("tank_3")->condition = 3;

		for (int i = 0; i < 28; i++) {
			if (elems.getPoint(i)->NameID != "mario"
				&& elems.getPoint(i)->NameID != "floar"
				&& elems.getPoint(i)->NameID != "floar_2"
				&& elems.getPoint(i)->NameID != "field")
				elems.getPoint(i)->deactive();
		}
	}
}


void functions::del_object(element * caller, element * second) //исчезновение объекта
{
	caller->deactive();
}

void functions::close_door(element * caller, element * second)
{
	element * temp = elems.getByName("floar_2");
	if (temp->getAngle() > (-M_PI / 2 + 0.001))
	{
		control->rotate(temp, pair(temp->getAngle() - 0.01, 2));
	}
	else {
		temp->Valid = false;
	}
}

void functions::open_door(element * caller, element * second)
{
	if (elems.getByName("tank_1")->condition == 0 &&
		elems.getByName("tank_2")->condition == 0 &&
		elems.getByName("tank_3")->condition == 0) {
		element * temp = elements::getInstance().getByName("wall_4");
		if (temp->getAngle() < (M_PI / 10))
		{
			control->rotate(temp, pair(temp->getAngle() + 0.001, 3));
		}
	}
}

void shoot(element * temp_tank, std::string n_s) {
	controller * control = controller::getInstance();

	element temp = element();
	temp.recoil = 0.99;
	temp.friction = 1;
	temp.isDraw = 1;
	temp.isThis = 1;
	temp.tempColis = 1;
	temp.Valid = 1;
	temp.NameID = std::to_string(GetTickCount());
	temp.gravitation = pair(0, 0);
	temp.addPoint(pair(0, 0));
	temp.addPoint(pair(16, 0));
	temp.addPoint(pair(16, 16));
	temp.addPoint(pair(0, 16));
	temp.name_sprite = n_s;
	temp.condition = clock();
	temp.number_sprite = 0;
	elements::getInstance().addElement(temp);
	element * cur = elements::getInstance().get_last();
	if (n_s == "bull") {

		happening hap = happening(elements::getInstance().IgetByName("tank_1"), cur->index_elem, "kill");
		fHelper::getInstance().addHappen(hap);

		happening hap_2 = happening(elements::getInstance().IgetByName("tank_2"), cur->index_elem, "kill");
		fHelper::getInstance().addHappen(hap_2);

		happening hap_3 = happening(elements::getInstance().IgetByName("tank_3"), cur->index_elem, "kill");
		fHelper::getInstance().addHappen(hap_3);
	}
	else
	{
		happening hap = happening(elements::getInstance().IgetByName("mario"), cur->index_elem, "kill_m");
		fHelper::getInstance().addHappen(hap);
	}

	control->move(cur, pair(50 * -sin(temp_tank->getAngle()), 50 * cos(temp_tank->getAngle())) + temp_tank->position);
	control->set_speed(cur, pair(700 * -sin(temp_tank->getAngle()), 700 * cos(temp_tank->getAngle())));
}



void functions::shoot_1(element * caller, element * second)
{
	element * temp_tank = elems.getByName("tank_1");
	if (temp_tank->Valid) {
		pair vect = caller->position - temp_tank->position;
		control->rotate(temp_tank, pair(-M_PI / 2 + acos(vect.getA() / vect.length(pair(0, 0))) * (vect.getB() < 0 ? -1 : 1), -1));
		control->set_speed(temp_tank, pair(100 * cos(caller->getAngle()), 100 * sin(caller->getAngle())));
		if (clock() - last_shoot_1 > 800) {
			shoot(temp_tank, "bull_e");
			last_shoot_1 = clock();
		}
	}
}

void functions::shoot_2(element * caller, element * second)
{
	element * temp_tank = elems.getByName("tank_2");
	if (temp_tank->Valid) {
		pair vect = caller->position - temp_tank->position;
		control->rotate(temp_tank, pair(-M_PI / 2 + acos(vect.getA() / vect.length(pair(0, 0))) * (vect.getB() < 0 ? -1 : 1), -1));
		if (clock() - last_shoot_2 > 800) {
			shoot(temp_tank, "bull_e");
			last_shoot_2 = clock();
		}
	}
}

void functions::shoot_3(element * caller, element * second)
{
	element * temp_tank = elems.getByName("tank_3");
	if (temp_tank->Valid) {
		pair vect = caller->position - temp_tank->position;
		control->rotate(temp_tank, pair(-M_PI / 2 + acos(vect.getA() / vect.length(pair(0, 0))) * (vect.getB() < 0 ? -1 : 1), -1));
		//control->set_speed(temp_tank, pair(100 * cos(temp_tank->getAngle()), 100 * sin(temp_tank->getAngle())));
		if (clock() - last_shoot_3 > 800) {
			shoot(temp_tank, "bull_e");
			last_shoot_3 = clock();
		}
	}
}

void functions::stop_plat(element * caller, element * second)
{
	caller->Valid = false;
	caller->isThis = false;
	control->set_speed(caller, pair(0, 0));
	control->move(caller, pair(caller->position.getA() - 0.1, 3875));
	element * mario = elems.getByName("mario");
	control->set_speed(mario, pair(0, 0));
	mario->gravitation = pair(0, -1400);
	control->move(mario, pair(mario->position.getA(), mario->lu_square.getB() - mario->rd_square.getB() + caller->lu_square.getB()));
	control->live_c(mario);
	control->live_v(mario);
}



void functions::end_tank(element * caller, element * second)
{
	element * temp = elems.getByName("wall_4");
	if (temp->getAngle() > 0)
	{
		control->rotate(temp, pair(temp->getAngle() - 0.001, 3));
	}
	if (count_bull == 0) {
		elements::getInstance().getByName("tank_field_last")->Valid = false;
		elements::getInstance().getByName("tank_field")->Valid = false;
		elements::getInstance().getByName("tank_field_1")->Valid = false;
		elements::getInstance().getByName("tank_field_2")->Valid = false;
		elements::getInstance().getByName("tank_field_3")->Valid = false;

		for (int i = elems.get_size() - 1; i >= 80; i--)
		{
			control->delete_back();
		}
		count_bull = 1;
	}
	else {

		pair vect = pair(-500, 500);

		if (clock() - last_shoot > 20 && frame_model > 40) {
			element temp = element();
			temp.recoil = 0.99;
			temp.friction = 1;
			temp.isDraw = 1;
			temp.isThis = 1;
			temp.tempColis = 1;
			temp.Valid = 1;
			temp.NameID = std::to_string(GetTickCount());
			temp.gravitation = pair(0, 0);
			temp.addPoint(pair(4800, 3300));
			temp.addPoint(pair(4816, 3300));
			temp.addPoint(pair(4816, 3316));
			temp.addPoint(pair(4800, 3316));
			temp.name_sprite = "bull_e";
			temp.condition = clock();
			temp.number_sprite = 0;
			elements::getInstance().addElement(temp);
			element * cur = elements::getInstance().get_last();

			//control->move(cur, pair(4800, 3300));
			control->set_speed(cur, vect);
			last_shoot = clock();
		}
	}
}

void functions::grav(element * caller, element * second)
{
	elements & elems = elements::getInstance();
	//pair temp_1 = elems[pl_index_1].position - caller->position;
	//pair temp_2 = elems[pl_index_2].position - caller->position;
	pair temp_3 = elems[pl_index_3].position - caller->position;

	//temp_3 += temp_1 + temp_2;
	caller->gravitation = temp_3;
	caller->gravitation.multiply(caller->Massa);
}





void functions::up_up_mario(element * caller, element * second)
{
	if (collizioner::getInstance().findLine_fhelp(caller, second) == 2) {
		elements & elems = elements::getInstance();
		if (!elems.getByName("enemy_1")->isThis && !elems.getByName("enemy_2")->isThis) {
			control->set_speed(caller, pair(0, 1000));
			control->speed(second, pair(0, 1000));
			caller->gravitation = pair(0, 0);
			control->live_t(second);
			caller->tempColis = false;
			caller->Valid = false;
		}
	}
}


void functions::meet_enemy(element * caller, element * second)
{
	if (collizioner::getInstance().findLine_fhelp(caller, second) == 2) {
		second->deactive();
	}
	else
		dead_mario(caller);
}

void functions::dead_mario(element * caller) // смерть марио
{

	if (caller->condition == 0) {
		control->speed(caller, pair(-caller->speed.getA(), 700));
		caller->name_sprite = "dead_m";
		caller->tempColis = false;
		caller->Valid = false;
		caller->condition = -1;
	}
	else
	{
		caller->condition = 0;
		control->size(caller, pair(26, 32));
		caller->name_sprite = "mario";
		caller->number_sprite = 0;
		control->move(caller, pair(100, 200));
	}

}

void functions::up_mario(element * caller)
{
	control->size(caller, pair(31, 63));

	caller->name_sprite = "b_mario";
	caller->number_sprite = 0;
	caller->condition = 1;
}



void functions::call(int index, element* caller, element* second, int frame)
{
	frame_model = frame;
	if (index < arr.size())
		(this->*(arr[index]))(caller, second);
}
