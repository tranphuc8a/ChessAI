#pragma once

#include <string>
#include <vector>
#include "Node.h"
#include "View.h"
#include "Point.h"
#include "Move.h"
using namespace std;

class Vua;
class Player;
class ChessBoard;

class Piece : public Node{
public:
	int id = 0;
	Vua* vua = nullptr;
	int r = 0, c = 0;
	Player* player = nullptr;

	int cntMove = 0;
	bool isDie = 0;
	int team = 0;
	ChessBoard* chessBoard = nullptr;

	vector<Point> kiemsoat, target;
	static int t;
	static vector<Piece *> lsPiece;
	// kiemsoat: vi tri ma neu vua doi phuong dat o do, this co the an ngay
	// target: vi tri ma this co the di chuyen den (co the di chuyen thuong, co the an)
public:
	Piece();
	Piece(Player* player);
	Piece(Player* player, int r, int c);
	virtual void init();
public:
	virtual Move move(int tr, int tc) = 0;
	virtual string getClassName() = 0;
	virtual vector<Point> updateTarget();
	virtual vector<Point> updateKiemsoat();
	virtual bool isKiemsoat(int x, int y) = 0;
	virtual bool isTarget(int x, int y) = 0;

	void setPoint(int x, int y);

	bool inBound(int x, int y);
	void die();
	void alive();
	void reupdate();
	void update();
	bool Try(int x, int y);
};


