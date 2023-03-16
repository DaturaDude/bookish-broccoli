#pragma once
#include <vector>
#include <memory>
#include <string>

enum items_list { w_club = 0, h_syringe = 1, k_vest = 2 };

enum equip_type {none = -1, wield = 0, head = 1, torso = 2, arms = 3, legs = 4, hands = 5, feet = 6, ring = 7, neck = 8 };
enum chug_effect { nothing = 0, healing = 1, magic_vision = 2, force_field = 3, teleport = 4 };

class item {
public:
	//i'm not sure how I want to do items, for now i'll cram everything into the base class
	std::string name{ "..." };
	std::string description{ "..." };
	int m_acc_bonus{ 0 };
	int m_dmg_bonus{ 0 };
	int defense_bonus{ 0 };
	equip_type equip_slot{ none };
	bool can_chug{ false };
	chug_effect on_chug{ nothing };
	int chug_effect_magnitude{ 0 };
	item(items_list new_item_type);
};



class inventory {
public:

	std::vector<std::unique_ptr<item>> items;
	int max_items{ 25 };
	int num_items{ 0 };
};

