#include "map_gen.h"

void MAP::AddBSPbasic() {

	Dungeon mainDungeon(0, 0, MAP_MAX_ROW, MAP_MAX_COLUMN);
	mainDungeon.splitInit();
	mainDungeon.split4();
	mainDungeon.createRooms();
	mainDungeon.drawSubDungeons();

	mainDungeon.connectRooms();

	DungeonList.push_back(mainDungeon);

	numDungeons++;

	return;
}

void MAP::Dungeon::subDungeon::createRoom() {
	int columns = generateRandomInt(2, origin.column - 2);
	int rows = generateRandomInt(2, origin.row - 2);

	int availableColumns = origin.column - 1;
	int availableRows = origin.row - 1;

	if (availableRows < rows) {
		rows = availableRows;
	}

	if (availableColumns < columns) {
		columns = availableColumns;
	}

	coords tempOrigin = origin;
	tempOrigin.row++;
	tempOrigin.column++;

	room.columns = columns;
	room.rows = rows;
	room.origin = tempOrigin;

	return;

}

void MAP::Dungeon::splitInit() {
	int INITSPLITVARIANCE = MAP_MAX_COLUMN / 8;  //10 for previous default

	int rand1 = generateRandomInt(1, 1000);
	bool H = false;
	bool V = false;
	coords Aorigin;
	size2d Asize;

	coords Borigin;
	size2d Bsize;

	if (rand1 <= 500) {
		H = true;

	}
	else {

	}

	//only vertical split on init for now

	V = true;
	int SplitUpperBound = max.columns + origin.column;
	int SplitLowerBound = origin.column;
	int SplitLength = SplitUpperBound - SplitLowerBound;
	int SplitMidPoint = SplitLength / 2;
	int splitPos;

	int rand = generateRandomInt(1, 10);
	if (rand <= 5) {
		splitPos = SplitMidPoint + INITSPLITVARIANCE;
	}
	else {
		splitPos = SplitMidPoint - INITSPLITVARIANCE;
	}

	Aorigin = origin;
	Borigin = origin;
	Borigin.column = origin.column + splitPos;

	Asize = max;
	Asize.columns = splitPos;
	Bsize = max;
	Bsize.columns = origin.column - splitPos;




	subDungeon subA(ID, Aorigin, Asize);
	subDungeon subB(ID, Borigin, Bsize);

	numSubDungeons = 2;

	subDungeonsList.push_back(subA);
	subDungeonsList.push_back(subB);


}

void MAP::Dungeon::splitSub(subDungeon sub, char HorV) {
	int SUBSPLITVARIANCE = 2;

	bool H = false;
	bool V = false;
	coords Aorigin;
	size2d Asize;

	coords Borigin;
	size2d Bsize;

	coords initialCoords = sub.getOrigin();
	size2d initialSize = sub.getSize();


	if (HorV == 'H') {
		H = true;


		int SplitUpperBound = initialSize.rows + initialCoords.row;
		int SplitLowerBound = initialCoords.row;
		int SplitLength = SplitUpperBound - SplitLowerBound;
		int SplitMidPoint = SplitLength / 2;
		int splitPos;

		int rand = generateRandomInt(1, 10);
		if (rand <= 5) {
			splitPos = SplitMidPoint + SUBSPLITVARIANCE;
		}
		else {
			splitPos = SplitMidPoint - SUBSPLITVARIANCE;
		}

		Aorigin = initialCoords; //

		Borigin = initialCoords;
		Borigin.row = Borigin.row + splitPos;

		Asize = initialSize; //
		Asize.rows = splitPos;
		Bsize = initialSize;
		Bsize.rows = Bsize.rows - splitPos;

	}
	else {
		V = true;

		int SplitUpperBound = initialSize.columns + initialCoords.column;
		int SplitLowerBound = initialCoords.column;
		int SplitLength = SplitUpperBound - SplitLowerBound;
		int SplitMidPoint = SplitLength / 2;
		int splitPos;

		int rand = generateRandomInt(1, 10);
		if (rand <= 5) {
			splitPos = SplitMidPoint + SUBSPLITVARIANCE;
		}
		else {
			splitPos = SplitMidPoint - SUBSPLITVARIANCE;
		}

		Aorigin = initialCoords;
		Borigin = initialCoords;
		Borigin.column = initialCoords.column + splitPos;

		Asize = initialSize;
		Asize.columns = splitPos;
		Bsize = initialSize;
		Bsize.columns = initialSize.columns - splitPos;
	}



	subDungeon subA(sub.getSubID(), Aorigin, Asize);
	subDungeon subB(sub.getSubID(), Borigin, Bsize);

	//call check negative here 
	subA.checkNegative();
	subB.checkNegative();


	numSubDungeons = numSubDungeons + 2;

	subDungeonsList.push_back(subA);
	subDungeonsList.push_back(subB);


}

