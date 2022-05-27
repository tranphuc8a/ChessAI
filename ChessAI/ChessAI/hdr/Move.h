#pragma once
#include <string>
using namespace std;
class Piece;
class Move {
public:
	enum MOVE {
		NORM, KILL, INN, UPP, SKILL
	};
	//	static const int NORM;
	//	static const int KILL;
	//	static const int INN;
	//	static const int UPP;
	//	static const int SKILL;
public:
	int id = 0;
	Piece* piece = nullptr;
	int sr = 0, sc = 0, tr = 0, tc = 0;
	Piece* kill = nullptr, * bear = nullptr;
	int type = 0;
	string src = "", tg = "";
public:
	Move();
	Move(int id, Piece* piece, int sr, int sc, int tr, int tc, int type);
	void setKillBear(Piece*, Piece*);
	string to_string();
};

