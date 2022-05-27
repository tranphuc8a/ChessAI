#pragma once
#include <string>
#include <vector>
#include <map>
#include "Node.h"
using namespace std;

class Game;
class ChessBoard;
class Piece;

class Player : public Node{
public:
	static int WHITE;
	static int BLACK;
	int team;
	Game* game;
	ChessBoard* chessBoard;

	vector<Piece* > piece;
	Player* rival;

public:
	Player();
	virtual void init(ChessBoard *, Player*);
public:
	void free();
	void initPiece();
	virtual void move() = 0;
	virtual string getClassName() = 0;
	bool contains(Piece* p);
	virtual void update();

};


