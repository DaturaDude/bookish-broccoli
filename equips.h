#pragma once
#include "items.h"

class equipment {
public:
	std::unique_ptr<item> wielded{nullptr};
	std::unique_ptr<item> worn_head{ nullptr };
	std::unique_ptr<item> worn_torso{ nullptr };
	std::unique_ptr<item> worn_arms{ nullptr };
	std::unique_ptr<item> worn_legs{nullptr };
	std::unique_ptr<item> worn_hands{ nullptr };
	std::unique_ptr<item> worn_feet{ nullptr };
	std::unique_ptr<item> worn_ring1{ nullptr };
	std::unique_ptr<item> worn_ring2{ nullptr };
	std::unique_ptr<item> worn_amulet{ nullptr };

	int get_m_acc_bonus();
	int get_m_dmg_bonus();
	int get_defense_bonus();
};