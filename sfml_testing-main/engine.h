#pragma once
#include "actors.h"

constexpr int MAX_ANNOUNCEMENTS = 12;

class engine {
public:
	char display_symbols[MAP_MAX_ROW][MAP_MAX_COLUMN];
	tile_map display;
	world_plane* map;
	player* player_char;
	std::vector<zombie*> active_npcs;
	void update(action players_action);
	void render();
	actor* getTarget(coords target_coords);
	void spawnRandomZombie();
	void checkDeaths();
	engine();
};