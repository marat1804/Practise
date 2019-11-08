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
		if (s.type == 1 or s.type == 0)
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
		if (s.x<0 || s.x>x || s.y<0 || s.y>y) {
			throw std::exception("Coordinates are out of circuit! Coordinates must be from 0 to 10");
		}
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
		if (s.x<0 || s.x>x || s.y<0 || s.y>y)
			throw std::exception("Coordinates are out of circuit! Coordinates must be from 0 to 10");
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
		if (x<0 || x>this->x || y<0 || y>this->y)
			throw std::exception("Coordinates are out of circuit! Coordinates must be from 0 to 10");
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
				if(i!=-1)
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

	bool lay_on_line(point p1,  Line  l) {
		if (l.n == 2) {
			double d1 = (double(p1.x - l.points[0].x)) / (l.points[1].x - l.points[0].x);
			double d2 = (double( p1.y - l.points[0].y)) / (l.points[1].y - l.points[0].y);
			return d1 == d2 && d1 >= 0 && d1 <=1 ;
		}
		else {
			for (int i = 0; i < l.n-1; ++i) {
				if (double((p1.x - l.points[i].x)) / (l.points[i + 1].x - l.points[i].x) == double((p1.y - l.points[i].y)) / (l.points[i + 1].y - l.points[i].y)) {
					return true;
				}
			}
		}
		return false;
	}

	bool cross_lines(point p1, point p2, Line l) {
		if (l.n != 2)
			for (int j = 0; j < l.n - 1; ++j) {
				if (intersect(p1, p2, l.points[j], l.points[j + 1])) {
					return true;
				}
			}
		else {
			if (intersect(p1, p2, l.points[0], l.points[1]))
				return true;
		}
		return false;
	}

	bool route_builing(point p1, point p2, Line *& routes, int lines, int MAX_x, int MAX_y) {
		Line l;
		int tmp;
		if (p1.x > p2.x) {
			tmp = p1.x;
			p1.x = p2.x;
			p2.x = tmp;
			tmp = p1.y;
			p1.y = p2.y;
			p2.y = tmp;
		}
		l.points[0] = p1, l.points[1] = p2;
		int fl = 1, i=0;

		while(i<lines && fl) { //пересекаются ли просто линии
			if (cross_lines(p1, p2, routes[i]))
				fl = 0;
			i++;
		}	
		i--;

		if (fl) {
			routes[lines] = l;
			return true;
		}

		int j = i;
		while (i < lines) {
			if (lay_on_line(p1, routes[i]) || lay_on_line(p2, routes[i])) {
				//std::cout << routes[i].points[0].x << " " << routes[i].points[0].y << std::endl;
				return false;
			}
			i++;
		}
		if (case_1a(p1, p2, routes, lines, MAX_x, MAX_y, j))
			return true;
		else {
			if (case_1b(p1, p2, routes, lines, MAX_x, MAX_y, j))
				return true;
			else {
				if (case_2a(p1, p2, routes, lines, MAX_x, MAX_y, j))
					return true;
				else {
					if (case_2b(p1, p2, routes, lines, MAX_x, MAX_y, j))
						return true;
					else return false;
				}
			}
		}
	}

	bool case_1a(point p1, point p2, Line *& routes, int lines, int MAX_x, int MAX_y, int i1) {
		point temp;
		point c1 = routes[i1].points[0], c2 = routes[i1].points[1];
		int i = c2.x, j;
		int fl1 = 1, fl2 = 1;
		while(i<MAX_x && fl1){
			for (j = c2.y + 1; j < MAX_y; ++j) {
				temp.x = i;
				temp.y = j;
				if (!cross_lines(p1, temp, routes[i1]) && !cross_lines(temp, p2, routes[i1])) {
					fl1 = 0;
					break;
				}

			}
			i++;
		}
		i = 0;
		if (!fl1) {
			fl2 = 1;
			while (i < lines && fl2) { //пересекаются ли просто линии
				if (cross_lines(p1, temp, routes[i]) || cross_lines(temp, p2, routes[i]))
					fl2 = 0;
				i++;
			}
		}
		if (!fl1 && fl2) {
			routes[lines].n = 3;
			routes[lines].points[0] = p1;
			routes[lines].points[1] = temp;
			routes[lines].points[2] = p2;
			return true;
		}
		else {
				return false;
		}
	}

	bool case_1b(point p1, point p2, Line *& routes, int lines, int MAX_x, int MAX_y, int i1) {
		point temp;
		point c1 = routes[i1].points[0], c2 = routes[i1].points[1];
		int i = c2.x, j;
		int fl1 = 1, fl2 = 1;
		while (i < MAX_x && fl1) {
			for (j = c2.y - 1; j > 0; --j) {
				temp.x = i;
				temp.y = j;
				if (!cross_lines(p1, temp, routes[i1]) && !cross_lines(temp, p2, routes[i1])) {
					fl1 = 0;
					break;
				}

			}
			i++;
		}
		i = 0;
		if (!fl1) {
			fl2 = 1;
			while (i < lines && fl2) { //пересекаются ли просто линии
				if (cross_lines(p1, temp, routes[i]) || cross_lines(temp, p2, routes[i]))
					fl2 = 0;
				i++;
			}
		}
		if (!fl1 && fl2) {
			routes[lines].n = 3;
			routes[lines].points[0] = p1;
			routes[lines].points[1] = temp;
			routes[lines].points[2] = p2;
			return true;
		}
		else {
				return false;
		}
	}

	bool case_2a(point p1, point p2, Line *& routes, int lines, int MAX_x, int MAX_y, int i1) {
		point temp;
		point c1 = routes[i1].points[0], c2 = routes[i1].points[1];
		int i = c1.x, j;
		int fl1 = 1, fl2 = 1;
		while (i > 0 && fl1) {
			for (j = c1.y + 1; j < MAX_y; ++j) {
				temp.x = i;
				temp.y = j;
				if (!cross_lines(p1, temp, routes[i1]) && !cross_lines(temp, p2, routes[i1])) {
					fl1 = 0;
					break;
				}

			}
			i--;
		}
		i = 0;
		if (!fl1) {
			fl2 = 1;
			while (i < lines && fl2) { //пересекаются ли просто линии
				if (cross_lines(p1, temp, routes[i]) || cross_lines(temp, p2, routes[i])) {
					fl2 = 0;
				}
				i++;
			}
		}
		if (!fl1 && fl2) {
			routes[lines].n = 3;
			routes[lines].points[0] = p1;
			routes[lines].points[1] = temp;
			routes[lines].points[2] = p2;
			return true;
		}
		else {
				return false;
		}
	}

	bool case_2b(point p1, point p2, Line *& routes, int lines, int MAX_x, int MAX_y, int i1) {
		point temp;
		point c1 = routes[i1].points[0], c2 = routes[i1].points[1];
		int i = c1.x, j;
		int fl1 = 1, fl2 = 1;
		while (i > 0  && fl1) {
			for (j = c1.y - 1; j > 0; --j) {
				temp.x = i;
				temp.y = j;
				if (!cross_lines(p1, temp, routes[i1]) && !cross_lines(temp, p2, routes[i1])) {
					fl1 = 0;
					break;
				}

			}
			i--;
		}
		i = 0;
		if (!fl1) {
			fl2 = 1;
			while (i < lines && fl2) { //пересекаются ли просто линии
				if (cross_lines(p1, temp, routes[i]) || cross_lines(temp, p2, routes[i]))
					fl2 = 0;
				i++;
			}
		}
		if (!fl1 && fl2) {
			routes[lines].n = 3;
			routes[lines].points[0] = p1;
			routes[lines].points[1] = temp;
			routes[lines].points[2] = p2;
			return true;
		}
		else {
				return false;
		}
	}

	void Circuit_Board::tracing()
	{
		contact c1, c2, c3, c4;
		Line l1, l2;
		point p1, p2;
		if (n == 0) {
			throw std::exception("The circuit is empty");
		}
		if (routes != nullptr) {
			delete[] routes;
			routes = nullptr;
			for (int i = 0; i < n; ++i)
				arr[i].traced = 0;
			lines = 0;
		}
		routes = new Line[SZ / 2];
		for (int i = 0; i < n; ++i) {
			if (arr[i].connected_contact == -1 || arr[i].traced == 1)
				continue;
			c1 = arr[i];
			c2 = arr[c1.connected_contact];
			p1.x = c1.x, p1.y = c1.y;
			p2.y = c2.y, p2.x = c2.x;
			if (route_builing(p1, p2, routes, lines,x, y)) {
				arr[i].traced = 1; arr[c1.connected_contact].traced = 1;
				lines++;
			}
		}
	}

	std::ostream & Circuit_Board::show_trc(std::ostream &s) const
	{
		s << "Traced contacts" << std::endl;
		double dist;
		for (int i = 0; i < n; ++i) {
			if (arr[i].traced == 1)
				s << "(" << arr[i].x << "," << arr[i].y << ")" << std::endl;
		}
		for (int i = 0; i < lines; ++i) {
			for (int j = 0; j < routes[i].n; j++)
				s << "(" << routes[i].points[j].x << "," << routes[i].points[j].y << "), ";
			if (routes[i].n == 2) {
				dist = pow(routes[i].points[0].x - routes[i].points[1].x, 2) + pow(routes[i].points[0].y - routes[i].points[1].y, 2);
				dist = sqrt(dist);
			}
			else {
				dist = pow(routes[i].points[0].x - routes[i].points[1].x, 2) + pow(routes[i].points[0].y - routes[i].points[1].y, 2);
				dist = sqrt(dist);
				dist = dist + sqrt(pow(routes[i].points[1].x - routes[i].points[2].x, 2) + pow(routes[i].points[1].y - routes[i].points[2].y, 2));
			}
			s << dist;
			s << std::endl;
		}
		s << std::endl << std::endl;
		return s;
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
	
	int area(point a, point b, point c) {
		return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
	}

	bool intersect_1(int a, int b, int c, int d) {
		int buf;
		if (a > b) {
			buf = a;
			a = b;
			b = buf;
		}
		if (c > d) {
			buf = c;
			c = d;
			d = buf;
		}
		int max =a>c ?a :c , min = b<d?b:d;
		return max <= min;
	}

	bool intersect(point a, point b, point c, point d) {
		return intersect_1(a.x, b.x, c.x, d.x) &&
			intersect_1(a.y, b.y, c.y, d.y) &&
			area(a, b, c) * area(a, b, d) <= 0 &&
			area(c, d, a)*area(c, d, b) <= 0;
	}
}