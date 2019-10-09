#include "pch.h"
#include "..//Simple_Class/stdafx.h"
#include "..//Simple_Class/Agnesi_Code.h"
#include"..//Simple_Class/Agnesi_Code.cpp"


TEST(CurveConstructor, DefaultConstructor)
{
	Prog::Agnesi curve;
	ASSERT_EQ(curve.getR(), 1.0);
	ASSERT_EQ(0, curve.getP().x);
	ASSERT_EQ(0, curve.getP().y);
}

TEST(CurveConstructor, InitConstructor)
{
	Prog::Agnesi curve1(3.0);
	Prog::point p(2, 3);
	ASSERT_EQ(curve1.getR(), 3.0);
	ASSERT_EQ(0, curve1.getP().x);
	ASSERT_EQ(0, curve1.getP().y);

	Prog::Agnesi curve2(p, 8);
	ASSERT_EQ(curve2.getR(), 8.0);
	ASSERT_EQ(2.0, curve2.getP().x);
	ASSERT_EQ(3.0, curve2.getP().y);

	Prog::Agnesi curve3(-4, -5, 5);
	ASSERT_EQ(curve3.getR(), 5.0);
	ASSERT_EQ(-4, curve3.getP().x);
	ASSERT_EQ(-5, curve3.getP().y);
}

TEST(CurveConstructor, TestException) {
	ASSERT_THROW(Prog::Agnesi(-1.0), std::exception);
	Prog::point p;
	ASSERT_THROW(Prog::Agnesi(p,-5.0), std::exception);
	ASSERT_THROW(Prog::Agnesi(2,3,-1.0), std::exception);
}

TEST(CurveMethods, Setter) {
	Prog::Agnesi curve;
	Prog::point p1(3, 2);
	curve.setP(p1);
	ASSERT_EQ(3.0, curve.getP().x);
	ASSERT_EQ(2.0, curve.getP().y);
	Prog::point p2(-3, -2);
	curve.setP(p2);
	ASSERT_EQ(-3.0, curve.getP().x);
	ASSERT_EQ(-2.0, curve.getP().y);
	curve.setR(5.2);
	ASSERT_EQ(5.2, curve.getR());
	ASSERT_ANY_THROW(curve.setR(-1.0));
}

TEST(CurveMethods, f) {
	Prog::Agnesi curve(2.5);
	double err = 0.00001;
	ASSERT_NEAR(2.15517, curve.f(1.0).y, err);
	ASSERT_NEAR(1.21549, curve.f(2.57).y, err);

	Prog::Agnesi curve1(1, 1, 2);
	ASSERT_NEAR(1.61538, curve1.f(4.0).y, err);
	ASSERT_NEAR(1.13425, curve1.f(8.456).y, err);
}

TEST(CurveMethods, Area) {
	Prog::Agnesi curve(8.4);
	double err = 0.001;
	ASSERT_NEAR(221.671, curve.area(), err);

	Prog::Agnesi curve1(1.3, 2.5, 7);
	ASSERT_NEAR(153.938, curve1.area(), err);
}

TEST(CurveMethods, Volume) {
	Prog::Agnesi curve(5.6);
	double err = 0.001;
	ASSERT_NEAR(866.63, curve.volume(), err);

	Prog::Agnesi curve1(5, 6, 2);
	ASSERT_NEAR(39.4784, curve1.volume(), err);
}

TEST(CurveMethods, Bending_Points) {
	Prog::Agnesi curve(9);
	Prog::point p1, p2;
	curve.bending_points(p1, p2);
	double err = 0.0001;
	ASSERT_NEAR(5.19615,p1.x, err);
	ASSERT_NEAR(-5.19615, p2.x, err);
	ASSERT_NEAR(6.75, p1.y, err);
	ASSERT_NEAR(6.75, p2.y, err);

	Prog::Agnesi curve1(6.2, 2.2, 8);
	curve1.bending_points(p1, p2);
	ASSERT_NEAR(-1.5812, p1.x, err);
	ASSERT_NEAR(-10.8188, p2.x, err);
	ASSERT_NEAR(8.2, p1.y, err);
	ASSERT_NEAR(8.2, p2.y, err);
}

TEST(CurveMethods, Bending_Points_Exception) {
	Prog::Agnesi curve2(0, 0, 0);
	Prog::point p1, p2;
	ASSERT_ANY_THROW(curve2.bending_points(p1, p2));
}

TEST(CurveMethods, Formula) {
	Prog::Agnesi curve(9.0);
	char  *buf = new char[70];
	curve.get_formula(buf, 70);
	ASSERT_STREQ("y = 9.00 ^ 3 / (9.00 ^ 2 + x ^ 2)", buf);
	delete[] buf;
	Prog::Agnesi curve1(1.6, 2.6, 1.3);
	buf = new char[70];
	curve1.get_formula(buf, 70);
	ASSERT_STREQ("y - 2.60 = 1.30 ^ 3 / (1.30 ^ 2 + (x - 1.60) ^ 2)", buf);
	delete[] buf;
	Prog::Agnesi curve2(0, 2, 5);
	buf = new char[70];
	curve2.get_formula(buf, 70);
	ASSERT_STREQ("y - 2.00 = 5.00 ^ 3 / (5.00 ^ 2 + x ^ 2)", buf);
	delete[] buf;
	Prog::Agnesi curve3(10000, 112310, 4545643);
	buf = new char[50];
	ASSERT_ANY_THROW(curve3.get_formula(buf, 50));
}

TEST(Curve, Parameters) {
	Prog::Agnesi curve(1.0);
	const double PI = atan(1.0) * 4, err = 0.00001;
	ASSERT_NEAR(PI, curve.area(), err);
	ASSERT_NEAR(PI*PI / 2, curve.volume(), err);
	Prog::point p = curve.f(1.0);
	ASSERT_EQ(p.y, 0.5);
	ASSERT_EQ(p.x, 1.0);
	Prog::point p1, p2;
	curve.bending_points(p1, p2);
	ASSERT_EQ(p1.y, 0.75);
	ASSERT_EQ(p2.y, 0.750);
	ASSERT_NEAR(p1.x, 0.57735, err);
	ASSERT_NEAR(p2.x, -0.57735, err);
	char *buf = new char[80];
	curve.get_formula(buf, 80);
	ASSERT_STREQ("y = 1.00 ^ 3 / (1.00 ^ 2 + x ^ 2)", buf);
	delete[] buf;

	Prog::Agnesi curve1(1, 1, 2.4);
	ASSERT_NEAR(PI*2.4*2.4, curve1.area(), err);
	ASSERT_NEAR(PI*PI*2.4*2.4*2.4/2, curve1.volume(), err);
	p = curve1.f(1.3);
	ASSERT_NEAR(p.y, 3.36308, err);
	ASSERT_EQ(p.x, 1.3);
	curve1.bending_points(p1, p2);
	ASSERT_NEAR(p1.y, 2.8, err);
	ASSERT_NEAR(p2.y, 2.8, err);
	ASSERT_NEAR(p1.x, 0.38564, err);
	ASSERT_NEAR(p2.x, -2.38564, err);
	buf = new char[80];
	curve1.get_formula(buf, 80);
	ASSERT_STREQ("y - 1.00 = 2.40 ^ 3 / (2.40 ^ 2 + (x - 1.00) ^ 2)",buf);
	delete[] buf;
}

int _tmain(int argc, _TCHAR* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}