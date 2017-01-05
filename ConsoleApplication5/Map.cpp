#include "Map.h"

bool map::get_elem(element * order, int & point)
{
	if (order->lu_square.getA() < LU.getA() || order->rd_square.getB() < RD.getB()) {
		order->deactive();
		return false;
	}
	if (order->lu_square.getB() > LU.getB() || order->rd_square.getA() > RD.getA()) {
		order->deactive();
		return false;
	}
	if (point == -1) {
		lists.clear();
		for (pair x : order->cells) {
			cell * c_current = &cells[x.getA() + x.getB() * size.getA()];

			for (int i = 0; i < c_current->size; i++)
			{
				lists.push_back(c_current->get_point(i));
			}
		}
	}

	if (lists.size() == 0) {
		return false;
	}

	point = lists[lists.size() - 1];
	lists.pop_back();
	return true;
}

void map::fresh(element * order)
{
	if (order->lu_square.getA() < LU.getA() || order->rd_square.getB() < RD.getB()) {
		//order->deactive();
		return;
	}
	if (order->lu_square.getB() > LU.getB() || order->rd_square.getA() > RD.getA()) {
		//order->deactive();
		return;
	}

	for (pair x : order->cells) {
		cells[x.getA() + x.getB() * size.getA()].remove(order->index_elem);
	}

	order->cells.clear();

	int i_to = order->rd_square.getA() / size_cell.getA();
	int j_to = order->lu_square.getB() / size_cell.getB();
	pair temp = pair(0, 0);

	for (int i = order->lu_square.getA() / size_cell.getA(); i <= i_to; i++)
	{
		for (int j = order->rd_square.getB() / size_cell.getB(); j <= j_to; j++)
		{
			temp = pair(i, j);
			order->cells.push_back(temp);
			cells[i + j * size.getA()].add(order->index_elem);
		}
	}
}

void map::remove(element * order)
{
	for (pair x : order->cells)
	{
		cell * c_current = &cells[x.getA() + x.getB() * size.getA()];
		c_current->remove(order->index_elem);
	}
}