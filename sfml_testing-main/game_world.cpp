#include "game_world.h"

void world_chunk::printGridCharsToConsole() {
	char printChar;
	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {

			printChar = GridTiles[i][j].symbol;
			std::cout << printChar;


		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return;
}


void world_chunk::setTilesFromMap(MAP charMap) {

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {


			GridTiles[i][j].symbol = charMap.DungeonList.front().tiles[i][j];


		}
	}

	loadTerrainTiles();

	return;
}

void world_chunk::setTilesDefault() {
	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {


			GridTiles[i][j].symbol = EMPTY;

		}
	}

	loadTerrainTiles();

	return;

}

coords world_chunk::findPlayerInitSpace() {

	coords returnCOORDS;					//literally just returns the first open space for now
	bool spaceFound = false;

	for (int i = 0; i < MAP_MAX_ROW; i++) {
		for (int j = 0; j < MAP_MAX_COLUMN; j++) {

			if (spaceFound == false) {


				if (GridTiles[i][j].passable == true) {

					spaceFound = true;
					returnCOORDS.row = i;
					returnCOORDS.column = j;

				}

			}
		}
	}

	if (spaceFound == false) {		//error no passable tile found
		std::cout << "ERROR: NO SPAWN LOCATION FOUND" << std::endl;
	}

	return returnCOORDS;

}

void world_chunk::setExplored(coords ActorLoc, int ActorFOVradius) {			/////FIX FOV BUG HERE

	//calculate a size2d based on the actors FOVradius
	size2d FOV;
	FOV.rows = (ActorFOVradius * 2) + 1;
	FOV.columns = (ActorFOVradius * 2) + 1;
	FOV.area = FOV.rows * FOV.columns;
	//then using that size2d rectangle and ActorLoc coordinates set flags on the plane
	//std::cout << "FOV calced: rows: " << FOV.rows << "columns: " << FOV.columns;
	int ActorLocNewOriginRow = ActorLoc.row - ActorFOVradius;
	int ActorLocNewOriginColumn = ActorLoc.column - ActorFOVradius;
	//std::cout << "ACTOR  ORIGIN: (" << ActorLoc.row << ", " << ActorLoc.column << ")" << std::endl;
	//std::cout << "ACTOR NEW ORIGIN: (" << ActorLocNewOriginRow << ", " << ActorLocNewOriginColumn << ")" << std::endl;
	//bool originPrinted = false;


	for (int i = ActorLocNewOriginRow; i < FOV.rows + ActorLocNewOriginRow; i++) {
		for (int j = ActorLocNewOriginColumn; j < FOV.columns + ActorLocNewOriginColumn; j++) {
			//originPrinted = true;
			//if (originPrinted == true)
				//std::cout << "FOV ORIGIN: " << "( " << i << ", j" << ")" << std::endl;
			bool rowout = false;
			if (i < 0 || i >= MAP_MAX_ROW)
				rowout = true;

			bool colout = false;
			if (j < 0 || j >= MAP_MAX_COLUMN)
				colout = true;

			if (!(rowout || colout))
				GridTiles[i][j].explored = true;


		}
	}




	return;
}

void world_plane::CREATEFROMMAP(MAP map) { //plane can only have one active DungeonGrid/Map for now 

	ActiveGrid = new world_chunk;


	for (int i = 0; i < MAP_MAX_ROW; i++) {
		for (int j = 0; j < MAP_MAX_COLUMN; j++) {

			ActiveGrid->GridTiles[i][j].symbol = map.DungeonList.front().tiles[i][j];

		}
	}

	ActiveGrid->loadTerrainTiles();


	return;
}

void world_plane::initDmap() {
	for (int i = 0; i < MAP_MAX_ROW; i++) {
		for (int j = 0; j < MAP_MAX_COLUMN; j++) {
			Dmap[i][j].distance = -1;
			Dmap[i][j].passable = false;
			Dmap[i][j].set = false;
			Dmap[i][j].searched = false;
		}
	}

	return;
}

