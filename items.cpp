#include "items.h"

item::item(items_list new_item_type) {

	switch (new_item_type) {
	case w_club:
		name = "Wooden club";
		description = "Not much of a weapon, but it will have to do for now.";
		equip_slot = wield;
		m_acc_bonus = 2;
		m_dmg_bonus = 1;
	break;

	case h_syringe:
		name = "Medical syringe";
		description = "A strange tube shaped object with the label: EMERGENCY USE ONLY SIDE EFFECTS MAY OCCUR.";
		can_chug = true;
		on_chug = healing;
		chug_effect_magnitude = 35;
	break;

	case k_vest:
		name = "Kevlar vest";
		description = "A piece of modern body armor made of woven aramid fibers. Designed to protect against relatively low-velocity projectiles.";
		equip_slot = torso;
		defense_bonus = 3;
	break;



	}

}
