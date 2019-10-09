#pragma once
#include <cmath>
#include "gtest_prod.h"
const double pi = atan(1.0)*4;

#ifndef CLASS1_H
#define CLASS1_H

namespace Prog {
	struct point {
		double x, y;
		point(double x0 = 0, double y0 = 0) : x(x0), y(y0) {};
	};

	class Agnesi {
	private:
		point p;
		double a;
	public:
		Agnesi(double rad = 1);
		Agnesi(const point &p0, double rad = 1);
		Agnesi(double x0, double y0, double rad = 1);
		point f(double x) const;
		double getR() const { return a; };
		point getP() const { return p; }
		Agnesi& setR(double rad);
		Agnesi& setP(const point &p0) { p = p0; return *this; }
		void bending_points(point &p1, point &p2);
		double area() const;
		double volume() const ;
		void get_formula(char *, int size) const;
	};


}
#endif 