DmapSearch world_plane::DmapCheckAdjTiles(coords checkLoc, coords sourceLoc) {

	//initialize search object to return
	DmapSearch returnSearch;
	returnSearch.Wdistance = -1;
	returnSearch.Adistance = -1;
	returnSearch.Sdistance = -1;
	returnSearch.Ddistance = -1;
	returnSearch.Wdistance = -1;
	returnSearch.Adistance = -1;
	returnSearch.Sdistance = -1;
	returnSearch.Ddistance = -1;
	returnSearch.Wpassable = false;
	returnSearch.Apassable = false;
	returnSearch.Spassable = false;
	returnSearch.Dpassable = false;
	returnSearch.Qpassable = false;
	returnSearch.Epassable = false;
	returnSearch.Zpassable = false;
	returnSearch.Cpassable = false;

	//first generate adjacent coords
	coords Wloc = checkLoc;
	Wloc.row--;
	coords Aloc = checkLoc;
	Aloc.column--;
	coords Sloc = checkLoc;
	Sloc.row++;
	coords Dloc = checkLoc;
	Dloc.column++;
	coords Qloc = checkLoc;
	Qloc.row--;
	Qloc.column--;
	coords Eloc = checkLoc;
	Eloc.row--;
	Eloc.column++;
	coords Zloc = checkLoc;
	Zloc.row++;
	Zloc.column--;
	coords Cloc = checkLoc;
	Cloc.row++;
	Cloc.column++;
	//then determine if any direction coords go OOB
	bool wOOB = false;
	bool aOOB = false;
	bool sOOB = false;
	bool dOOB = false;
	bool qOOB = false;
	bool eOOB = false;
	bool zOOB = false;
	bool cOOB = false;

	if (Wloc.row < 0 || Wloc.row >= MAP_MAX_ROW)
		wOOB = true;
	if (Wloc.column < 0 || Wloc.column >= MAP_MAX_COLUMN)
		wOOB = true;

	if (Aloc.row < 0 || Aloc.row >= MAP_MAX_ROW)
		aOOB = true;
	if (Aloc.column < 0 || Aloc.column >= MAP_MAX_COLUMN)
		aOOB = true;

	if (Sloc.row < 0 || Sloc.row >= MAP_MAX_ROW)
		sOOB = true;
	if (Sloc.column < 0 || Sloc.column >= MAP_MAX_COLUMN)
		sOOB = true;

	if (Dloc.row < 0 || Dloc.row >= MAP_MAX_ROW)
		dOOB = true;
	if (Sloc.column < 0 || Sloc.column >= MAP_MAX_COLUMN)
		dOOB = true;

	if (Qloc.row < 0 || Qloc.row >= MAP_MAX_ROW)
		qOOB = true;
	if (Qloc.column < 0 || Qloc.column >= MAP_MAX_COLUMN)
		qOOB = true;

	if (Eloc.row < 0 || Eloc.row >= MAP_MAX_ROW)
		eOOB = true;
	if (Eloc.column < 0 || Eloc.column >= MAP_MAX_COLUMN)
		eOOB = true;

	if (Zloc.row < 0 || Zloc.row >= MAP_MAX_ROW)
		zOOB = true;
	if (Zloc.column < 0 || Zloc.column >= MAP_MAX_COLUMN)
		zOOB = true;

	if (Cloc.row < 0 || Cloc.row >= MAP_MAX_ROW)
		cOOB = true;
	if (Cloc.column < 0 || Cloc.column >= MAP_MAX_COLUMN)
		cOOB = true;
	//then check if tiles are passable
	if (!wOOB)
		returnSearch.Wpassable = ActiveGrid->GridTiles[Wloc.row][Wloc.column].passable;

	if (!aOOB)
		returnSearch.Apassable = ActiveGrid->GridTiles[Aloc.row][Aloc.column].passable;

	if (!sOOB)
		returnSearch.Spassable = ActiveGrid->GridTiles[Sloc.row][Sloc.column].passable;

	if (!dOOB)
		returnSearch.Dpassable = ActiveGrid->GridTiles[Dloc.row][Dloc.column].passable;

	if (!qOOB)
		returnSearch.Qpassable = ActiveGrid->GridTiles[Qloc.row][Qloc.column].passable;

	if (!eOOB)
		returnSearch.Epassable = ActiveGrid->GridTiles[Eloc.row][Eloc.column].passable;

	if (!zOOB)
		returnSearch.Zpassable = ActiveGrid->GridTiles[Zloc.row][Zloc.column].passable;

	if (!cOOB)
		returnSearch.Cpassable = ActiveGrid->GridTiles[Cloc.row][Cloc.column].passable;
	//if it is passable, calc distances and return


	if (!wOOB && returnSearch.Wpassable) {
		int distance = pow(abs(Wloc.row - sourceLoc.row), 2) + pow(abs(Wloc.column - sourceLoc.column), 2);
		distance = sqrt(distance);
		returnSearch.Wdistance = distance;
	}

	if (!aOOB && returnSearch.Apassable) {
		int distance = pow(abs(Aloc.row - sourceLoc.row), 2) + pow(abs(Aloc.column - sourceLoc.column), 2);
		distance = sqrt(distance);
		returnSearch.Adistance = distance;
	}

	if (!sOOB && returnSearch.Spassable) {
		int distance = pow(abs(Sloc.row - sourceLoc.row), 2) + pow(abs(Sloc.column - sourceLoc.column), 2);
		distance = sqrt(distance);
		returnSearch.Sdistance = distance;
	}

	if (!dOOB && returnSearch.Dpassable) {
		int distance = pow(abs(Dloc.row - sourceLoc.row), 2) + pow(abs(Dloc.column - sourceLoc.column), 2);
		distance = sqrt(distance);
		returnSearch.Ddistance = distance;
	}

	if (!qOOB && returnSearch.Qpassable) {
		int distance = pow(abs(Qloc.row - sourceLoc.row), 2) + pow(abs(Qloc.column - sourceLoc.column), 2);
		distance = sqrt(distance);
		returnSearch.Qdistance = distance;
	}

	if (!eOOB && returnSearch.Epassable) {
		int distance = pow(abs(Eloc.row - sourceLoc.row), 2) + pow(abs(Eloc.column - sourceLoc.column), 2);
		distance = sqrt(distance);
		returnSearch.Edistance = distance;
	}

	if (!zOOB && returnSearch.Zpassable) {
		int distance = pow(abs(Zloc.row - sourceLoc.row), 2) + pow(abs(Zloc.column - sourceLoc.column), 2);
		distance = sqrt(distance);
		returnSearch.Zdistance = distance;
	}

	if (!cOOB && returnSearch.Cpassable) {
		int distance = pow(abs(Cloc.row - sourceLoc.row), 2) + pow(abs(Cloc.column - sourceLoc.column), 2);
		distance = sqrt(distance);
		returnSearch.Cdistance = distance;
	}


	//^ janky but acceptable distance metric. test with the angband metric below v

	return returnSearch;
}

