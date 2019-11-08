#ifndef _CHARACTERS_H_
#define _CHARACTERS_H_
#include "Items.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;
using namespace ITEMS;

namespace CHARACTERS {

	struct Effect {
		HeroParams boost;
		int duration;
	};

	struct EnemyParams {
		EnemyType type;
		double attack;
		double defence;
	};

	class Hero : public Object{
	private:
		double experience;
		string name;
		double CurHealth;
		HeroParams ParamTable;
		Weapon weapon;
		Equipment equipment [static_cast<int>(EquipType::EQUIPCOUNT)];	
		int MaxPotionNumber;
		Potion *potions;
		int picklocks;
		Effect effects;
	public:
		double getAttackProb();
		double getAttackBonus();
		double getDefenceBonus();
		double generateDamage();
		double dealDamage();
		double getHackProb();
		void LevelUp();
		void getParams();
		void changeParams();
		void takeItem();
		void drinkPotion();
		void takeDamage();
	};

	class HeroTable {
	private:
		map<HeroParams, double> table;
	public:
		void changeParams();
		int getCount();
		friend class HeroTableIt;
		HeroTableIt begin();
		HeroTableIt end();
	};

	class HeroTableIt {
		map<HeroParams, double>::iterator cur;
	};

	class Enemy : public Object {
	private:
		string name;
		double experience;
		Item item;
		double CurHealth;
		double MaxHealth;
		EnemyParams params;
	public:
		void changeParams();
		void getParams();
		double dealDamage();
		void getDamage();
	};
}

#endif