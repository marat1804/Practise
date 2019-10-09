#include "pch.h"
#include <iostream>
#include "..//Library/Circuit_Board.h"
#include "gtest/gtest.h"

TEST(Add_contact, All) {
	Prog::Circuit_Board circuit;
	Prog::contact s1(0, 1, 1), s2(5, 2, 3);
	ASSERT_NO_THROW(circuit.add_contact(s1));
	ASSERT_NO_THROW(circuit.add_contact(1, 2, 3));
	ASSERT_NO_THROW(circuit.add_contact(1, 5, 6));
	ASSERT_THROW(circuit.add_contact(s2), std::exception);
	ASSERT_NO_THROW(circuit.add_contact(0, 8, 7));
	ASSERT_THROW(circuit.add_contact(5, 1, 2), std::exception);
	Prog::contact s(1, 2, 5);
	ASSERT_NO_THROW(circuit.add_contact(1, 6, 9));
	ASSERT_THROW(circuit.add_contact(s), std::exception);
	ASSERT_THROW(circuit.add_contact(1, 0, 5), std::exception);
}

TEST(Check_Connection, ALL) {
	Prog::Circuit_Board circuit;
	ASSERT_NO_THROW(circuit.add_contact(1, 2, 3));
	ASSERT_NO_THROW(circuit.add_contact(1, 5, 6));
	ASSERT_NO_THROW(circuit.add_contact(0, 8, 7));
	ASSERT_NO_THROW(circuit.add_contact(1, 6, 9));
	ASSERT_NO_THROW(circuit.add_contact(0, 7, 10));

	ASSERT_THROW(circuit.check_connetcion(-8, 1), std::exception);
	ASSERT_THROW(circuit.check_connetcion(1, 6), std::exception);

	ASSERT_TRUE(circuit.check_connetcion(1, 2));
	ASSERT_EQ(circuit.check_connetcion(0, 1), false);
	ASSERT_EQ(circuit.check_connetcion(0, 3), false);
}

TEST(Add_Connection, All) {
	Prog::Circuit_Board circuit;
	ASSERT_NO_THROW(circuit.add_contact(1, 2, 3));
	ASSERT_NO_THROW(circuit.add_contact(1, 5, 6));
	ASSERT_NO_THROW(circuit.add_contact(0, 8, 7));
	ASSERT_NO_THROW(circuit.add_contact(1, 6, 9));
	ASSERT_NO_THROW(circuit.add_contact(0, 7, 10));

	ASSERT_THROW(circuit.add_connection(-1, 0), std::exception);
	ASSERT_THROW(circuit.add_connection(0, 8), std::exception);

	ASSERT_THROW(circuit.add_connection(0, 1), std::exception);
	ASSERT_THROW(circuit.add_connection(2, 4), std::exception);

	ASSERT_NO_THROW(circuit.add_connection(0, 2));
	ASSERT_NO_THROW(circuit.add_connection(3, 4));

	ASSERT_THROW(circuit.add_connection(1, 2), std::exception);
}

TEST(Route_Distance, Everything) {
	Prog::Circuit_Board circuit;
	ASSERT_NO_THROW(circuit.add_contact(1, 2, 3));
	ASSERT_NO_THROW(circuit.add_contact(1, 5, 6));
	ASSERT_NO_THROW(circuit.add_contact(0, 8, 7));
	ASSERT_NO_THROW(circuit.add_contact(1, 6, 9));
	ASSERT_NO_THROW(circuit.add_contact(0, 7, 10));

	double err = 0.0001;
	ASSERT_NEAR(circuit.route_length(0, 2), 7.2111, err);
	ASSERT_NEAR(circuit.route_length(1, 2), 3.16228, err);
	ASSERT_NEAR(circuit.route_length(3, 4), 1.41421, err);

	ASSERT_THROW(circuit.route_length(0, 1), std::exception);
	ASSERT_THROW(circuit.route_length(2, 4), std::exception);
}

TEST(Get_Group, Test1) {
	Prog::Circuit_Board c1, c2;
	ASSERT_THROW(c1.get_group(c2,1), std::exception);
	ASSERT_THROW(c1.get_group(c2, 8), std::exception);

	ASSERT_NO_THROW(c1.add_contact(1, 2, 3));
	ASSERT_NO_THROW(c1.add_contact(1, 5, 6));
	ASSERT_NO_THROW(c1.add_contact(0, 8, 7));
	ASSERT_NO_THROW(c1.add_contact(1, 6, 9));
	ASSERT_NO_THROW(c1.add_contact(0, 7, 10));

	ASSERT_NO_THROW(c1.get_group(c2, 0));
	ASSERT_THROW(c2.check_connetcion(0, 2), std::exception);
	ASSERT_EQ(c2.check_connetcion(0, 1), false);

}

int _tmain(int argc, _TCHAR *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


