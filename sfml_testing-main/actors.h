#pragma once
#include "game_world.h"
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
	int hp{ 50 };
	int meleeDmg{ 2 };
	int meleeAcc{ 0 };
	int energy{ 5000 };
	int speed{ 100 };
	int move_energy_cost{ 100 };
	int melee_energy_cost{ 100 };
	bool alive{ true };
	bool isPlayer{ false };
	bool isInFOV(coords Loc);
	world_plane* active_map;

	action_return moveTile(action move_dir);
	action_return meleeAttack(actor* target);

	

};

class player : public actor {
public:

		player(coords initPos, world_plane* spawn_map);
};


class zombie : public actor { 
public:
	action_return update(actor* player_target); 
	zombie(coords initPos, world_plane* spawn_map);

	bool isHostile{ true };
	bool playerDetected{false};
	bool checkAdjacent(coords PlayerLoc);
	action DetermineZombieMove(coords PlayerLoc); 
};


