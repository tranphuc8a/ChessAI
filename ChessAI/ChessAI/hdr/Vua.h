#pragma once
#include "Piece.h"

class Vua : public Piece {
public:
public:
	Vua();
	Vua(Player* player);
	Vua(Player* player, int r, int c);
	void init() override;
public:
	Move move(int tr, int tc) override;
	Move nhapthanh(int tr, int tc);
	bool beChecking();
	vector<Piece*> getChecking();
	string getClassName() override;
	vector<Point> updateTarget() override;
	vector<Point> updateKiemsoat() override;
	bool isKiemsoat(int x, int y) override;
	bool isTarget(int x, int y) override;
	bool canNhapthanhtrai();
	bool canNhapthanhphai();
};


