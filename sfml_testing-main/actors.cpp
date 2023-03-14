#include "actors.h"

action_return actor::meleeAttack(actor* target) {
	action_return return_info;
	return_info.notify_player = true;
	int baseDmg = meleeDmg;

	//first roll 3d6 for hit/miss

	int d1 = generateRandomInt(1, 6);
	int d2 = generateRandomInt(1, 6);
	int d3 = generateRandomInt(1, 6);
	int accRoll = d1 + d2 + d3;
	//add acc bonus to acc roll, if roll is greater than or equal to nine(<-prob too high) hit else miss
	accRoll += meleeAcc;
	bool Hit;
	if (accRoll > 6) {
		Hit = true;
	}
	else {
		Hit = false;
	}

	if (Hit == false) {
		std::string AnnouncementMiss = name + " Misses " + target->name + ".";
		return_info.announcement = AnnouncementMiss;
		//std::cout << AnnouncementMiss << std::endl;
		return_info.success = false;
		return return_info;
	}

	int damageRoll = 0;
	//next for each meleeDmg point an actor has sum 1d2 for damage
	for (int i = 0; i < baseDmg; i++) {
		damageRoll += generateRandomInt(1, 2);

	}

	damageRoll += baseDmg - 1;
	target->hp -= damageRoll;



	std::string Announcement = name + " hits " + target->name + " for " + std::to_string(damageRoll) + " damage.";
	//std::cout << Announcement << std::endl;
	return_info.announcement = Announcement;
	return_info.success = true;
	if (target->hp <= 0)
		target->alive = false;

	return return_info;

}

