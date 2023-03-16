#pragma once
#include "game_world.h"
#include "equips.h"

enum action {
	up = 'w', left = 'a', right = 'd', down = 's', up_left = 'q',
	up_right = 'e', down_left = 'z', down_right = 'c', wait_here = 'x', attack = 'A', null = 'X'
};
struct action_return {
	bool success{ true };
	bool notify_player{ false };
	std::string announcement{ "..." };
	action alternate_action{ null };
};



class actor {
public:
	coords position;
	char symbol{'X'};
	int FOVradius{ 8 };
	std::string name{"..."};
	std::string description{"..."};
	int max_hp{ 50 };
	int hp{ 50 };
	int meleeDmg{ 1 };
	int meleeAcc{ 0 };
	int energy{ 5000 };
	int speed{ 100 };
	int move_energy_cost{ 100 };
	int melee_energy_cost{ 100 };
	bool alive{ true };
	bool isPlayer{ false };
	bool isInFOV(coords Loc);
	std::shared_ptr<world_plane> active_map;

	action_return moveTile(action move_dir);
	action_return meleeAttack(actor* target);
	action_return pickItem(coords ground_loc);
	action_return equipItem(int inv_index);
	action_return chugItem(int inv_index);

	equipment worn_items;
	inventory backpack;
};

class player : public actor {
public:

	player(coords initPos, std::shared_ptr<world_plane> spawn_map);
};


class zombie : public actor { 
public:
	action_return update(actor* player_target); 
	zombie(coords initPos, std::shared_ptr<world_plane> spawn_map);

	bool isHostile{ true };
	bool playerDetected{false};
	bool checkAdjacent(coords PlayerLoc);
	action DetermineZombieMove(coords PlayerLoc); 
};



