#pragma once
#include "actors.h"

constexpr int MAX_ANNOUNCEMENTS = 12;

struct engine_return {
	bool updated{ false };
	std::vector<std::string> announcements;
	int player_hp{ -1 };
	//will probably later contain generalized end of turn information + extra announcements
};

class engine {
public:
	char display_symbols[MAP_MAX_ROW][MAP_MAX_COLUMN];
	tile_map display;
	world_plane* map;
	player* player_char;
	std::vector<zombie*> active_npcs;
	engine_return update(action players_action);
	engine_return info_to_return;
	void render();
	actor* getTarget(coords target_coords);
	void spawnRandomZombie();
	void checkDeaths();
	engine();


};