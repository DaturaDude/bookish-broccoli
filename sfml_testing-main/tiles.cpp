#include "tiles.h"

bool tile_map::load_BSPbasic() {

	MAP map;
	map.AddBSPbasic();
	//char char_array[MAP_MAX_ROW][MAP_MAX_COLUMN];
	for (int i = 0; i < display_square_side; i++) {
		for (int j = 0; j < display_square_side; j++) {

			display_symbols[i][j] = map.DungeonList.front().tiles[i + display_origin.row][j + display_origin.column]; // <- use these offsets to adjust display origin

		}
	}

	if (!m_tileset.loadFromFile(tileset_name))
		return false;

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(display_square_side * display_square_side * 4);

    //
   // char_array[2][2] = '@';
    //char_array[4][4] = 'Z';
    //

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < display_square_side; ++i)
        for (unsigned int j = 0; j < display_square_side; ++j)
        {
            // get the current tile number


            int tileNumber{ 0 };
            if (display_symbols[i][j] == EMPTY || display_symbols[i][j] == UNSEEN)
                tileNumber = 0;
            if (display_symbols[i][j] == ROCK) {
                tileNumber = 1;
            }
            if (display_symbols[i][j] == FLOOR) {
                tileNumber = 2;
            }
            if (display_symbols[i][j] == '@')
                tileNumber = 3;
            if (display_symbols[i][j] == 'Z')
                tileNumber = 4;

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);


            // find its position in the tileset texture
 

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(j + i * display_square_side) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;


}

bool tile_map::load_from_array(char(&tiles)[MAP_MAX_ROW][MAP_MAX_COLUMN]) {

    for (int i = 0; i < display_square_side; i++) {
        for (int j = 0; j < display_square_side; j++) {
            if ((i + display_origin.row) > MAP_MAX_ROW || (j + display_origin.column) > MAP_MAX_COLUMN)
                display_symbols[i][j] = EMPTY;
            else if ((i + display_origin.row) < 0 || (j + display_origin.column) < 0) {
                display_symbols[i][j] = EMPTY;
            }
            else {
                display_symbols[i][j] = tiles[i + display_origin.row][j + display_origin.column]; // <- use these offsets to adjust display origin
            }
            

        }
    }

    if (!m_tileset.loadFromFile(tileset_name))
        return false;

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(display_square_side * display_square_side * 4);

    //
   // char_array[2][2] = '@';
    //char_array[4][4] = 'Z';
    //

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < display_square_side; ++i)
        for (unsigned int j = 0; j < display_square_side; ++j)
        {
            // get the current tile number


            int tileNumber{ 0 };
            if (display_symbols[j][i] == EMPTY) // [j][i] here!!!!!!
                tileNumber = 0;
            if (display_symbols[j][i] == ROCK) {
                tileNumber = 1;
            }
            if (display_symbols[j][i] == FLOOR) {
                tileNumber = 2;
            }
            if (display_symbols[j][i] == '@')
                tileNumber = 3;
            if (display_symbols[j][i] == 'Z')
                tileNumber = 4;

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);


            // find its position in the tileset texture


            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * display_square_side) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;

}