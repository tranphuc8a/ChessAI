#include "../hdr/Ma.h"
#include <vector>
#include "../hdr/Point.h"
#include "../hdr/Player.h"
#include "../hdr/Game.h"
#include "../hdr/ChessBoard.h"
#include "../hdr/Move.h"
using namespace std;

vector<Point> Ma::cango{
	Point(1, 2), Point(1, -2), Point(-1, 2), Point(-1, -2),
	Point(2, 1), Point(2, -1), Point(-2, 1), Point(-2, -1)
};

Ma::Ma() : Piece() {}
Ma::Ma(Player* player) : Piece(player) {
};
Ma::Ma(Player* player, int r, int c) : Piece(player, r, c) {
};
void Ma::init() {
	string path;
	if (team == Player::WHITE) 	
		path = "images/" + to_string(Game::theme) + "/whiteKnight.png";
	else 
		path = "images/" + to_string(Game::theme) + "/blackKnight.png";
	setView(new View(path));
	Piece::init();
	Piece::init();
}

Move Ma::move(int tr, int tc) {
	int lr = r, lc = c;
	Piece*** table = player->game->chessBoard->piece;
	Piece* select = table[tr][tc];
	int type = Move::NORM;
	if (select) {
		select->isDie = 1;;
		type = Move::KILL;
	}
	table[r][c] = nullptr;
	table[tr][tc] = this;
	setPoint(tr, tc);
	Move rs(0, this, lr, lc, r, c, type);
	rs.setKillBear(select, NULL);
	cntMove++;
	return rs;
};
string Ma::getClassName() {
	return "M";
};

vector<Point> Ma::updateTarget() {
	if (isDie) return {};
	target.clear();
	int x, y;
	for (auto it : Ma::cango) {
		x = r + it.r, y = c + it.c;
		if (isTarget(x, y))
			target.push_back(Point(x, y));
	}
	return target;
}
vector<Point> Ma::updateKiemsoat() {
	if (isDie) return {};
	kiemsoat.clear();
	int x, y;
	for (auto it : Ma::cango) {
		x = r + it.r, y = c + it.c;
		if (isKiemsoat(x, y)) {
			kiemsoat.push_back(Point(x, y));
		}
	}
	return kiemsoat;
}
bool Ma::isKiemsoat(int x, int y) {	// can eat viral's king at (x, y)?
	if (isDie || !inBound(x, y)) return false;	
	int a = abs(r - x), b = abs(c - y);
	if (a <= 0 || b <= 0) return false;
	return a + b == 3;
}
bool Ma::isTarget(int x, int y) { // co thi di den o (x, y) hay khong?
	if (!isKiemsoat(x, y)) return false;
	// o (x, y) chua quan minh dang dung:
	Piece* select = chessBoard->piece[x][y];
	if (select && select->team == team) return false;

	return Try(x, y);
}









