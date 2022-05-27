#pragma once
#include "Player.h"
#include <map>
using namespace std;

class AI : public Player {
public:
	struct SimpleMove {
		int sr, sc, tr, tc;
		char pc; int point;
		SimpleMove() : SimpleMove(0, 0, 0, 0) {}
		SimpleMove(int a, int b, int c, int d) {
			sr = a, sc = b, tr = c, tc = d;
			pc = 0; point = INT_MIN;
		}
		SimpleMove(int a, int b, int c, int d, char p) : SimpleMove(a, b, c, d) { pc = p; }
		SimpleMove(int a, int b, int c, int d, char p, int pnt) : SimpleMove(a, b, c, d, p) { point = pnt; }
		friend bool operator < (const SimpleMove& m1, const SimpleMove& m2) {
			return m1.point < m2.point;
		}
	};
	SimpleMove tree[4];
	int depth;
public:
	int t = 0, hr = 0;
	Player* cur;
	map<char, int> pieceVal;
public:
	// constructor:
	AI();
	AI(int team, Game* game);
	AI(int team, Game* game, int maxdepth);
public:
	// AI.cpp:
	string getClassName() override;
	void move() override;
	vector<SimpleMove> getMove(Player* player);
	virtual SimpleMove thinking();
	SimpleMove random();
	
public: // heuristic
	// Heuristic.cpp:
	int heuristic(Player* cur);
	int chatluongquan(Player* player);
	int vitriquan(Player* player);
	int space(Player* player);
	int nearKing(Player* player);
	int lienketquan();
};


