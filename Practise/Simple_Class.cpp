#include "pch.h"
#include "Agnesi_Code.h"
#include "stdafx.h"
#include <iostream>



int _tmain(int argc, _TCHAR* argv[])
{
	Prog::Agnesi curve(1.0);
	Prog::point p;
	int fl1 = 1;
	double r;
	char *s = nullptr;
	while (fl1) {
		std::cout << "Your curve is: ";
		s = new char[70];
		try {
			curve.get_formula(s, 70);
			std::cout << s << std::endl;
		}
		catch (std::exception &ex) {
			std::cout << ex.what() << std::endl;
		}
		delete[] s;
		std::cout << "Area: " << curve.area() << std::endl;
		std::cout << "Volume: " << curve.volume() << std::endl;
		std::cout << "Bendibgs points are: ";
		Prog::point point1, point2;
		try {
			curve.bending_points(point1, point2);
			std::cout << "( " << point1.x << ", " << point1.y << ") ";
			std::cout << "( " << point2.x << ", " << point2.y << ") " << std::endl;
		}
		catch (std::exception &ex) {
			std::cout << ex.what() << std::endl;
		}
		int fl2 = 1;
		while (fl2) {
			std::cout << "Enter x for calculate value y(x) or press ctrl+Z to quit: " << std::endl;
			double x;
			Prog::point y;
			std::cin >> x;
			fl2 = std::cin.good();
			if (!fl2) {
				std::cout << "Error input or stopped manually" << std::endl;
				continue;
			}
			y = curve.f(x);
			std::cout << "y(" << y.x << ") = " << y.y << std::endl;
		}
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Enter new x, y and a to continue or press ctrl+Z to quit: " << std::endl;
		std::cin >>p.x >>p.y>> r;
		if (std::cin.good()) {
			curve.setP(p);
			try {
				curve.setR(r);
			}
			catch (std::exception &ex) {
				std::cout << ex.what()<<", the default settings are set. "<< std::endl;
				curve.setR(1.0);
			}
			std::cout << std::endl;
		}
		else {
			std::cout << std::endl << "Goodbye" << std::endl;
			fl1 = 0;
		}
	}
	return 0;
}