#include <iostream>
#include<conio.h>
#include "Code.h"

using namespace Code;

int main()
{
	int m, n;
	Line *arr = nullptr, *res = nullptr;
	if (input(arr, m, n)==1) {
		std::cout << "error" << std::endl;
		_getch();
		return 1;
	}
	if (n == 0 || m == 0) {
		arr = nullptr;
	}
	output("Source matrix", arr, m);
	if (matrix_processing(arr, m, n, res, isLess)) {
		std::cout << "" << std::endl;
		erase(arr, m);
		_getch();
		return 1;
	}
	output("Result matrix with numbers that a larger than an average in the line", res, m);
	erase(res, m);
	erase(arr, m);
	_getch();
	return 0;
}