void world_plane::FloodFillDmap(coords source) {
	initDmap();
	//first check and set source tile
	Dmap[source.row][source.column].distance = 0;
	Dmap[source.row][source.column].passable = true;
	Dmap[source.row][source.column].set = true;
	//then search, update Dmap, and store the coordinates of valid searches in a vector
	DmapSearch searchResults;
	std::vector<coords> validSearches;
	int numValidSearches = 0;

	coords searchCoords = source;
	searchResults = DmapCheckAdjTiles(source, source);
	Dmap[source.row][source.column].searched = true;
	if (searchResults.Wpassable == true) {


		Dmap[searchCoords.row - 1][searchCoords.column].passable = true;
		Dmap[searchCoords.row - 1][searchCoords.column].distance = searchResults.Wdistance;
		Dmap[searchCoords.row - 1][searchCoords.column].set = true;

		coords tempcoords;
		tempcoords.row = searchCoords.row - 1;
		tempcoords.column = searchCoords.column;
		if (!Dmap[tempcoords.row][tempcoords.column].searched) {
			validSearches.push_back(tempcoords);
			numValidSearches++;
		}

	}

	if (searchResults.Apassable == true) {

		Dmap[searchCoords.row][searchCoords.column - 1].passable = true;
		Dmap[searchCoords.row][searchCoords.column - 1].distance = searchResults.Adistance;
		Dmap[searchCoords.row][searchCoords.column - 1].set = true;

		coords tempcoords;
		tempcoords.row = searchCoords.row;
		tempcoords.column = searchCoords.column - 1;
		if (!Dmap[tempcoords.row][tempcoords.column].searched) {
			validSearches.push_back(tempcoords);
			numValidSearches++;
		}
	}

	if (searchResults.Spassable == true) {

		Dmap[searchCoords.row + 1][searchCoords.column].passable = true;
		Dmap[searchCoords.row + 1][searchCoords.column].distance = searchResults.Sdistance;
		Dmap[searchCoords.row + 1][searchCoords.column].set = true;

		coords tempcoords;
		tempcoords.row = searchCoords.row + 1;
		tempcoords.column = searchCoords.column;
		if (!Dmap[tempcoords.row][tempcoords.column].searched) {
			validSearches.push_back(tempcoords);
			numValidSearches++;
		}
	}

	if (searchResults.Dpassable == true) {

		Dmap[searchCoords.row][searchCoords.column + 1].passable = true;
		Dmap[searchCoords.row][searchCoords.column + 1].distance = searchResults.Ddistance;
		Dmap[searchCoords.row][searchCoords.column + 1].set = true;

		coords tempcoords;
		tempcoords.row = searchCoords.row;
		tempcoords.column = searchCoords.column + 1;
		if (!Dmap[tempcoords.row][tempcoords.column].searched) {
			validSearches.push_back(tempcoords);
			numValidSearches++;
		}
	}

	if (searchResults.Qpassable == true) {

		Dmap[searchCoords.row - 1][searchCoords.column - 1].passable = true;
		Dmap[searchCoords.row - 1][searchCoords.column - 1].distance = searchResults.Qdistance;
		Dmap[searchCoords.row - 1][searchCoords.column - 1].set = true;

		coords tempcoords;
		tempcoords.row = searchCoords.row - 1;
		tempcoords.column = searchCoords.column - 1;
		if (!Dmap[tempcoords.row][tempcoords.column].searched) {
			validSearches.push_back(tempcoords);
			numValidSearches++;
		}
	}

	if (searchResults.Epassable == true) {

		Dmap[searchCoords.row - 1][searchCoords.column + 1].passable = true;
		Dmap[searchCoords.row - 1][searchCoords.column + 1].distance = searchResults.Edistance;
		Dmap[searchCoords.row - 1][searchCoords.column + 1].set = true;

		coords tempcoords;
		tempcoords.row = searchCoords.row - 1;
		tempcoords.column = searchCoords.column + 1;
		if (!Dmap[tempcoords.row][tempcoords.column].searched) {
			validSearches.push_back(tempcoords);
			numValidSearches++;
		}
	}

	if (searchResults.Zpassable == true) {

		Dmap[searchCoords.row + 1][searchCoords.column - 1].passable = true;
		Dmap[searchCoords.row + 1][searchCoords.column - 1].distance = searchResults.Zdistance;
		Dmap[searchCoords.row + 1][searchCoords.column - 1].set = true;

		coords tempcoords;
		tempcoords.row = searchCoords.row + 1;
		tempcoords.column = searchCoords.column - 1;
		if (!Dmap[tempcoords.row][tempcoords.column].searched) {
			validSearches.push_back(tempcoords);
			numValidSearches++;
		}
	}

	if (searchResults.Cpassable == true) {

		Dmap[searchCoords.row + 1][searchCoords.column + 1].passable = true;
		Dmap[searchCoords.row + 1][searchCoords.column + 1].distance = searchResults.Cdistance;
		Dmap[searchCoords.row + 1][searchCoords.column + 1].set = true;

		coords tempcoords;
		tempcoords.row = searchCoords.row + 1;
		tempcoords.column = searchCoords.column + 1;
		if (!Dmap[tempcoords.row][tempcoords.column].searched) {
			validSearches.push_back(tempcoords);
			numValidSearches++;
		}
	}

	/*
	while (validSearches.size() > 0) {
		coords display = validSearches.back();
		std::cout << display.row << ", " << display.column << std::endl;
		validSearches.pop_back();
	}
	*/

	while (numValidSearches > 0) {
		searchCoords = validSearches.back();
		validSearches.pop_back();
		numValidSearches--;

		searchResults = DmapCheckAdjTiles(searchCoords, source);
		Dmap[searchCoords.row][searchCoords.column].searched = true;


		if (searchResults.Wpassable == true) {


			Dmap[searchCoords.row - 1][searchCoords.column].passable = true;
			Dmap[searchCoords.row - 1][searchCoords.column].distance = searchResults.Wdistance;
			Dmap[searchCoords.row - 1][searchCoords.column].set = true;

			coords tempcoords;
			tempcoords.row = searchCoords.row - 1;
			tempcoords.column = searchCoords.column;
			if (!Dmap[tempcoords.row][tempcoords.column].searched) {
				validSearches.push_back(tempcoords);
				numValidSearches++;
			}

		}

		if (searchResults.Apassable == true) {

			Dmap[searchCoords.row][searchCoords.column - 1].passable = true;
			Dmap[searchCoords.row][searchCoords.column - 1].distance = searchResults.Adistance;
			Dmap[searchCoords.row][searchCoords.column - 1].set = true;

			coords tempcoords;
			tempcoords.row = searchCoords.row;
			tempcoords.column = searchCoords.column - 1;
			if (!Dmap[tempcoords.row][tempcoords.column].searched) {
				validSearches.push_back(tempcoords);
				numValidSearches++;
			}
		}

		if (searchResults.Spassable == true) {

			Dmap[searchCoords.row + 1][searchCoords.column].passable = true;
			Dmap[searchCoords.row + 1][searchCoords.column].distance = searchResults.Sdistance;
			Dmap[searchCoords.row + 1][searchCoords.column].set = true;

			coords tempcoords;
			tempcoords.row = searchCoords.row + 1;
			tempcoords.column = searchCoords.column;
			if (!Dmap[tempcoords.row][tempcoords.column].searched) {
				validSearches.push_back(tempcoords);
				numValidSearches++;
			}
		}

		if (searchResults.Dpassable == true) {

			Dmap[searchCoords.row][searchCoords.column + 1].passable = true;
			Dmap[searchCoords.row][searchCoords.column + 1].distance = searchResults.Ddistance;
			Dmap[searchCoords.row][searchCoords.column + 1].set = true;

			coords tempcoords;
			tempcoords.row = searchCoords.row;
			tempcoords.column = searchCoords.column + 1;
			if (!Dmap[tempcoords.row][tempcoords.column].searched) {
				validSearches.push_back(tempcoords);
				numValidSearches++;
			}
		}

		if (searchResults.Qpassable == true) {

			Dmap[searchCoords.row - 1][searchCoords.column - 1].passable = true;
			Dmap[searchCoords.row - 1][searchCoords.column - 1].distance = searchResults.Qdistance;
			Dmap[searchCoords.row - 1][searchCoords.column - 1].set = true;

			coords tempcoords;
			tempcoords.row = searchCoords.row - 1;
			tempcoords.column = searchCoords.column - 1;
			if (!Dmap[tempcoords.row][tempcoords.column].searched) {
				validSearches.push_back(tempcoords);
				numValidSearches++;
			}
		}

		if (searchResults.Epassable == true) {

			Dmap[searchCoords.row - 1][searchCoords.column + 1].passable = true;
			Dmap[searchCoords.row - 1][searchCoords.column + 1].distance = searchResults.Edistance;
			Dmap[searchCoords.row - 1][searchCoords.column + 1].set = true;

			coords tempcoords;
			tempcoords.row = searchCoords.row - 1;
			tempcoords.column = searchCoords.column + 1;
			if (!Dmap[tempcoords.row][tempcoords.column].searched) {
				validSearches.push_back(tempcoords);
				numValidSearches++;
			}
		}

		if (searchResults.Zpassable == true) {

			Dmap[searchCoords.row + 1][searchCoords.column - 1].passable = true;
			Dmap[searchCoords.row + 1][searchCoords.column - 1].distance = searchResults.Zdistance;
			Dmap[searchCoords.row + 1][searchCoords.column - 1].set = true;

			coords tempcoords;
			tempcoords.row = searchCoords.row + 1;
			tempcoords.column = searchCoords.column - 1;
			if (!Dmap[tempcoords.row][tempcoords.column].searched) {
				validSearches.push_back(tempcoords);
				numValidSearches++;
			}
		}

		if (searchResults.Cpassable == true) {

			Dmap[searchCoords.row + 1][searchCoords.column + 1].passable = true;
			Dmap[searchCoords.row + 1][searchCoords.column + 1].distance = searchResults.Cdistance;
			Dmap[searchCoords.row + 1][searchCoords.column + 1].set = true;

			coords tempcoords;
			tempcoords.row = searchCoords.row + 1;
			tempcoords.column = searchCoords.column + 1;
			if (!Dmap[tempcoords.row][tempcoords.column].searched) {
				validSearches.push_back(tempcoords);
				numValidSearches++;
			}
		}

	}



	return;
}

