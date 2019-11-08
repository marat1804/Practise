#include "Items.h"
#include "Ñharacters.h"

#ifndef _CELL_H_
#define _CELL_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::vector;
using std::string;
using std::map;
using namespace ITEMS;
using namespace CHARACTERS;


namespace CELL {
	enum CellType{
		FLOOR,
		OPENED_DOOR,
		CLOSED_DOOR,
		STAIRS_UP,
		STAIRS_DOWN
	};

	class Cell {
	private:
		int x, y;
		CellType type;
		Object object;
	public:
		void setType();
		int getType();
		void openDoor();
		void closeDoor();
	};

	class Rooms {
	private:
		Cell *cell;
		unsigned int length, width;
		Enemy *enemies;
		int enemyCount;
	public:
		void putItem();
		void getSize();
		unsigned int getWidth();
		unsigned int getLength();
		void setLength();
		void setWidth();
	};

	class Floor {
	private:
		Rooms *rooms;
		int n;
	};

	class Dungeon {
		Floor *floors;
		int numberOfFloors;	
		Hero hero;
		HeroTable table;
	public:
		void makeTurn();
		void save();
		void load();	
	};

}
#endif 


