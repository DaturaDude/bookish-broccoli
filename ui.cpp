#include "ui.h"
#include <iostream>

void game_ui::run() {

    game_engine.render(); 

    sf::RenderWindow window(sf::VideoMode(1080, 800), "Tilemap");
    sf::Event event;
    while (window.isOpen())
    {
        // handle events

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed && STATE == RUN) {
                player_action_turn(event);
            }
            else if (event.type == sf::Event::KeyPressed && STATE == MENU) {
                run_inventory_menu(event);
            }

        }
        

        if (game_engine.game_over)
            window.close();

        // draw the map
        window.clear();

        draw_UI(window);

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


    return;
}

void game_ui::load_announcement(std::string a_string) {

    ALERT alert_to_add;
    alert_to_add.display.setFont(font);
    alert_to_add.display.setString(a_string);
    alert_to_add.display.setCharacterSize(16);
    alert_to_add.display.setFillColor(sf::Color::White);

    alerts.push_back(alert_to_add);

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

void ALERT::insert_linefeeds() {

    sf::Vector2f cur_char_pos;

    for (int i = 0; i < display.getString().getSize(); i++) {
        cur_char_pos = display.findCharacterPos(i);

        if (cur_char_pos.x >= 1060.f && extra_lines < 1) {//insert newline into text string;
            std::string wrap_string = display.getString();
            std::string lf = "\n";
            wrap_string.insert(i, lf);
            display.setString(wrap_string);
            extra_lines++;
        }


    }


    return;
}

void game_ui::player_action_turn(sf::Event event) {


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

    if (event.key.code == sf::Keyboard::I) {
        inventory_map.clear();
        STATE = MENU;

    }

    return;


}

void game_ui::run_inventory_menu(sf::Event event) {

    if (event.key.code == sf::Keyboard::Escape) {
        STATE = RUN;
    }

    if (event.key.code == sf::Keyboard::A) {
        action_return info = game_engine.player_char->equipItem(0);
        if (info.success == false) {
            info = game_engine.player_char->chugItem(0);
            load_announcement(info.announcement);
        }
        else {
            load_announcement(info.announcement);
        }

    }

    if (event.key.code == sf::Keyboard::B) {
        action_return info = game_engine.player_char->equipItem(1);
        if (info.success == false) {
            info = game_engine.player_char->chugItem(1);
            load_announcement(info.announcement);
        }
        else {
            load_announcement(info.announcement);
        }
    }

    if (event.key.code == sf::Keyboard::C) {
        action_return info = game_engine.player_char->equipItem(2);
        if (info.success == false) {
            info = game_engine.player_char->chugItem(2);
            load_announcement(info.announcement);
        }
        else {
            load_announcement(info.announcement);
        }
    }


    
    return;
}

void game_ui::draw_UI(sf::RenderWindow& window) {

    if (turn_info.updated) { // out put to console for debugging right now
        for (int i = 0; i < turn_info.announcements.size(); i++) {
            //  std::cout << turn_info.announcements[i] << std::endl;
            load_announcement(i);
        }

        for (int i = 0; i < alerts.size(); i++) {
            if (alerts[i].cur_turns < alerts[i].max_turns) {

                alerts[i].cur_turns++;
            }
            else {
                alerts.erase(alerts.begin() + i);
            }
        }

        while (alerts.size() > max_announce) {
            for (int i = 0; i < alerts.size(); i++) {
                alerts.erase(alerts.begin() + i);
            }
        }

        // std::cout << "player hp: " << turn_info.player_hp << std::endl;
        load_HUD();


    }

    window.draw(game_engine.display); //ui should choose what to draw based on turn_info
    window.draw(HUDline1);
    for (int i = 0; i < alerts.size(); i++) {   //I think I finally fixed the worst of the announcement jank here v and up there ^
        if (i == alerts.size() - 1) {             //needs word wrap now! 
            alerts.at(i).display.setFillColor(sf::Color::Red);

        }
        else {
            alerts.at(i).display.setFillColor(sf::Color::White);
        }
        alerts.at(alerts.size() - 1 - i).insert_linefeeds();
        alerts.at(alerts.size() - 1 - i).display.setPosition(820.f, 700.f - (i * 50.f) + (25.f * alerts.at(alerts.size() - 1 - i).extra_lines));
        if (alerts.at(alerts.size() - 1 - i).extra_lines == 0) {
            alerts.at(alerts.size() - 1 - i).display.move(0.f, 25.f);
        }
        window.draw(alerts.at(alerts.size() - 1 - i).display);
    }

    turn_info.updated = false;
    turn_info.announcements.clear();
    if (STATE == MENU) {
       window.draw(inv_backdrop);

       float x = 180.f;
       float y = 550.f;
        inventory_text.setPosition(sf::Vector2f(150.f, 150.f));

        for (int i = 0; i < game_engine.player_char->backpack.items.size(); i++) {

            if(i <= 10)
            inventory_text.setPosition(sf::Vector2f(125.f , 150.f + (50.f * i)));
            else if (i <= 20)
             inventory_text.setPosition(sf::Vector2f(125.f + x, 150.f + (50.f * i) - y));
            else if(i > 20)
             inventory_text.setPosition(sf::Vector2f(125.f + 2*x, 150.f + (50.f * i) - 2*y));

            std::string temp = game_engine.player_char->backpack.items[i]->name;
            temp += " - ";
            temp += i + 97;
            inventory_text.setString(temp);

            window.draw(inventory_text);

        }
    }

    return;
}
