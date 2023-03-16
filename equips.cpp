#include "equips.h"

int equipment::get_m_acc_bonus() {

	if (wielded != nullptr) {
		return wielded->m_acc_bonus;
	}
	else {
		return 0;
	}
}

int equipment::get_m_dmg_bonus() {

	if (wielded != nullptr) {
		return wielded->m_dmg_bonus;
	}
	else {
		return 0;
	}

}

int equipment::get_defense_bonus() {
	int total_def = 0;

	if (worn_head != nullptr) {
		total_def += worn_head->defense_bonus;
	}

	if (worn_torso != nullptr) {
		total_def += worn_torso->defense_bonus;
	}

	if (worn_arms != nullptr) {
		total_def += worn_arms->defense_bonus;
	}

	if (worn_legs != nullptr) {
		total_def += worn_legs->defense_bonus;
	}

	if (worn_hands != nullptr) {
		total_def += worn_hands->defense_bonus;
	}

	if (worn_feet != nullptr) {
		total_def += worn_feet->defense_bonus;
	}

	return total_def;

}