void world_plane::printDmap() {
	for (int i = 0; i < MAP_MAX_ROW; i++) {
		for (int j = 0; j < MAP_MAX_COLUMN; j++) {
			if (Dmap[i][j].distance < 0) {
				std::cout << 'X';
				//std::cout << Dmap[i][j].distance;
			}
			else if (Dmap[i][j].distance > 9) {
				std::cout << 9;
			}
			else {
				std::cout << Dmap[i][j].distance;
			}


		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}

bool world_plane::checkOOB(coords Loc) {
	bool returnBool = false;

	if (Loc.row > 0 || Loc.row >= MAP_MAX_ROW)
		returnBool = true;

	if (Loc.column > 0 || Loc.column >= MAP_MAX_COLUMN)
		returnBool = false;

	return returnBool;

}

char world_plane::DmapPath(coords NPCLoc) {

	int Dmin = Dmap[NPCLoc.row][NPCLoc.column].distance;
	char returnChar = 'x';
	coords Wloc = NPCLoc;
	Wloc.row--;
	coords Aloc = NPCLoc;
	Aloc.column--;
	coords Sloc = NPCLoc;
	Sloc.row++;
	coords Dloc = NPCLoc;
	Dloc.column++;
	coords Qloc = NPCLoc;
	Qloc.row--;
	Qloc.column--;
	coords Eloc = NPCLoc;
	Eloc.row--;
	Eloc.column++;
	coords Zloc = NPCLoc;
	Zloc.row++;
	Zloc.column--;
	coords Cloc = NPCLoc;
	Cloc.row++;
	Cloc.column++;


	if (Dmap[Wloc.row][Wloc.column].distance < Dmin && Dmap[Wloc.row][Wloc.column].distance >= 0) {
		Dmin = Dmap[Wloc.row][Wloc.column].distance;
		returnChar = 'w';
	}


	if (Dmap[Aloc.row][Aloc.column].distance < Dmin && Dmap[Aloc.row][Aloc.column].distance >= 0) {
		Dmin = Dmap[Aloc.row][Aloc.column].distance;
		returnChar = 'a';
	}

	if (Dmap[Sloc.row][Sloc.column].distance < Dmin && Dmap[Sloc.row][Sloc.column].distance >= 0) {
		Dmin = Dmap[Sloc.row][Sloc.column].distance;
		returnChar = 's';
	}

	if (Dmap[Dloc.row][Dloc.column].distance < Dmin && Dmap[Dloc.row][Dloc.column].distance >= 0) {
		Dmin = Dmap[Dloc.row][Dloc.column].distance;
		returnChar = 'd';
	}

	if (Dmap[Qloc.row][Qloc.column].distance < Dmin && Dmap[Qloc.row][Qloc.column].distance >= 0) {
		Dmin = Dmap[Qloc.row][Qloc.column].distance;
		returnChar = 'q';
	}


	if (Dmap[Eloc.row][Eloc.column].distance < Dmin && Dmap[Eloc.row][Eloc.column].distance >= 0) {
		Dmin = Dmap[Eloc.row][Eloc.column].distance;
		returnChar = 'e';
	}

	if (Dmap[Zloc.row][Zloc.column].distance < Dmin && Dmap[Zloc.row][Zloc.column].distance >= 0) {
		Dmin = Dmap[Zloc.row][Zloc.column].distance;
		returnChar = 'z';
	}

	if (Dmap[Cloc.row][Cloc.column].distance < Dmin && Dmap[Cloc.row][Cloc.column].distance >= 0) {
		Dmin = Dmap[Cloc.row][Cloc.column].distance;
		returnChar = 'c';
	}






	return returnChar;

}

coords world_plane::getRandomSpawnPoint() {

	coords returnCOORDS;					//literally just returns the first open space for now
	bool spaceFound = false;
	std::vector<coords> validSpawns;
	int numValidSpawns = 0;
	coords temp;
	temp.elevation = 0;
	temp.row = 0;
	temp.column = 0;
	for (int i = 0; i < MAP_MAX_ROW; i++) {
		for (int j = 0; j < MAP_MAX_COLUMN; j++) {

			if (ActiveGrid->GridTiles[i][j].passable == true) {
				spaceFound = true;
				temp.row = i;
				temp.column = j;
				validSpawns.push_back(temp);
				numValidSpawns++;
			}

		}
	}

	int randIndex = generateRandomInt(1, numValidSpawns - 5);
	returnCOORDS = validSpawns.at(randIndex);


	if (spaceFound == false) {		//error no passable tile found
		std::cout << "ERROR: NO SPAWN LOCATION FOUND" << std::endl;
	}

	return returnCOORDS;

}