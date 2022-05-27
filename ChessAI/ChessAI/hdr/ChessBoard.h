#pragma once
#include <vector>
#include <iostream>
#include <set>
#include "Node.h"
#include "Move.h"
using namespace std;

template <class T>
void remove(vector<T>& a, T val);

class Piece;
class Game;

class ChessBoard : public Node {
public:
	Piece*** piece;
	vector<Piece*> kiemsoat[9][9][3];
	vector<Piece*> target[9][9][3];
	Game* game;
public:
	ChessBoard();
	ChessBoard(Game* game);
	void init();

public:
	void free();
	// for input by pointer:
	Move phongcap(Piece* select, int tr, int tc);
	Move move(int sr, int sc, int tr, int tc);
	// for AI:
	Move move(int sr, int sc, int tr, int tc, char pc);
	// for input by interface:
	Move move(string src, string tg);
	Move phongcap(Piece* select, int tr, int tc, char newPiece);
	void back();
	
	void updateTarget();
	void updateKiemsoat();
	void update() override;
	void render() override;
};




