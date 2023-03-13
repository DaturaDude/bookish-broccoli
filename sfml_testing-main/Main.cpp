
#include "engine.h"

int main()
{

    engine new_engine;


    sf::RenderWindow window(sf::VideoMode(1080, 720), "Tilemap");

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
                    new_engine.update(player_action);
                }
                if (event.key.code == sf::Keyboard::A) {
                    action player_action = left;
                    new_engine.update(player_action);
                }
                if (event.key.code == sf::Keyboard::S) {
                    action player_action = down;
                    new_engine.update(player_action);
                }
                if (event.key.code == sf::Keyboard::D) {
                    action player_action = right;
                    new_engine.update(player_action);
                }
                if (event.key.code == sf::Keyboard::Q) {
                    action player_action = up_left;
                    new_engine.update(player_action);
                }
                if (event.key.code == sf::Keyboard::E) {
                    action player_action = up_right;
                    new_engine.update(player_action);
                }
                if (event.key.code == sf::Keyboard::Z){
                    action player_action = down_left;
                    new_engine.update(player_action);
                }
                if (event.key.code == sf::Keyboard::C) {
                    action player_action = down_right;
                    new_engine.update(player_action);
                }


            }
        }

        // draw the map
        window.clear();
        window.draw(new_engine.display);
        window.display();
    }

    return 0;
}