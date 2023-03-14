#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include "engine.h"

//this class takes place of main event window. main just creates a game_ui and calls .run();
struct ALERT {
	sf::Text display;
	int max_turns{ 6 };
	int cur_turns{ 0 };
	bool displayed{ false };
};

class game_ui {
public:
	engine game_engine;
	engine_return turn_info;

	sf::Font font;
	game_ui() {
		font.loadFromFile("cp437.ttf");

	}
	float total_row_pix{800.f}; //<-positions menu bar on screen, coded manually for now
	float total_col_pix{280.f}; //1080 - 800 = 280
	float origin_col{0.f};
	float origin_row{ 0.f };

	sf::Text HUDline1;
	std::vector<ALERT> alerts;
	int max_announce{ 12 };

	void load_HUD(); //sf::Text and tile_maps must be loaded with new data before they are drawn
	void load_announcement(int index);
	void load_display();
	void run();


	int max_announcements{ 12 };


};

/*
class announcement {
public:
	sf::Font font;
	std::string announce{ "TESTING." };
	sf::Text display_text;
	bool load_font();
	bool load_announcement(std::string new_announce);
};

class announcement_display {
public:
	std::deque<std::string> announcements;
	sf::Font font;
	sf::Text display_chars;
	int max_length;
	int character_size{ 18 };
	float x_pixels{ 850.f };
	float y_pixels{ 500.f };
	announcement_display() {
		if (!font.loadFromFile("cp437.ttf")) {
			std::cout << "font error." << std::endl;
		}

	}
};
*/