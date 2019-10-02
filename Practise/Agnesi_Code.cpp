#include "pch.h"
#include "Agnesi_Code.h"
#include "stdafx.h"

namespace Prog {
	Agnesi::Agnesi(double rad): p(0,0)
	{
		if (rad < 0)
			throw std::exception("Invalid radius");
		a = rad;
	}

	Agnesi::Agnesi(const point & p0, double rad) : p(p0)
	{
		if (rad < 0)
			throw std::exception("Invalid radius");
		a = rad;
	}

	Agnesi::Agnesi(double x0, double y0, double rad):p(x0, y0)
	{
		if (rad < 0)
			throw std::exception("Invalid radius");
		a = rad;
	}

	point Agnesi::f(double x) const
	{
		point res;
		res.x = x;
		res.y = pow(a, 3) / (pow(a, 2) + pow(x - p.x, 2))+p.y;
		return res;
	}


	Agnesi& Agnesi::setR(double rad)
	{
		if (rad < 0)
			throw std::exception("Invalid radius");
		a = rad;
		return *this;
	}

	void Agnesi::bending_points(point & p1, point & p2)
	{
		if (a != 0) {
			p1.x = a / sqrt(3) - p.x;
			p1.y = 3 * a / 4 + p.y;
			p2.x = a * -1 / sqrt(3) - p.x;
			p2.y = 3 * a / 4 + p.y;
		}
		else {
			throw std::exception("There are no bending points");
		}
	}

	double Agnesi::area() const
	{
		return pi * pow(a, 2);
	}

	double Agnesi::volume() const
	{
		return pow(pi, 2)*pow(a, 3) / 2;
	}

	void Agnesi::get_formula(char *buf, int size) const
	{
		char s1[] = "y - y0 = a ^ 3 / (a ^ 2 + (x - x0) ^ 2)";
		int l = strlen(s1) + 1;
		size_t Size = 20;
		char num[20];
		sprintf_s(num, 20, "%.2f", a);
		l += strlen(num);
		sprintf_s(num, 20, "%.2f", a);
		l += strlen(num);
		sprintf_s(num, 20, "%.2f", p.x);
		l += strlen(num);
		sprintf_s(num, 20, "%.2f", p.y);
		l += strlen(num);
		if (size < l){
			throw std::exception("There is no enough space for formula");
		}
		if (p.y == 0)
			sprintf_s(buf, l, "y = ");
		else
			sprintf_s(buf, l, "y - %.2f = ", p.y);
		int k = strlen(buf);
		sprintf_s(buf + k, l - k, "%.2f ^ 3 / (%.2f ^ 2 + ", a, a);
		k = strlen(buf);
		if (p.x == 0)
			sprintf_s(buf + k, l - k, "x ^ 2)");
		else
			sprintf_s(buf + k, l - k, "(x - %.2f) ^ 2)", p.x);
		//return s;
	}

	/*char* Agnesi::get_formula() const
	{
		char s1[] = "y - y0 = a ^ 3 / (a ^ 2 + (x - x0) ^ 2)";
		int l = strlen(s1) + 1;
		size_t Size = 20;
		char num[20];
		sprintf_s(num, 20, "%.2f", a*a*a);
		l += strlen(num);
		sprintf_s(num, 20, "%.2f", a*a);
		l += strlen(num);
		sprintf_s(num, 20, "%.2f", p.x);
		l += strlen(num);
		sprintf_s(num, 20, "%.2f", p.y);
		l += strlen(num);
		char *s = new char[l];
		if (p.y == 0)
			sprintf_s(s, l, "y = ");
		else
			sprintf_s(s, l, "y - %.2f = ", p.y);
		int k = strlen(s);
		sprintf_s(s + k, l - k, "%.2f ^ 3 / (%.2f ^ 2 + ", a, a);
		k = strlen(s);
		if (p.x == 0)
			sprintf_s(s+k, l-k, "x ^ 2)");
		else
			sprintf_s(s+k, l-k, "(x - %.2f) ^ 2)", p.x);
		return s;
	}*/
}