void MAP::Dungeon::subDungeon::drawRoom() {

	//first fill array with EMPTY
	for (int i = 0; i < MAP_MAX_ROW; i++) {
		for (int j = 0; j < MAP_MAX_COLUMN; j++) {
			SUBTILES[i][j] = EMPTY;
		}

	}

	//fill subdungeon spaces with rock (door for testing)
	for (int i = origin.row; i < subSize.rows + origin.row; i++) {
		for (int j = origin.column; j < subSize.columns + origin.column; j++) {
			SUBTILES[i][j] = ROCK;
		}

	}

	//create temp reduced bounds
	coords TempCoords = origin;
	TempCoords.row++;
	TempCoords.column++;
	size2d TempSize = subSize;
	TempSize.rows--;
	TempSize.columns--;
	//


	//generate random rectangle <- right now it only places the rectangles at an offset from subdungeon origin
	//later i can randomly pick another suitable origin within the subdungeon
	int width = generateRandomInt(2, subSize.columns - 2);
	int height = generateRandomInt(2, subSize.rows - 2);

	int AvailableHeight = TempSize.rows;
	int AvailableWidth = TempSize.columns;


	if (AvailableHeight < height) {
		height = AvailableHeight;
	}

	if (AvailableWidth < width) {
		width = AvailableWidth;
	}

	for (int i = TempCoords.row; i < height + TempCoords.row; i++) {
		for (int j = TempCoords.column; j < width + TempCoords.column; j++) {
			SUBTILES[i][j] = FLOOR;

		}

	}

	return;

}

void MAP::Dungeon::drawSubDungeons() {

	while (!subDungeonsList.empty()) {
		//load a temporary subdungeon variable with a subdungeon and pop it from the stack
		subDungeon tempSub = subDungeonsList.back();
		subDungeonsList.pop_back();


		//insert subdungeon onto big dungeon

		for (int i = 0; i < MAP_MAX_ROW; i++) {
			for (int j = 0; j < MAP_MAX_COLUMN; j++) {
				if (tempSub.SUBTILES[i][j] != EMPTY) {
					tiles[i][j] = tempSub.SUBTILES[i][j];
				}
			}

		}


	}

	return;
}

void MAP::Dungeon::split4() {
	//called after init, so three splits here
	subDungeon TEMPSUBA = POP_SUB_DUNGEON();
	subDungeon TEMPSUBB = POP_SUB_DUNGEON();

	splitSub(TEMPSUBA, 'V');
	splitSub(TEMPSUBB, 'V');

	subDungeon TEMPSUBA1 = POP_SUB_DUNGEON();
	subDungeon TEMPSUBA2 = POP_SUB_DUNGEON();
	subDungeon TEMPSUBB1 = POP_SUB_DUNGEON();
	subDungeon TEMPSUBB2 = POP_SUB_DUNGEON();

	splitSub(TEMPSUBA1, 'H');
	splitSub(TEMPSUBA2, 'H');
	splitSub(TEMPSUBB1, 'H');
	splitSub(TEMPSUBB2, 'H');

	subDungeon TEMPSUBA11 = POP_SUB_DUNGEON();
	subDungeon TEMPSUBA12 = POP_SUB_DUNGEON();
	subDungeon TEMPSUBA21 = POP_SUB_DUNGEON();
	subDungeon TEMPSUBA22 = POP_SUB_DUNGEON();
	subDungeon TEMPSUBB11 = POP_SUB_DUNGEON();
	subDungeon TEMPSUBB12 = POP_SUB_DUNGEON();
	subDungeon TEMPSUBB21 = POP_SUB_DUNGEON();
	subDungeon TEMPSUBB22 = POP_SUB_DUNGEON();

	splitSub(TEMPSUBA11, 'H');
	splitSub(TEMPSUBA12, 'H');
	splitSub(TEMPSUBA21, 'H');
	splitSub(TEMPSUBA22, 'H');
	splitSub(TEMPSUBB11, 'H');
	splitSub(TEMPSUBB12, 'H');
	splitSub(TEMPSUBB21, 'H');
	splitSub(TEMPSUBB22, 'H');

	return;
}

