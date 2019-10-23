#include "..//Library/Circuit_Board.h"
using namespace Prog;


const char* menu[] = { "0. Exit", "1. Add contact on circuit", "2. Add connection", "3. Route distance","4. Delete contact", "5. Print", "6. Select a specific type "};


int main()
{
	Circuit_Board circuit, circuit2;
	int fl = 1, fl2 = 1, item;
	double dist;
	int from, to;
	Prog::contact elem;
	while (fl) {
		for (int i = 0; i < 7; i++) {
			std::cout << menu[i] << std::endl;
		}
		std::cout << "Choose --> ";
		std::cin >> item;
		if (!std::cin.good()) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			continue;
		}
		switch (item) {
		case 0:
			fl = 0;
			break;
		case 1:
			fl2 = 1;
			std::cout << "To add a new contact please enter type (0 - out, 1 - in) and coordinates (x,y) --> ";
			std::cin >> circuit;
			if (!std::cin.good()) {
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::cout << "ERROR!" << std::endl << std::endl;
				continue;
			}
			else {
				std::cout << "Contact successfully added!" << std::endl << std::endl;
			}
			break;
		case 2:
			std::cout << "To add a new connection please enter from and to contacts -->";
			fl2 = 1;
			while (fl2) {
				std::cin >> from >> to;
				if (!std::cin.good()) {
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					std::cout << "ERROR!" << std::endl << std::endl;
					continue;
				}
				else
					fl2 = 0;
			}
			try {
				circuit.add_connection(from, to);
				std::cout << "Connection succesfully added" << std::endl << std::endl;
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl << std::endl;
			}
			break;
		case 3:
			std::cout << "To calculate the route distance please enter two contact's id -->";
			std::cin >> from >> to;
			try {
				dist = circuit(from, to);
				std::cout << "Distance between " << from << " and " << to << " is: " << dist << std::endl << std::endl;
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl << std::endl;
			}
			break;
		case 4:
			std::cout << "Enter the contact's id to delete -->";
			std::cin >> item;
			try {
				circuit -= circuit.get_contact(item);
				std::cout << "Successfully deleted" << std::endl << std::endl;
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl << std::endl;
			}
			break;
		case 5:
			std::cout << circuit;
			break;
		case 6:
			fl2 = 1;
			while (fl2) {
				std::cout << "Enter the type of contacts (0 - out, 1 - in) -->";
				std::cin >> to;
				if (!std::cin.good()) {
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					std::cout << "ERROR!" << std::endl << std::endl;
					continue;
				}
				else
					fl2 = 0;
			}
			{
				Circuit_Board circuit1;
				circuit.get_group(circuit1, to);
				circuit1.print(std::cout);
			}
			std::cout << std::endl << std::endl;
			break;
		}

	}
	return 0;
}