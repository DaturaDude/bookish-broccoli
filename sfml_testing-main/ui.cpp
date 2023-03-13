#include "ui.h"
#include <iostream>

void game_ui::run() {



    sf::RenderWindow window(sf::VideoMode(1080, 800), "Tilemap");

    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::W) {
                    action player_action = up;
                   turn_info = game_engine.update(player_action);
                   turn_info.updated = true;
                }
                if (event.key.code == sf::Keyboard::A) {
                    action player_action = left;
                    turn_info = game_engine.update(player_action);
                    turn_info.updated = true;
                }
                if (event.key.code == sf::Keyboard::S) {
                    action player_action = down;
                    turn_info = game_engine.update(player_action);
                    turn_info.updated = true;
                }
                if (event.key.code == sf::Keyboard::D) {
                    action player_action = right;
                    turn_info = game_engine.update(player_action);
                    turn_info.updated = true;
                }
                if (event.key.code == sf::Keyboard::Q) {
                    action player_action = up_left;
                    turn_info = game_engine.update(player_action);
                    turn_info.updated = true;
                }
                if (event.key.code == sf::Keyboard::E) {
                    action player_action = up_right;
                    turn_info = game_engine.update(player_action);
                    turn_info.updated = true;
                }
                if (event.key.code == sf::Keyboard::Z) {
                    action player_action = down_left;
                    turn_info = game_engine.update(player_action);
                    turn_info.updated = true;
                }
                if (event.key.code == sf::Keyboard::C) {
                    action player_action = down_right;
                    turn_info = game_engine.update(player_action);
                    turn_info.updated = true;
                }


            }
        }


        if (turn_info.updated) { // out put to console for debugging right now
            for (int i = 0; i < turn_info.announcements.size(); i++) {
                std::cout << turn_info.announcements[i] << std::endl;
            }

            std::cout << "player hp: " << turn_info.player_hp << std::endl;

            while (turn_info.announcements.size() > max_announcements) {
                turn_info.announcements.pop_back();
            }

        }

        turn_info.updated = false;
        // draw the map
        window.clear();
        window.draw(game_engine.display); //ui should choose what to draw based on turn_info

        window.display();
    }

    
    return;

}



/*
bool announcement::load_font() {

	if (!font.loadFromFile("cp437.ttf")) {
		std::cout << "font error." << std::endl;
		return false;
	}

	return true;

}

bool announcement::load_announcement(std::string new_announce) {
	announce = new_announce;
	load_font();
	display_text.setFont(font);
	display_text.setString(announce);
	display_text.setCharacterSize(24);
	display_text.setFillColor(sf::Color::White);
	//display_text.setStyle(sf::Text::Bold); does nothing with this font i think
	display_text.setPosition(850.f, 500.f); //moves text out off the display tile square // numbers are pixels!
	
	return true;
}
*/