action_return actor::moveTile(action move_dir) { // handle speed/energy stuff in the update function
	action_return return_info;
	
	coords tempCoords = position;

	switch (move_dir) {
    case up:

        tempCoords.row--;
		if (active_map->ActiveGrid->GridTiles[tempCoords.row][tempCoords.column].passable) {

			if (active_map->ActiveGrid->GridTiles[tempCoords.row][tempCoords.column].occupied) {
				return_info.success = false;
				return_info.announcement = "attack_instead.";
				return_info.alternate_action = attack; //queue attack instead
				return return_info;
			}
			else {
				active_map->ActiveGrid->GridTiles[position.row][position.column].occupied = false;
				position = tempCoords;
				active_map->ActiveGrid->GridTiles[position.row][position.column].occupied = true;
				if(isPlayer)
				active_map->ActiveGrid->setExplored(position, FOVradius);
				return_info.announcement = "movement_successful";
				return_info.success = true;
				return_info.alternate_action = null;
				//std::cout << "rows: " << position.row << " columns: " << position.column << std::endl;
				return return_info;

			}

		}
		else {
			return_info.success = false;
			return_info.announcement = "movement_blocked.";
			return_info.alternate_action = null;//no alternate action requested for now
			return return_info;
		}
		break;

	case left:
		tempCoords = position;
		tempCoords.column--;
		if (active_map->ActiveGrid->GridTiles[tempCoords.row][tempCoords.column].passable) {

			if (active_map->ActiveGrid->GridTiles[tempCoords.row][tempCoords.column].occupied) {
				return_info.success = false;
				return_info.announcement = "attack_instead.";
				return_info.alternate_action = attack; //queue attack instead
				return return_info;
			}
			else {
				active_map->ActiveGrid->GridTiles[position.row][position.column].occupied = false;
				position = tempCoords;
				active_map->ActiveGrid->GridTiles[position.row][position.column].occupied = true;
				if (isPlayer)
				active_map->ActiveGrid->setExplored(position, FOVradius);
				return_info.announcement = "movement_successful";
				return_info.success = true;
				return_info.alternate_action = null;
				//std::cout << "rows: " << position.row << " columns: " << position.column << std::endl;
				return return_info;

			}

		}
		else {
			return_info.success = false;
			return_info.announcement = "movement_blocked.";
			return_info.alternate_action = null;//no alternate action requested for now
			return return_info;
		}
		break;
	case down:
		tempCoords = position;
		tempCoords.row++;
		if (active_map->ActiveGrid->GridTiles[tempCoords.row][tempCoords.column].passable) {

			if (active_map->ActiveGrid->GridTiles[tempCoords.row][tempCoords.column].occupied) {
				return_info.success = false;
				return_info.announcement = "attack_instead.";
				return_info.alternate_action = attack; //queue attack instead
				return return_info;
			}
			else {
				active_map->ActiveGrid->GridTiles[position.row][position.column].occupied = false;
				position = tempCoords;
				active_map->ActiveGrid->GridTiles[position.row][position.column].occupied = true;
				if (isPlayer)
				active_map->ActiveGrid->setExplored(position, FOVradius);
				return_info.announcement = "movement_successful";
				return_info.success = true;
				return_info.alternate_action = null;
				//std::cout << "rows: " << position.row << " columns: " << position.column << std::endl;
				return return_info;

			}

		}
		else {
			return_info.success = false;
			return_info.announcement = "movement_blocked.";
			return_info.alternate_action = null;//no alternate action requested for now
			return return_info;
		}
		break;
	case right:
		tempCoords = position;
		tempCoords.column++;
		if (active_map->ActiveGrid->GridTiles[tempCoords.row][tempCoords.column].passable) {

			if (active_map->ActiveGrid->GridTiles[tempCoords.row][tempCoords.column].occupied) {
				return_info.success = false;
				return_info.announcement = "attack_instead.";
				return_info.alternate_action = attack; //queue attack instead
				return return_info;
			}
			else {
				active_map->ActiveGrid->GridTiles[position.row][position.column].occupied = false;
				position = tempCoords;
				active_map->ActiveGrid->GridTiles[position.row][position.column].occupied = true;
				if (isPlayer)
				active_map->ActiveGrid->setExplored(position, FOVradius);
				return_info.announcement = "movement_successful";
				return_info.success = true;
				return_info.alternate_action = null;
				//std::cout << "rows: " << position.row << " columns: " << position.column << std::endl;
				return return_info;

			}

		}
		else {
			return_info.success = false;
			return_info.announcement = "movement_blocked.";
			return_info.alternate_action = null;//no alternate action requested for now
			return return_info;
		}
		break;
	case up_left:
		tempCoords = position;
		tempCoords.row--;
		tempCoords.column--;
		if (active_map->ActiveGrid->GridTiles[tempCoords.row][tempCoords.column].passable) {

			if (active_map->ActiveGrid->GridTiles[tempCoords.row][tempCoords.column].occupied) {
				return_info.success = false;
				return_info.announcement = "attack_instead.";
				return_info.alternate_action = attack; //queue attack instead
				return return_info;
			}
			else {
				active_map->ActiveGrid->GridTiles[position.row][position.column].occupied = false;
				position = tempCoords;
				active_map->ActiveGrid->GridTiles[position.row][position.column].occupied = true;
				if (isPlayer)
				active_map->ActiveGrid->setExplored(position, FOVradius);
				return_info.announcement = "movement_successful";
				return_info.success = true;
				return_info.alternate_action = null;
				return return_info;

			}

		}
		else {
			return_info.success = false;
			return_info.announcement = "movement_blocked.";
			return_info.alternate_action = null;//no alternate action requested for now
			return return_info;
		}
		break;
	case up_right:
		tempCoords = position;
		tempCoords.row--;
		tempCoords.column++;
		if (active_map->ActiveGrid->GridTiles[tempCoords.row][tempCoords.column].passable) {

			if (active_map->ActiveGrid->GridTiles[tempCoords.row][tempCoords.column].occupied) {
				return_info.success = false;
				return_info.announcement = "attack_instead.";
				return_info.alternate_action = attack; //queue attack instead
				return return_info;
			}
			else {
				active_map->ActiveGrid->GridTiles[position.row][position.column].occupied = false;
				position = tempCoords;
				active_map->ActiveGrid->GridTiles[position.row][position.column].occupied = true;
				if (isPlayer)
				active_map->ActiveGrid->setExplored(position, FOVradius);
				return_info.announcement = "movement_successful";
				return_info.success = true;
				return_info.alternate_action = null;
				return return_info;

			}

		}
		else {
			return_info.success = false;
			return_info.announcement = "movement_blocked.";
			return_info.alternate_action = null;//no alternate action requested for now
			return return_info;
		}
		break;
	case down_left:
		tempCoords = position;
		tempCoords.row++;
		tempCoords.column--;
		if (active_map->ActiveGrid->GridTiles[tempCoords.row][tempCoords.column].passable) {

			if (active_map->ActiveGrid->GridTiles[tempCoords.row][tempCoords.column].occupied) {
				return_info.success = false;
				return_info.announcement = "attack_instead.";
				return_info.alternate_action = attack; //queue attack instead
				return return_info;
			}
			else {
				active_map->ActiveGrid->GridTiles[position.row][position.column].occupied = false;
				position = tempCoords;
				active_map->ActiveGrid->GridTiles[position.row][position.column].occupied = true;
				if (isPlayer)
				active_map->ActiveGrid->setExplored(position, FOVradius);
				return_info.announcement = "movement_successful";
				return_info.success = true;
				return_info.alternate_action = null;
				return return_info;

			}

		}
		else {
			return_info.success = false;
			return_info.announcement = "movement_blocked.";
			return_info.alternate_action = null;//no alternate action requested for now
			return return_info;
		}
		break;
	case down_right:
		tempCoords = position;
		tempCoords.row++;
		tempCoords.column++;
		if (active_map->ActiveGrid->GridTiles[tempCoords.row][tempCoords.column].passable) {

			if (active_map->ActiveGrid->GridTiles[tempCoords.row][tempCoords.column].occupied) {
				return_info.success = false;
				return_info.announcement = "attack_instead.";
				return_info.alternate_action = attack; //queue attack instead
				return return_info;
			}
			else {
				active_map->ActiveGrid->GridTiles[position.row][position.column].occupied = false;
				position = tempCoords;
				active_map->ActiveGrid->GridTiles[position.row][position.column].occupied = true;
				if (isPlayer)
				active_map->ActiveGrid->setExplored(position, FOVradius);
				return_info.announcement = "movement_successful";
				return_info.success = true;
				return_info.alternate_action = null;
				return return_info;

			}

		}
		else {
			return_info.success = false;
			return_info.announcement = "movement_blocked.";
			return_info.alternate_action = null;//no alternate action requested for now
			return return_info;
		}
		break;
    default:




        break;


	}

	return return_info;
}

