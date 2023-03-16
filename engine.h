#pragma once
#include "actors.h"

constexpr int MAX_ANNOUNCEMENTS = 12;




struct engine_return {
	bool updated{ false };
	std::vector<std::string> announcements;
	int player_hp{ 50 };
	//will probably later contain generalized end of turn information + extra announcements
	engine_return& operator=(const engine_return& c) {
		updated = c.updated;
		player_hp = c.player_hp;

		for (int i = 0; i < c.announcements.size(); i++) {
			announcements.push_back(c.announcements[i]);
		}
		return *this;
	}
};

class engine {
public:
	char display_symbols[MAP_MAX_ROW][MAP_MAX_COLUMN];
	tile_map display;
	std::shared_ptr<world_plane> map;
	player* player_char;

	engine_return update(action players_action);
	engine_return info_to_return;
	void render();
	actor* getTarget(coords target_coords);
	void spawnRandomZombie();
	void checkDeaths();
	engine();
	bool game_over{ false };

	//mostly for debugging for now
	void spawn_player_items();

};