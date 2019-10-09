#include "stdafx.h"
#include "Circuit_Board.h"

namespace Prog {
	std::ostream & Circuit_Board::print(std::ostream &s) const
	{
		if (n != 0) {
			s << "There are " << n << " contacts" << std::endl;
			for (int i = 0; i < n; i++) {
				s << i << "(" << arr[i].x << ", " << arr[i].y << ")-" << arr[i].type << "  connected with " << arr[i].connected_contact << std::endl; ;
			}
		}
		else
			s << "The circuit is empty!";
		return s;
	}

	std::istream & Circuit_Board::input(std::istream &s)
	{
		int type, x, y;
		s >> type >> x >> y;
		if (!s.good()) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			throw std::exception("Invalid input");
		}
		this->add_contact(type, x, y);
		return s;
	}

	void Circuit_Board::add_contact(contact s)
	{
		if (n == SZ) {
			throw std::exception("The circuit is full!");
		}
		if (s.type != 1 and s.type != 0)
			throw std::exception("Invalid type!");
		arr[n] = s;
		n += 1;
	}

	void Circuit_Board::add_contact(int type, int x, int y)
	{
		if (n == SZ) {
			throw std::exception("The circuit is full!");
		}
		if (type != 1 and type != 0)
			throw std::exception("Invalid type!");
		contact el(type, x, y);
		arr[n] = el;
		n += 1;
	}

	bool Circuit_Board::check_connetcion(int id, int to) const
	{
		if (id >= n or id < 0 or to >= n or to < 0)
			throw std::exception("Invalid index");
		if (arr[to].type != arr[id].type)
			return true;
		else
			return false;
	}

	void Circuit_Board::add_connection(int from, int to)
	{
		if (check_connetcion(from, to)) {
			if (arr[from].connected_contact == -1 and arr[to].connected_contact == -1) {
				arr[from].connected_contact = to;
				arr[to].connected_contact = from;
			}
			else
				throw std::exception("One contact already has a connection");
		}
		else
			throw std::exception("They're the same type");
	}

	void Circuit_Board::get_group(Circuit_Board &board1, int type_) const
	{
		if (this->n == 0)
			throw std::exception("The circuit is empty!");
		if (type_ != 1 and type_ != 0)
			throw std::exception("Invalid type");
		else {
			for (int i = 0; i < n; i++) {
				if (this->arr[i].type == type_) {
					board1.add_contact(this->arr[i]);
				}
			}
		}
	
	}


	double Circuit_Board::route_length(int from, int to) const
	{
		double dist = 0;
		if (check_connetcion(from, to)) {
			dist = pow(arr[from].x - arr[to].x, 2) + pow(arr[from].y - arr[to].y, 2);
		}
		else
			throw std::exception("There're the same type");
		return sqrt(dist);
	}
}