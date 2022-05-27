#pragma once

#include "SDL.h"
#include <stack>
using namespace std;
#include "AI.h"
#include "Point.h"

using spMove = AI::SimpleMove;

class Node;
class ChessBoard;
class Game;

class EventSolver{
public:
	Game* game;
	ChessBoard* chessBoard;
	Node* selected;
//	SDL_Event event;
public:
	EventSolver();
	EventSolver(Game* game);
	void init();
public:
	spMove getMove();
	void setChessBoard(ChessBoard* cb);
	Point click(int a, int b);
};

