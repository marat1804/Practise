#include "Code.h"
#include <iostream>
using namespace  Code;

int input(Line *&a, int &m, int &n)
{
	std::cout << "Enter the number of lines -->" << std::endl;
	if (getNum(m)) {
		return 1;
	}
	std::cout << "Enter the number of columns -->" << std::endl;
	if (getNum(n)) {
		return 1;
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
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j) {
			std::cout << "Enter the number of non-zero items" << std::endl;
			std::cin >> col;
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
				else{
					item->data = number;
					std::cout << "Enter the i->";
					getNum(i1);
					std::cout << "Enter the j->";
					getNum(j1);
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
					//a[i].n += 1;
				}
			}
		}
	return 0;
}