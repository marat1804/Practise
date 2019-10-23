#include "Circuit_Board.h"

namespace Prog {
	Circuit_Board::Circuit_Board(const Circuit_Board & ob): SZ(ob.SZ), n(ob.n), arr(new contact[SZ]) {
		if (n) {
			arr = new contact[SZ];

			for (int i = 0; i < n; ++i) {
				arr[i] =  ob.arr[i];
			}
		}
	}

	Circuit_Board::Circuit_Board(Circuit_Board &&ob) : n(ob.n), SZ(ob.SZ), arr(ob.arr)
	{
		ob.n = 0;
		ob.arr = nullptr;
	}

	Circuit_Board::Circuit_Board(contact & s): n(0), SZ(QUOTA), arr(new contact[QUOTA])
	{
		if (s.type == 1 || s.type == 0)
			this->add_contact(s);
		else
			throw std::exception("Invalid type");
	}

	std::ostream& Circuit_Board::print(std::ostream& s) const
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

	std::istream& Circuit_Board::input(std::istream& s)
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

	void Circuit_Board::add_contact(contact &s)
	{
		if (n >= SZ) {
			SZ += QUOTA;
			contact *old = arr;
			arr = new contact[SZ];
			for (int i = 0; i < n; ++i)
				arr[i] = old[i];
			delete[] old;
		}
		if (s.type != 1 && s.type != 0)
			throw std::exception("Invalid type!");
		arr[n] = s;
		n += 1;
	}

	void Circuit_Board::add_contact(contact &s, int disp)
	{
		if (n >= SZ) {
			SZ += QUOTA;
			contact *old = arr;
			arr = new contact[SZ];
			for (int i = 0; i < n; ++i)
				arr[i] = old[i];
			delete[] old;
		}
		if (s.type != 1 && s.type != 0)
			throw std::exception("Invalid type!");
		arr[n] = s;
		if (arr[n].connected_contact != -1)
			arr[n].connected_contact += disp;
		n += 1;
	}

	void Circuit_Board::add_contact(int type, int x, int y)
	{
		if (n >= SZ) {
			SZ += QUOTA;
			contact *old = arr;
			arr = new contact[SZ];
			for (int i = 0; i < n; ++i)
				arr[i] = old[i];
			delete[] old;
		}
		if (type != 1 && type != 0)
			throw std::exception("Invalid type!");
		contact el(type, x, y);
		arr[n] = el;
		n += 1;
	}

	bool Circuit_Board::check_connetcion(int id, int to) const
	{
		if (n == 0)
			throw std::exception("The circuit is empty");
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
			if (arr[from].connected_contact == -1 && arr[to].connected_contact == -1) {
				arr[from].connected_contact = to;
				arr[to].connected_contact = from;
			}
			else
				throw std::exception("One contact already has a connection");
		}
		else
			throw std::exception("They're the same type");
	}

	void Circuit_Board::get_group(Circuit_Board& board1, int type_) const
	{
		if (this->n == 0)
			throw std::exception("The circuit is empty!");
		if (type_ != 1 && type_ != 0)
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

	Circuit_Board & Circuit_Board::operator+(const Circuit_Board &c)
	{
		int i, disp = n;
		for (i = 0; i < c.n; ++i) {
			this->add_contact(c.arr[i], disp);
		}
		return *this;
	}

	Circuit_Board & Circuit_Board::operator+=(const Circuit_Board &s)
	{
		int i, disp = n;
		for (i = 0; i < s.n; ++i) {
			this->add_contact(s.arr[i], disp);
		}
		return *this;
	}

	const double & Circuit_Board::operator()(int from, int to)
	{
		return this->route_length(from, to);
	}

	contact & Circuit_Board::get_contact(int id)
	{
		if (id<0 || id >n - 1)
			throw std::exception("Invalid index");
		else
			return arr[id];
	}


	Circuit_Board & Circuit_Board::operator-(const Circuit_Board &c)
	{
		for (int j = 0; j < c.n; ++j) {
			for (int i = 0; i < n; ++i) {
				if (c.arr[j].type == arr[i].type && c.arr[j].x == arr[i].x && c.arr[j].y == arr[i].y)
					this->delete_contact(i);
			}
		}
		return *this;
	}

	void Circuit_Board::delete_contact(int item)
	{
		int i;
		if (n == 0) {
			throw std::exception("The circuit is empty");
		}
		if (item > n - 1 or item < 0) {
			throw std::exception("Invalid ID");
		}
		else {
			i = arr[item].connected_contact;
			if (i != -1) {
				arr[i].connected_contact = -1;
			}
			if (n != 1 && item != n - 1) {
				arr[item] = arr[n - 1];
				i = arr[item].connected_contact;
				if(i=!-1)
					arr[i].connected_contact = item;
			}
			n--;
		}
	}

	Circuit_Board & Circuit_Board::operator-=(const Circuit_Board &c)
	{
		for (int j = 0; j < c.n; ++j) {
			for (int i = 0; i < n; ++i) {
				if (c.arr[j].type == arr[i].type && c.arr[j].x == arr[i].x && c.arr[j].y == arr[i].y)
					this->delete_contact(i);
			}
		}
		return *this;
	}

	Circuit_Board & Circuit_Board::operator=(const Circuit_Board &ob)
	{
		if (this != &ob) {
			n = ob.n;
			SZ = ob.SZ;
			delete[] arr;
			arr = new contact[SZ];;
			for (int i = 0; i < n; ++i)
				arr[i] = ob.arr[i];
		}
		return *this;
	}

	Circuit_Board & Circuit_Board::operator=(Circuit_Board &&ob)
	{
		int tmp = n;
		n = ob.n;
		ob.n = tmp;
		tmp = SZ;
		SZ = ob.SZ;
		ob.SZ = tmp;
		contact *ptr = arr;
		arr = ob.arr;
		ob.arr = ptr;
		return *this;
	}

	std::ostream& operator<<(std::ostream& s, const Circuit_Board& c)
	{
		if (c.n != 0) {
			s << "There are " << c.n << " contacts" << std::endl;
			for (int i = 0; i < c.n; i++) {
				s << i << "(" << c.arr[i].x << ", " << c.arr[i].y << ")-" << c.arr[i].type << "  connected with " << c.arr[i].connected_contact << std::endl; ;
			}
		}
		else
			s << "The circuit is empty!";
		s << std::endl << std::endl;
		return s;
	}
	std::istream & operator>>(std::istream &s, Circuit_Board &c)
	{
		int type, x, y;
		s >> type >> x >> y;
		if (s.good()) {
			if (type == 1 or type == 0) {
				contact c1(type, x, y);
				c += c1;
			}
			else
				s.setstate(std::ios::failbit);
		}
		return s;
	}



}