void MAP::Dungeon::createRooms() {
	for (int i = 0; i < numSubDungeons; i++) {
		subDungeonsList.at(i).createRoom();
		subDungeonsList.at(i).drawRoom();
		//testcode to debug
		//subDungeonsList.at(i).printSubDungeonData();
		//printTiles(subDungeonsList.at(i).SUBTILES);
		//testcode to debug
	}
	return;
}



void MAP::PrintFirstDungeon() {


	printTiles(DungeonList.front().tiles);

	return;

}

void MAP::Dungeon::subDungeon::printSubDungeonData() {

	/*
	for (int i = 0; i < MAP_MAX_ROW; i++) {
		for (int j = 0; j < MAP_MAX_COLUMN; j++) {
			std::cout << SUBTILES[i][j];
		}
		std::cout << '\n';
	}
	std::cout << '\n';
	*/

	std::cout << "ID: " << subID << " Parent ID: " << parentID << std::endl;
	std::cout << "Origin: (" << origin.row << ", " << origin.column << ") Size: " << subSize.rows << "rows and " << subSize.columns << "columns." << std::endl;
	std::cout << std::endl;


	return;

}


void MAP::Dungeon::subDungeon::checkNegative() {
	if (subSize.rows < 0) {
		subSize.rows = abs(subSize.rows);
	}

	if (subSize.columns < 0) {
		subSize.columns = abs(subSize.columns);
	}

	return;
}


adjsearch MAP::Dungeon::checkAdjacentTiles(coords searchPoint, char symbol) {
	//initialize search object to return
	adjsearch returnSearch;
	returnSearch.numOccurances = 0;
	returnSearch.W = false;
	returnSearch.A = false;
	returnSearch.S = false;
	returnSearch.D = false;
	returnSearch.Q = false;
	returnSearch.E = false;
	returnSearch.Z = false;
	returnSearch.C = false;
	returnSearch.X = false;

	if (tiles[searchPoint.row][searchPoint.column] == symbol) {
		returnSearch.X = true;
		returnSearch.numOccurances++;
	}

	coords W = searchPoint;
	W.row = W.row - 1;
	if (W.row > 0 && W.column > 0) {
		if (tiles[W.row][W.column] == symbol) {
			returnSearch.W = true;
			returnSearch.numOccurances++;

		}

	}

	coords A = searchPoint;
	A.column = A.column - 1;
	if (A.row > 0 && A.column > 0) {
		if (tiles[A.row][A.column] == symbol) {
			returnSearch.A = true;
			returnSearch.numOccurances++;
		}

	}

	coords S = searchPoint;
	S.row = S.row + 1;
	if (S.row < MAP_MAX_ROW && S.column < MAP_MAX_COLUMN) {
		if (tiles[S.row][S.column] == symbol) {
			returnSearch.S = true;
			returnSearch.numOccurances++;
		}


	}

	coords D = searchPoint;
	D.column = D.column + 1;
	if (D.row < MAP_MAX_ROW && D.column < MAP_MAX_COLUMN) {
		if (tiles[D.row][D.column] == symbol) {
			returnSearch.D = true;
			returnSearch.numOccurances++;
		}



	}

	coords Q = searchPoint;
	Q.row--;
	Q.column--;
	if (Q.row > 0 && Q.column > 0) {
		if (tiles[Q.row][Q.column] == symbol) {
			returnSearch.Q = true;
			returnSearch.numOccurances++;
		}

	}

	coords E = searchPoint;
	E.row--;
	E.column++;
	if (E.row > 0 && E.column < MAP_MAX_COLUMN) {
		if (tiles[E.row][E.column] == symbol) {
			returnSearch.E = true;
			returnSearch.numOccurances++;
		}

	}

	coords Z = searchPoint;
	Z.row++;
	Z.column--;
	if (Z.row < MAP_MAX_ROW && E.column > 0) {
		if (tiles[Z.row][Z.column] == symbol) {
			returnSearch.Z = true;
			returnSearch.numOccurances++;
		}

	}

	coords C = searchPoint;
	C.row++;
	C.column++;
	if (C.row < MAP_MAX_ROW && C.column < MAP_MAX_COLUMN) {
		if (tiles[C.row][C.column] == symbol) {
			returnSearch.C = true;
			returnSearch.numOccurances++;
		}

	}



	return returnSearch;
}

