#pragma once
#include "Piece.h"
class Player;
class Move;

class Tot : public Piece {
public:
	Tot();
	Tot(Player* player);
	Tot(Player* player, int r, int c);
	void init() override;
public:
	Move move(int tr, int tc) override;
	Move eat(int tr, int tc);
	Move eatRoad(int tr, int tc);
	string getClassName() override;
	vector<Point> updateTarget() override;
	vector<Point> updateKiemsoat() override;
	bool isKiemsoat(int x, int y) override;
	bool isTarget(int x, int y) override;
};
