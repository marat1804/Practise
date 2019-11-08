#ifndef _ITEMS_H_
#define _ITEMS_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

namespace ITEMS {

	enum class EnemyType {
		HUMANOID,
		INSECT,
		ANIMAL,
		DEMON, 
		ICY, 
		UNDEAD
	};

	struct HeroParams {
		int strength=0, agility=0, stamina=0;
		double MaxHealth;
	};

	enum class EquipType {
		HELMET,
		CHESTPLATE,
		AMULET,
		PANTS,
		SHOES,
		EQUIPCOUNT
	};

	class Object {
	protected:
	public:

	};

	class Item :public virtual  Object {
	protected:
		string name;
	public:
		Item(string s = nullptr) : name(s) {};
	};

	class Weapon : public Item {
	private:
		double damage;
	public:
		Weapon(string name, double damage, HeroParams mod, map <EnemyType, double> m );
		double generateDamage();
		void getFeatures();
		void changeFeatures();
	};

	class EnchantedWeapon : public Weapon {
	private:
		map < EnemyType, double> multipler;
	public:
		EnchantedWeapon(string name, double h = 0, double in = 0, double an = 0, double de = 0, double icy = 0, double un = 0);
		double getMultiplier(EnemyType type);
	};


	class Artefact : public Item {
	private:
		HeroParams modifications;
	public:
		Artefact(int sta = 0, int str = 0, int ag = 0);
		int getStamina();
		int getStrength();
		int getAgility();
	};

	class ArtfectEnchantedWeapon : public EnchantedWeapon, public Artefact {
	private:

	public:

	};


	class Equipment : public Item {
	private:
		EquipType type;
		double defence;
	public:
		Equipment(string name, EquipType type0, double def);
		void changeFeatures();
		double generateDefence();
	};

	class ArtefectEquipment : public Equipment, public Artefact {
	private:
		EquipType type;
		double defence;
	public:
		ArtefectEquipment(string name, EquipType type0, double def);
	};


	class Picklocks : public Item {
	private:
		int amount;
	public:
		Picklocks(string name, int c = 1);
		int getCount();
	};

	class Potion : public Item {
	private:
		HeroParams features;
		int duration;

	};

	class Chest : public Object {
	private:
		int lockLevel;
		Item item;
	public:
		Chest(Item i, int l = 1);
		void getParams();
		void tryToOpen();
		void changeParams();
	};

}
#endif