bool actor::isInFOV(coords Loc) {


	int FOVrows = (FOVradius * 2) + 1;
	int FOVcolumns = (FOVradius * 2) + 1;

	int FOVoriginRow = position.row - FOVradius;
	int FOVoriginCol = position.column - FOVradius;

	bool playerFound = false;

	for (int i = FOVoriginRow; i < FOVrows + FOVoriginRow; i++) {
		for (int j = FOVoriginCol; j < FOVcolumns + FOVoriginCol; j++) {

			bool OOB = false;
			if (i < 0 || i >= MAP_MAX_ROW)
				OOB = true;
			else if (j < 0 || j >= MAP_MAX_COLUMN)
				OOB = true;

			if (!OOB) {
				if ((Loc.row == i) && (Loc.column == j))
					playerFound = true;
			}


		}
	}

	return playerFound;


}

action zombie::DetermineZombieMove(coords PlayerLoc) {

	action moveChar = wait_here;	//pass turn
	if (isInFOV(PlayerLoc))
		playerDetected = true;


	if (playerDetected) {
		bool isAdjacent = checkAdjacent(PlayerLoc);
		if (isAdjacent) {
			moveChar = attack; //melee player
		}
		else {
			char pathing = active_map->DmapPath(position);
			switch (pathing) {
			case 'w':
				moveChar = up;
				break;
			case 'a':
				moveChar = left;
				break;
			case 's':
				moveChar = down;
				break;
			case 'd':
				moveChar = right;
				break;
			case 'q':
				moveChar = up_left;
				break;
			case 'e':
				moveChar = up_right;
				break;
			case 'z':
				moveChar = down_left;
				break;
			case 'c':
				moveChar = down_right;
				break;
			case 'x':
				moveChar = wait_here;
				break;

			}
		}

	}

	return moveChar;


}

