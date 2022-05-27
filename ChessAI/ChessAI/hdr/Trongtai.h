#pragma once
#include <string>
using namespace std;

class Game;
class Player;

class Trongtai {
public:
	static int NORM;
	static int MATE;
	static int DRAW;
public:
	Game* game;
	string quan = "hHxXtTmM";
public:
	Trongtai();
	Trongtai(Game* game);
	void init();
public:
	void free();
	bool checkNuocdi(string&, string&);
	int checkMate(Player* player);
};


