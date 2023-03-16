#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "engine.h"

//this class takes place of main event window. main just creates a game_ui and calls .run();
class ALERT {
public:
	sf::Text display;
	int max_turns{ 6 };
	int cur_turns{ 0 };
	bool displayed{ false };
	int extra_lines{ 0 };
	void insert_linefeeds();
};

enum game_state {RUN = 1, MENU = 2};

class game_ui {
public:
	game_state STATE{ RUN };

	engine game_engine;
	engine_return turn_info;

	sf::Font font;
	game_ui() {
		font.loadFromFile("cp437.ttf");

		inv_backdrop.setFillColor(sf::Color::Black);
		inv_backdrop.setOutlineColor(sf::Color::Red);
		inv_backdrop.setOutlineThickness(5);
		inv_backdrop.setPosition(sf::Vector2f(75.f,75.f));
		inv_backdrop.setSize(sf::Vector2f(650.f, 650.f));

		inventory_text.setFont(font);
		inventory_text.setCharacterSize(20);
		inventory_text.setFillColor(sf::Color::White);
		inventory_text.setPosition(sf::Vector2f(150.f, 150.f));
		inventory_text.setString("debugging");

	}

	sf::Text inventory_text;
	std::map<char, int> inventory_map;
	sf::RectangleShape inv_backdrop;
	sf::Text HUDline1;
	std::vector<ALERT> alerts;


	void load_HUD(); //sf::Text and tile_maps must be loaded with new data before they are drawn
	void load_announcement(int index);
	void run();
	int max_announce{ 12 };

	void player_action_turn(sf::Event event);
	void run_inventory_menu(sf::Event event);
	void draw_UI(sf::RenderWindow& window);

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