bool zombie::checkAdjacent(coords PlayerLoc) {

	bool returnBool = false;

	coords Wloc = position;
	Wloc.row--;
	coords Aloc = position;
	Aloc.column--;
	coords Sloc = position;
	Sloc.row++;
	coords Dloc = position;
	Dloc.column++;
	coords Qloc = position;
	Qloc.row--;
	Qloc.column--;
	coords Eloc = position;
	Eloc.row--;
	Eloc.column++;
	coords Zloc = position;
	Zloc.row++;
	Zloc.column--;
	coords Cloc = position;
	Cloc.row++;
	Cloc.column++;

	if (Wloc.row == PlayerLoc.row && Wloc.column == PlayerLoc.column)
		returnBool = true;
	if (Aloc.row == PlayerLoc.row && Aloc.column == PlayerLoc.column)
		returnBool = true;
	if (Sloc.row == PlayerLoc.row && Sloc.column == PlayerLoc.column)
		returnBool = true;
	if (Dloc.row == PlayerLoc.row && Dloc.column == PlayerLoc.column)
		returnBool = true;
	if (Qloc.row == PlayerLoc.row && Qloc.column == PlayerLoc.column)
		returnBool = true;
	if (Eloc.row == PlayerLoc.row && Eloc.column == PlayerLoc.column)
		returnBool = true;
	if (Zloc.row == PlayerLoc.row && Zloc.column == PlayerLoc.column)
		returnBool = true;
	if (Cloc.row == PlayerLoc.row && Cloc.column == PlayerLoc.column)
		returnBool = true;

	return returnBool;


}

zombie::zombie(coords initPos, world_plane* spawn_map) {
	symbol = 'Z';
	position = initPos;
	name = "Zombie";
	description = "It wants to eat your brains.";
	speed = 80;
	hp = 20;
	active_map = spawn_map;
}

player::player(coords initPos, world_plane* spawn_map) {
	symbol = '@';
	position = initPos;
	name = "player_name";
	description = "You.";
	active_map = spawn_map;
	isPlayer = true;
}

action_return zombie::update(actor* player_target) {

	action npc_turn = DetermineZombieMove(player_target->position);
	action_return return_info;

	if (npc_turn == wait_here) {		//get speed back at the end of engine's update.
		energy -= move_energy_cost;
		return_info.announcement = "\0";
		return_info.alternate_action = null;
		return_info.success = true;
		return return_info;
	}


	if (npc_turn == attack) {
		return_info = meleeAttack(player_target);
		return_info.notify_player = true;
		energy -= melee_energy_cost;
		return return_info;
	}

	if (npc_turn == up) {
		return_info = moveTile(up);
		energy -= move_energy_cost;
		return return_info;
	}

	if (npc_turn == down) {
		return_info = moveTile(down);
		energy -= move_energy_cost;
		return return_info;
	}

	if (npc_turn == left) {
		return_info = moveTile(left);
		energy -= move_energy_cost;
		return return_info;
	}

	if (npc_turn == right) {
		return_info = moveTile(right);
		energy -= move_energy_cost;
		return return_info;
	}

	if (npc_turn == up_left) {
		return_info = moveTile(up_left);
		energy -= move_energy_cost;
		return return_info;
	}

	if (npc_turn == up_right) {
		return_info = moveTile(up_right);
		energy -= move_energy_cost;
		return return_info;
	}

	if (npc_turn == down_left) {
		return_info = moveTile(down_left);
		energy -= move_energy_cost;
		return return_info;
	}

	if (npc_turn == down_right) {
		return_info = moveTile(down_right);
		energy -= move_energy_cost;
		return return_info;
	}

	return return_info;

}