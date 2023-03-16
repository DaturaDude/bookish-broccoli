#pragma once
#include <SFML/Graphics.hpp>
#include "map_gen.h"

//tile_map takes character arrays / maps and displays them

class tile_map : public sf::Drawable, public sf::Transformable {
public:

	bool load_BSPbasic();
	bool load_from_array(char(&tiles)[MAP_MAX_ROW][MAP_MAX_COLUMN]);


	void set_display_origin(coords new_origin) {
		display_origin = new_origin;
		return;
	}
	coords get_origin() {
		return display_origin;
	}

	int get_size() {
		return display_square_side;
	}

	tile_map() {
		display_symbols = new char* [display_square_side];
		for (int i = 0; i < display_square_side; i++) {
			display_symbols[i] = new char[display_square_side];
		}
	}

	~tile_map() {
		for (int i = 0; i < display_square_side; i++) {
			delete display_symbols[i];
		}
		delete display_symbols;
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &m_tileset;

		// draw the vertex array
		target.draw(m_vertices, states);
	}

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	std::string tileset_name{"angband_test2.png"};
	sf::Vector2u tileSize{16,16};
	int display_square_side{ 50 };
	coords display_origin;

	char** display_symbols;



};