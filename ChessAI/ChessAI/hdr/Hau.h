#pragma once
#include "Piece.h"
class Hau : public Piece {
public:
	static vector<Point> cango;
public:
	Hau();
	Hau(Player* player);
	Hau(Player* player, int r, int c);
	void init() override;
public:
	Move move(int tr, int tc) override;
	string getClassName() override;
	vector<Point> updateTarget() override;
	vector<Point> updateKiemsoat() override;
	bool isKiemsoat(int x, int y) override;
	bool isTarget(int x, int y) override;
};


