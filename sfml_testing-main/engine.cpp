#include "engine.h"

engine::engine() {
	MAP new_map;
	new_map.AddBSPbasic();
	map = new world_plane(new_map);

	player_char = new player(map->getRandomSpawnPoint(), map);
	map->ActiveGrid->setExplored(player_char->position, player_char->FOVradius);
	render();

	///
	

	for (int i = 0; i < 48; i++) {
		spawnRandomZombie();
	}



}

void engine::render() {

	for (int i = 0; i < MAP_MAX_ROW; i++) {
		for (int j = 0; j < MAP_MAX_COLUMN; j++) {

			if (map->ActiveGrid->GridTiles[i][j].explored)
				display_symbols[i][j] = map->ActiveGrid->GridTiles[i][j].symbol;
			else
				display_symbols[i][j] = UNSEEN;
		}
	}
	coords cam_origin = player_char->position;
	cam_origin.row = cam_origin.row - (display.get_size() / 2);
	cam_origin.column = cam_origin.column - (display.get_size() / 2);
	display.set_display_origin(cam_origin);
	display_symbols[player_char->position.row][player_char->position.column] = player_char->symbol;
	for (int i = 0; i < active_npcs.size(); i++) {
		
	}


	for (int i = 0; i < active_npcs.size(); i++) {

		if (player_char->isInFOV(active_npcs[i]->position)) {
			display_symbols[active_npcs[i]->position.row][active_npcs[i]->position.column] = active_npcs[i]->symbol;
		}

	}




	display.load_from_array(display_symbols);
	return;
}

engine_return engine::update(action players_action) {

	info_to_return.announcements.clear();
	//info_to_return.announcements.push_back("TESTING!.");
	action_return player_go;
	coords attackCoords = player_char->position;
	if(player_char->energy>=5000)
	switch (players_action) {
	case up:
		player_go = player_char->moveTile(up);
		if (player_go.success == true) {
			player_char->energy -= player_char->move_energy_cost;
			map->FloodFillDmap(player_char->position);
			if(player_go.notify_player)
			info_to_return.announcements.push_back(player_go.announcement);
		}
		attackCoords.row--;
		break;
	case down:
		player_go = player_char->moveTile(down);
		if (player_go.success == true) {
			player_char->energy -= player_char->move_energy_cost;
			map->FloodFillDmap(player_char->position);
			if (player_go.notify_player)
			info_to_return.announcements.push_back(player_go.announcement);
		}
		attackCoords.row++;
		break;
	case right:
		player_go = player_char->moveTile(right);
		if (player_go.success == true) {
			player_char->energy -= player_char->move_energy_cost;
			map->FloodFillDmap(player_char->position);
			if (player_go.notify_player)
			info_to_return.announcements.push_back(player_go.announcement);
		}
		attackCoords.column++;
		break;
	case left:
		player_go = player_char->moveTile(left);
		if (player_go.success == true) {
			player_char->energy -= player_char->move_energy_cost;
			map->FloodFillDmap(player_char->position);
			if (player_go.notify_player)
			info_to_return.announcements.push_back(player_go.announcement);
		}
		attackCoords.column--;
		break;
	case up_left:
		player_go = player_char->moveTile(up_left);
		if (player_go.success == true) {
			player_char->energy -= player_char->move_energy_cost;
			map->FloodFillDmap(player_char->position);
			if (player_go.notify_player)
			info_to_return.announcements.push_back(player_go.announcement);
		}
		attackCoords.row--;
		attackCoords.column--;
		break;
	case up_right:
		player_go = player_char->moveTile(up_right);
		if (player_go.success == true) {
			player_char->energy -= player_char->move_energy_cost;
			map->FloodFillDmap(player_char->position);
			if (player_go.notify_player)
			info_to_return.announcements.push_back(player_go.announcement);
		}
		attackCoords.row--;
		attackCoords.column++;
		break;
	case down_left:
		player_go = player_char->moveTile(down_left);
		if (player_go.success == true) {
			player_char->energy -= player_char->move_energy_cost;
			map->FloodFillDmap(player_char->position);
			if (player_go.notify_player)
			info_to_return.announcements.push_back(player_go.announcement);
		}
		attackCoords.row++;
		attackCoords.column--;
		break;
	case down_right:
		player_go = player_char->moveTile(down_right);
		if (player_go.success == true) {
			player_char->energy -= player_char->move_energy_cost;
			map->FloodFillDmap(player_char->position);
			if (player_go.notify_player)
			info_to_return.announcements.push_back(player_go.announcement);
		}
		attackCoords.row++;
		attackCoords.column++;
		break;
	}

	if (player_go.success == false && player_go.alternate_action == null) {

	}

	if (player_go.alternate_action == attack) {

		actor* attack_target = getTarget(attackCoords);
		
		if (attack_target != nullptr) {
			player_go = player_char->meleeAttack(attack_target);
			checkDeaths();
			player_char->energy -= player_char->melee_energy_cost;

			info_to_return.player_hp = player_char->hp;
			if(player_go.notify_player)
			info_to_return.announcements.push_back(player_go.announcement);
		}


	}


	player_char->energy += player_char->speed;

	action_return cur_npc_turn_result;

	for (int i = 0; i < active_npcs.size(); i++) {

		if (active_npcs[i]->energy >= 5000) {
			cur_npc_turn_result = active_npcs[i]->update(player_char);

			if(cur_npc_turn_result.notify_player)
			info_to_return.announcements.push_back(cur_npc_turn_result.announcement);
		}
		checkDeaths();
		active_npcs[i]->energy += active_npcs[i]->speed;
			

	}

	render();
	//null
	info_to_return.player_hp = player_char->hp;
	//engine_return return_info = info_to_return;
	return info_to_return;
}

actor* engine::getTarget(coords target_coords) {

	for (int i = 0; i < active_npcs.size(); i++) {
		if (active_npcs[i]->position.row == target_coords.row && active_npcs[i]->position.column == target_coords.column)
			return active_npcs[i];
	}

	return nullptr;

}

void engine::spawnRandomZombie() {

	coords spawn_pos = map->getRandomSpawnPoint();
	while (map->ActiveGrid->GridTiles[spawn_pos.row][spawn_pos.column].occupied) {
		spawn_pos = map->getRandomSpawnPoint();
	}

	zombie* rand_zomb = new zombie(spawn_pos, map);
	map->ActiveGrid->GridTiles[spawn_pos.row][spawn_pos.column].occupied = true;
	active_npcs.push_back(rand_zomb);

	return;
}

void engine::checkDeaths() {
	if (player_char->hp <= 0) {
		//std::cout << "You died!" << std::endl;
		info_to_return.announcements.push_back("You died!.");
		info_to_return.player_hp = player_char->hp;
		//exit(0);
	}


	for (int i = 0; i < active_npcs.size(); i++) {
		if (!active_npcs[i]->alive) {
			map->ActiveGrid->GridTiles[active_npcs[i]->position.row][active_npcs[i]->position.column].occupied = false;
			delete active_npcs[i];
			active_npcs.erase(active_npcs.begin() + i);
			//std::cout << "The zombie dies!" << std::endl;
			info_to_return.announcements.push_back("The zombie dies!");
		}
	}



}