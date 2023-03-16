#pragma once
#include <random>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

//map_gen creates character arrays

constexpr int MAP_MAX_COLUMN = 200;  
constexpr int MAP_MAX_ROW = 200;

constexpr char ROCK = '%';
constexpr char FLOOR = '.';
constexpr char DOOR = '+';
constexpr char STAIRDOWN = 'v';
constexpr char STAIRUP = '^';
constexpr char EMPTY = ' ';
constexpr char UNSEEN = '#';

struct coords {
	int row{ 0 };
	int column{ 0 };
	int elevation{ 0 };
};

struct size2d {
	int rows{ 0 };
	int columns{ 0 };
	int area = rows * columns;
};

struct adjsearch {
	int numOccurances{ 0 };
	bool W;
	bool A;
	bool S;
	bool D;
	bool Q;
	bool E;
	bool Z;
	bool C;
	bool X;
};

class MAP {
public:
	class Dungeon {
	public:
		class subDungeon {
		public:
			struct room {
				coords origin;
				int rows;
				int columns;
			};

			void createRoom();
			void drawRoom();
			subDungeon(int ID, coords ORIGIN, size2d SUBSIZE) {
				parentID = ID;
				subID = ID + 2;
				origin = ORIGIN;
				subSize = SUBSIZE;

				room.origin.row = 0;
				room.origin.column = 0;
				room.rows = 0;
				room.columns = 0;

				for (int i = 0; i < MAP_MAX_ROW; i++) {
					for (int j = 0; j < MAP_MAX_COLUMN; j++) {
						SUBTILES[i][j] = EMPTY;
					}

				}


			}

			coords getOrigin() {
				return origin;
			}

			size2d getSize() {
				return subSize;
			}

			int getParentID() {
				return parentID;
			}

			int getSubID() {
				return subID;
			}
			void checkNegative();
			void printSubDungeonData();
			char SUBTILES[MAP_MAX_ROW][MAP_MAX_COLUMN];
		private:
			coords origin;
			size2d subSize;
			int parentID;
			int subID;
			room room;

		};

		void splitInit();
		void split4();

		subDungeon POP_SUB_DUNGEON() {
			subDungeon returnSub = subDungeonsList.back();
			subDungeonsList.pop_back();
			numSubDungeons--;
			return returnSub;
		}

		void splitSub(subDungeon sub, char HorV);
		void createRooms();
		void drawRectangle(coords origin, size2d size);
		void drawSubDungeons();
		void connectRooms();

		//returns a search object containing the number of nearby occurances of the symbol and the directions of those occurances
		adjsearch checkAdjacentTiles(coords startPoint, char symbol);

		//return true if the symbol exists after start point on it's row or column
		bool checkEndOfRow(coords startPoint, char symbol);
		bool checkEndOfColumn(coords startPoint, char symbol);

		Dungeon(int IDnum, int elevation, int maxRows, int maxColumns) {
			ID = IDnum;
			origin.row = 0;
			origin.column = 0;
			origin.elevation = elevation;
			max.rows = maxRows;
			max.columns = maxColumns;
			numSubDungeons = 0;

			for (int i = 0; i < MAP_MAX_ROW; i++) {
				for (int j = 0; j < MAP_MAX_COLUMN; j++) {
					tiles[i][j] = ROCK;
				}
			}

		}
		char tiles[MAP_MAX_ROW][MAP_MAX_COLUMN];
		size2d getSize() {
			return max;
		}

	private:
		int ID;
		coords origin;
		size2d max;
		int numSubDungeons;
		std::vector<subDungeon> subDungeonsList;

	};

	void AddBSPbasic();
	void PrintFirstDungeon();

	MAP() {
		numDungeons = 0;
	}


	//private:
	//Add print to file functions

	//then add functions later to read chars from files

	int numDungeons;
	std::vector<Dungeon>DungeonList;

	void placeMapTerrainSymbol(coords location, char symbol);
	char getMapSymbol(coords location);


};

static int generateRandomInt() {
	std::mt19937_64 mt1(std::chrono::steady_clock::now().time_since_epoch().count());
	int num = mt1();

	num = abs(num);
	//std::cout << "generated random int: " << num << std::endl;
	return num;
}

static int generateRandomInt(int lowerBound, int upperBound) {
	std::mt19937_64 mt1(std::chrono::steady_clock::now().time_since_epoch().count());
	int num = mt1();
	num = abs(num);
	int modBounds = (upperBound - lowerBound + 1);
	if (modBounds == 0) {
		modBounds = 1;
	}
	int rangedNum = (num % modBounds) + lowerBound;
	return rangedNum;
}

static void printTilesToFile(std::string fileName, char(&tiles)[MAP_MAX_ROW][MAP_MAX_COLUMN]) {
	std::ofstream outFile;
	outFile.open(fileName);

	if (!outFile) {
		std::cout << "could not open file.";
	}

	for (int i = 0; i < MAP_MAX_ROW; i++) {
		for (int j = 0; j < MAP_MAX_COLUMN; j++) {
			outFile << tiles[i][j];
		}
		outFile << '\n';
	}
	outFile << '\n';

	outFile.close();

	return;
}

static void printTiles(char(&tiles)[MAP_MAX_ROW][MAP_MAX_COLUMN]) {
	for (int i = 0; i < MAP_MAX_ROW; i++) {
		for (int j = 0; j < MAP_MAX_COLUMN; j++) {
			std::cout << tiles[i][j];
		}
		std::cout << '\n';
	}
	std::cout << '\n';
	return;
}

