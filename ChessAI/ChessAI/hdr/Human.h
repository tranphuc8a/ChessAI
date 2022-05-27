#pragma once
#include "Player.h"
class EventSolver;

class Human : public Player {
public:
	EventSolver * eventSolver;
	Piece* selected = nullptr;
public:
	Human();
	Human(int team, Game* game);
	void init(ChessBoard *, Player *) override;
public:
	void move() override;
	string getClassName() override;
};

