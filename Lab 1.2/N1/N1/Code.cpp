#include "Code.h"

namespace Code {
	int input(Line *&a, int &m, int &n)
	{
		std::cout << "Enter the number of lines -->" << std::endl;
		if (getNum(m)||m==0) {
			std::cout << "Zero rows, LOL" << std::endl;
			a = nullptr;
			return 2;
		}
		std::cout << "Enter the number of columns -->" << std::endl;
		if (getNum(n)||n==0) {
			std::cout << "Zero items in colums, OMG" << std::endl;
			a = nullptr;
			return 2;
		}
		try {
			a = new Line[m];
		}
		catch (std::bad_alloc &ba) {
			std::cout << "-----too many rows in matrix" << ba.what() << std::endl;
		}
		for (int i = 0; i < m; ++i) {
			//a[i].n = 0;
			a[i].a = nullptr;
		}
		int number = 0, col, i1, j1;
		Item *item = nullptr, *last = nullptr;
		for (int i = 0; i < m; ++i) {
			std::cout << "Enter the number of non-zero items on "<<i<<" row" << std::endl;
			std::cin >> col;
			if (col > n) {
				std::cout << "Soooory, but only " << n << " numbers is posible" << std::endl;
				col = n;
			}
			for (int q = 0; q < col; q++) {
				try {
					item = new Item;
				}
				catch (std::bad_alloc &ba) {
					std::cout << "-----oopsie" << ba.what() << std::endl;
				}
				std::cout << "Enter the data->";
				if (getNum(number) || number == 0) {
					q--;
					continue;
				}
				else {
					item->data = number;
					std::cout << "Enter the j->";
					getNum(j1);
					if (j1 >= n) {
						std::cout << "Sorry but it will be " << n - 1 << std::endl;
						j1 = n - 1;
					}
					item->j = j1;
					item->next = nullptr;
					if (!a[i].a) {
						a[i].a = item;
						last = a[i].a;
					}
					else {
						last->next = item;
						last = last->next;
					}
				}
			}
		
		}
		return 0;
	}

	void output(const char *string, Line *a, int m)
	{
		Item *item;
		std::cout << string << std::endl;
		if (a) {
			for (int i = 0; i < m; ++i) {
				item = a[i].a;
				while (item != nullptr) {
					std::cout << item->data << " (" << i << ',' << item->j << ')' << "; ";
					item = item->next;
				}
				std::cout << std::endl;
			}
		}
	}

	void erase(Line *& a, int m)
	{
		Item *item, *p;
		if (a) {
			for (int i = 0; i < m; ++i) {
				item = a[i].a;
				while (item != nullptr) {
					p = item;
					item = item->next;
					delete p;
				}
			}
			delete[] a;
			a = nullptr;
		}
	}


	int matrix_processing(Line *a, int m, int n, Line *& res, bool (f(int, int)))
	{
		res = new Line[m];
		Item *item, *ptr;
		int average=0, k;
		for (int i = 0; i < m; ++i) {
			res[i].a = nullptr;
			//res[i].n = 0;
		}
		if (a) {
			for (int i = 0; i < m; ++i) {
				item = a[i].a;
				k = 0;
				while (item) {
					average += number_of_digits(item->data);
					item = item->next;
					k += 1;
				}
				average = average + n - k;
				average = average / n;
				item = a[i].a;
				while (item) {
					if (f(number_of_digits(item->data), average)) {
						ptr = new Item;
						copy_data(item, ptr);
						ptr->next = res[i].a;
						res[i].a = ptr;
					}
					item = item->next;
				}
			}
		}
		return 0;
	}

	void copy_data(Item *from, Item *&to) {
		to->data = from->data;
		to->j = from->j;
	}

	int count_average(int * a, int n)
	{
		int sum = 0;
		for (int i = 0; i < n; ++i)
			sum += a[i];
		return sum / n;
	}

	int number_of_digits(int a)
	{
		int n = 0;
		if (a < 0)
			a = a * -1;
		if (a <10)
			return 1;
		while (a >  0) {
			n++;
			a = a / 10;
		}
		return n;
	}


}