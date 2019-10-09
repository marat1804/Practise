#include "pch.h"
#include <tchar.h>
#include "..//N1/Code.h"
#include"..//N1/Code.cpp"
using namespace Code;

TEST(Nuber_of_digits_1, Test1) {
	int a = 112;
	int n = number_of_digits(a);
	ASSERT_EQ(n, 3);
}

TEST(Nuber_of_digits_2, Test2) {
	int a = 99999999;
	int n = number_of_digits(a);
	ASSERT_EQ(n, 8);
}

TEST(Nuber_of_digits_3, Test3) {
	int a = 0;
	int n = number_of_digits(a);
	ASSERT_EQ(n, 1);
}

TEST(is_Grater_1, Test1) {
	int a = 12, b = 6;
	bool n = isGrater(a, b);
	ASSERT_EQ(n, true);
}


TEST(is_Grater_2, Test2) {
	int a = 12, b = 6;
	bool n = isGrater(b, a);
	ASSERT_EQ(n, false);
}

TEST(matrix, Test1) {
	int m = 4, n = 3;
	Line *a = nullptr, *res = nullptr;
	try {
		a = new Line[m];
	}
	catch (std::bad_alloc &ba) {
		std::cout << "-----too many rows in matrix" << ba.what() << std::endl;
	}
	for (int i = 0; i < m; ++i) {
		a[i].a = nullptr;
	}
	a[0].a = new Item;
	a[0].a->data = 143; a[0].a->i = 0; a[0].a->j = 0; a[0].a->next = nullptr;
	a[1].a = new Item;
	a[1].a->data = 1; a[1].a->i = 1; a[1].a->j = 1; a[1].a->next = nullptr;
	a[2].a = new Item;
	a[2].a->data = 14; a[2].a->i = 2; a[2].a->j = 2; a[2].a->next = nullptr;
	a[3].a = new Item;
	a[3].a->data = 85; a[3].a->i = 3; a[3].a->j = 1; a[3].a->next = nullptr;
	matrix_processing(a, m, n, res, isGrater);

	ASSERT_EQ(res[0].a->data, 143);
	ASSERT_EQ(res[1].a, nullptr);
	ASSERT_EQ(res[2].a->data, 14);
	ASSERT_EQ(res[3].a->i, 3);
	erase(a, m);
	erase(res, m);
	ASSERT_EQ(a, nullptr);
	ASSERT_EQ(res, nullptr);
}

TEST(matrix, Test2) {
	int m = 4, n = 3;
	Line *a = nullptr, *res = nullptr;
	try {
		a = new Line[m];
	}
	catch (std::bad_alloc &ba) {
		std::cout << "-----too many rows in matrix" << ba.what() << std::endl;
	}
	for (int i = 0; i < m; ++i) {
		a[i].a = nullptr;
	}
	a[0].a = new Item;
	a[0].a->data = 143; a[0].a->i = 0; a[0].a->j = 0; a[0].a->next = nullptr;
	a[1].a = new Item;
	Item *pop = new Item;
	pop->data = 1444; pop->i = 1; pop->j = 2; pop->next = nullptr;
	a[1].a->data = 1; a[1].a->i = 1; a[1].a->j = 1; a[1].a->next = pop;
	a[2].a = new Item;
	a[2].a->data = 14; a[2].a->i = 2; a[2].a->j = 2; a[2].a->next = nullptr;
	a[3].a = new Item;
	a[3].a->data = 85; a[3].a->i = 3; a[3].a->j = 1; a[3].a->next = nullptr;
	matrix_processing(a, m, n, res, isLess);

	ASSERT_EQ(res[0].a, nullptr);
	Item *item = res[1].a;
	ASSERT_EQ(res[1].a->data, 1);
	ASSERT_EQ(res[1].a->i,1 );
	ASSERT_EQ(res[3].a, nullptr);
	erase(a, m);
	erase(res, m);
	ASSERT_EQ(a, nullptr);
	ASSERT_EQ(res, nullptr);
}

int _tmain(int argc, _TCHAR* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}