bool MAP::Dungeon::checkEndOfRow(coords startPoint, char symbol) {


	bool returnBool = false;
	for (int i = startPoint.column; i < MAP_MAX_COLUMN; i++) {
		if (tiles[startPoint.row][i] == symbol) {

			returnBool = true;
			break;
		}


	}

	return returnBool;


}

bool MAP::Dungeon::checkEndOfColumn(coords startPoint, char symbol) {
	bool returnBool = false;
	for (int i = startPoint.row; i < MAP_MAX_ROW; i++) {
		if (tiles[i][startPoint.column] == symbol) {
			returnBool = true;
			break;

		}


	}

	return returnBool;
}


void MAP::Dungeon::connectRooms() {

	//identify which wall tiles connect rooms


	//std::vector<coords> WallsToFill;


	for (int currentRow = 0; currentRow < MAP_MAX_ROW; currentRow++) {
		for (int currentCol = 0; currentCol < MAP_MAX_COLUMN; currentCol++) {

			coords currentLocation;
			currentLocation.elevation = 0;
			currentLocation.row = currentRow;
			currentLocation.column = currentCol;

			bool Edge = false;
			if (currentLocation.row == 0 || currentLocation.row == MAP_MAX_ROW || currentLocation.column == 0 || currentLocation.column == MAP_MAX_COLUMN) {
				Edge = true;
			}

			char currentLocationChar = tiles[currentRow][currentCol];

			if (currentLocationChar == ROCK && !Edge) {

				adjsearch searchResults = checkAdjacentTiles(currentLocation, FLOOR);

				if (checkEndOfRow(currentLocation, FLOOR)) {



					if (searchResults.A || searchResults.D) {


						if (searchResults.numOccurances <= generateRandomInt(1, 9))
							tiles[currentLocation.row][currentLocation.column] = FLOOR;



					}


				}

				if (checkEndOfColumn(currentLocation, FLOOR)) {


					if (searchResults.W || searchResults.S) {


						if (searchResults.numOccurances <= generateRandomInt(1, 9))
							tiles[currentLocation.row][currentLocation.column] = FLOOR;



					}


				}






			}



		}
	}

	//fill them in
/*
	for (int i = 0; i < WallsToFill.size(); i++) {
		tiles[WallsToFill.at(i).row][WallsToFill.at(i).column] = FLOOR;

	}
*/



	return;
}

void MAP::placeMapTerrainSymbol(coords location, char symbol) {
	int z = location.elevation;
	int row = location.row;
	int column = location.column;

	DungeonList.at(z).tiles[row][column] = symbol;



	return;
}

char MAP::getMapSymbol(coords location) {
	int z = location.elevation;
	int row = location.row;
	int column = location.column;

	char returnChar;
	returnChar = DungeonList.at(z).tiles[row][column];
	return returnChar;

}


