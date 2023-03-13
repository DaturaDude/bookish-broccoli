#pragma once
#include <iostream>
#include "tiles.h"

constexpr int CHUNK_SIZE = MAP_MAX_ROW; 
constexpr int PLANE_CHUNKS = 4;

struct world_tile {
	char symbol{ EMPTY };
	char prev_symbol{ EMPTY };
	bool passable{ false };
	bool explored{ false };
	bool occupied{ false }; // only one actor per tile for now

};

class world_chunk {
public:

	void loadTerrainTiles() {
		for (int i = 0; i < MAP_MAX_ROW; i++) {
			for (int j = 0; j < MAP_MAX_COLUMN; j++) {


				int checkSymbol;

				checkSymbol = GridTiles[i][j].symbol;



				if (checkSymbol == ROCK) {
					GridTiles[i][j].passable = false;
					GridTiles[i][j].explored = false;
					GridTiles[i][j].symbol = ROCK;
				}
				else if (checkSymbol == FLOOR) {
					GridTiles[i][j].passable = true;
					GridTiles[i][j].explored = false;
					GridTiles[i][j].symbol = FLOOR;
				}
				else if (checkSymbol == EMPTY) {
					GridTiles[i][j].passable = false;
					GridTiles[i][j].explored = false;
					GridTiles[i][j].symbol = EMPTY;
				}




			}

		}
	}

	world_tile GridTiles[MAP_MAX_ROW][MAP_MAX_COLUMN];

	world_chunk() {

		for (int i = 0; i < MAP_MAX_ROW; i++) {
			for (int j = 0; j < MAP_MAX_COLUMN; j++) {
				GridTiles[i][j].explored = false;
				GridTiles[i][j].passable = false;
				GridTiles[i][j].symbol = EMPTY;

			}
		}

	}
	void setTilesFromMap(MAP CharMap);
	void setTilesDefault();
	void editSingleTileTerrain(coords Loc, int TERRAIND);
	//sets tiles explored flags based on a given actor location and fov radius
	void setExplored(coords ActorLoc, int ActorFOVradius);
	coords findPlayerInitSpace();
	void printGridCharsToConsole();
};


struct DmapTile {
	int distance;
	bool passable;
	bool set;
	bool searched;
};

struct DmapSearch {
	bool Qpassable;
	bool Wpassable;
	bool Epassable;
	bool Apassable;
	bool Spassable;
	bool Dpassable;
	bool Zpassable;
	bool Cpassable;
	int Wdistance;
	int Adistance;
	int Sdistance;
	int Ddistance;
	int Qdistance;
	int Edistance;
	int Zdistance;
	int Cdistance;
};


class world_plane {	
public:

	world_chunk* TotalGrids[PLANE_CHUNKS / 2][PLANE_CHUNKS / 2];
	world_chunk* ActiveGrid;


	world_plane(MAP initMap) {
		CREATEFROMMAP(initMap);
	}

	void CREATEFROMMAP(MAP map); //creates a Plane from a MAP based on generated symbols
	int calcDistance(coords point1, coords point2);
	void initDmap();
	DmapSearch DmapCheckAdjTiles(coords checkLoc, coords sourceLoc);
	DmapTile Dmap[MAP_MAX_ROW][MAP_MAX_COLUMN];
	void FloodFillDmap(coords source); //flood fill Dmap from the source tile
	void printDmap(); //for debugging
	bool checkOOB(coords Loc);
	char DmapPath(coords NPCLoc);
	coords getRandomSpawnPoint();

	//********


};
