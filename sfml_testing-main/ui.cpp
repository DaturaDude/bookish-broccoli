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


        // draw the map
        window.clear();

        if (turn_info.updated) { // out put to console for debugging right now
            for (int i = 0; i < turn_info.announcements.size(); i++) {
                std::cout << turn_info.announcements[i] << std::endl;
                load_announcement(i);
            }

            for (int i = 0; i < alerts.size(); i++) {
                if (alerts[i].cur_turns <= alerts[i].max_turns) {

                    alerts[i].cur_turns++;
                }
                else {
                    alerts.erase(alerts.begin() + i);
                }
            }
            std::cout << "player hp: " << turn_info.player_hp << std::endl;
            load_HUD();


        }

        window.draw(game_engine.display); //ui should choose what to draw based on turn_info
        window.draw(HUDline1);  
        for (int i = 0; i < alerts.size(); i++) {   //I think I finally fixed the worst of the announcement jank here v and up there ^
            if (i == alerts.size() - 1) {             //needs word wrap now! // i'm definitely losing some announcements for zombie hits on turns when i also attack, even on the console!
                alerts.at(i).display.setFillColor(sf::Color::Red);

            }
            else {
                alerts.at(i).display.setFillColor(sf::Color::White);
            }
            alerts.at(alerts.size() -1 - i).display.setPosition(820.f, 750.f - (i * 50.f));
            window.draw(alerts.at(alerts.size() - 1 - i).display);
        }

        turn_info.updated = false;
        turn_info.announcements.clear();
        window.display();
    }


    return;

}

void game_ui::load_HUD() {

    HUDline1.setFont(font);
    std::string HUDstring1 = "Player HP: " + std::to_string(turn_info.player_hp);
    HUDline1.setString(HUDstring1);
    HUDline1.setCharacterSize(24);
    HUDline1.setFillColor(sf::Color::White);
    HUDline1.setPosition(820.f, 20.f);
    return;
}

void game_ui::load_announcement(int index) {


        ALERT alert_to_add;
        alert_to_add.display.setFont(font);
        alert_to_add.display.setString(turn_info.announcements.at(index));
        alert_to_add.display.setCharacterSize(16);
        alert_to_add.display.setFillColor(sf::Color::White);
       

        alerts.push_back(alert_to_add);
    
        turn_info.announcements.erase(turn_info.announcements.begin() + index);








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