#pragma once



#include <iostream>
//структуры, классы, прототипы, реализация шаблонов и инлайн функций
namespace Code {

	struct Item {
		int data;
		int j;
		Item *next;
	};

	struct Line{
	//	int n;
		Item *a;
	};


	template <class T>
	int getNum(T &a) {
		std::cin >> a;
		if (!std::cin.good()) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			return 1;
		}
		return 0;
	}

	inline bool isGrater(int a,int b) {
		return a > b;
	}

	inline bool isLess(int a, int b) {
		return a < b;
	}

	int input(Line *&, int &, int &);
	void output(const char*, Line *, int );
	void erase(Line *&res, int m);
	int matrix_processing(Line *a, int m, int n, Line *&res, bool (f(int, int)));
	int count_average(int *a, int n);
	int number_of_digits(int);
	void copy_data(Item *, Item *&);
}
