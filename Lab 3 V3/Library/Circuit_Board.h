#ifndef CLASS_2H
#define CLASS_2H
#include <iostream>
namespace Prog {
	struct contact {
		int type; //1 - in, 0 - out
		int x, y;
		int connected_contact = -1;
		contact(int type_0 = 0, int x_0 = 0, int y_0 = 0) : type(type_0), x(x_0), y(y_0) {};
	};

	class Circuit_Board {
	private:
		static const int QUOTA = 5;
		int SZ;
		int n;
		contact* arr;

		void add_contact(contact &, int);
	public:
		Circuit_Board() : n(0), SZ(QUOTA), arr(new contact[QUOTA]) { };
		Circuit_Board(const Circuit_Board &ob);
		Circuit_Board(Circuit_Board&&);
		Circuit_Board(contact &s);
		~Circuit_Board() { if (arr != nullptr){ delete[] arr; n = 0; } };
		std::ostream& print(std::ostream&) const;
		std::istream& input(std::istream&);
		void add_contact(contact &);
		void add_contact(int type, int x, int y);
		bool check_connetcion(int, int) const;
		void add_connection(int from, int to);
		void get_group(Circuit_Board&, int) const;
		double route_length(int from, int to) const;
		friend std::ostream& operator<< (std::ostream&, const Circuit_Board&);
		friend std::istream& operator>> (std::istream&, Circuit_Board &);
		Circuit_Board & operator + (const Circuit_Board &);
		Circuit_Board & operator +=(const Circuit_Board &);
		const double & operator () (int, int);
		Circuit_Board & operator - (const Circuit_Board &);
		void delete_contact(int);
		contact & get_contact(int);
		Circuit_Board & operator -=(const Circuit_Board &);
		Circuit_Board & operator = (const Circuit_Board &);
		Circuit_Board &operator =(Circuit_Board &&);
	};
}

#endif