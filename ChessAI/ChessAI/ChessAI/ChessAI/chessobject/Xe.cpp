#include "../hdr/Xe.h"
#include "../hdr/ChessBoard.h"
#include "../hdr/Move.h"
#include "../hdr/Player.h"
#include "../hdr/Point.h"
#include "../hdr/Game.h"

Xe::Xe() : Piece() { cntMove = 0; }
Xe::Xe(Player* player) : Piece(player) {
	cntMove = 0;
};
Xe::Xe(Player* player, int r, int c) : Piece(player, r, c) {
	cntMove = 0;
};
void Xe::init() {
	string path;
	if (team == Player::WHITE) 	
		path = "images/" + to_string(Game::theme) + "/whiteRook.png";
	else 
		path = "images/" + to_string(Game::theme) + "/blackRook.png";
	setView(new View(path));
	Piece::init();
}

Move Xe::move(int tr, int tc) {
	// update for chessBoard, killed Piece, this piece and create a Move
	int lr = r, lc = c;
	Piece*** table = chessBoard->piece;
	Piece* select = table[tr][tc];
	int type = Move::NORM;
	if (select) {
		select->isDie = 1;
		type = Move::KILL;
	}
	table[r][c] = nullptr;
	table[tr][tc] = this;
	setPoint(tr, tc);

	Move rs(0, this, lr, lc, r, c, type);
	rs.setKillBear(select, nullptr);
	cntMove++;
	return rs;
};
string Xe::getClassName() {
	return "X";
};


vector<Point> Xe::updateTarget() {
	if (isDie) return {};
	target.clear();
	int x, y;
	for (int a = -1; a <= 1; a++) {
		for (int b = -1; b <= 1; b++) {
			if (!((a + b == 1) || (a + b == -1))) continue;
			x = r, y = c;
			for (int i = 1; i <= 8; i++) {
				x += a, y += b;
				if (!inBound(x, y)) break;
				if (isTarget(x, y))
					target.push_back(Point(x, y));
			}
		}
	}
	return target;
}
vector<Point> Xe::updateKiemsoat() {
	if (isDie) return {};
	kiemsoat.clear();
	int x, y;
	for (int a = -1; a <= 1; a++) {
		for (int b = -1; b <= 1; b++) {
			if (!((a + b == 1) || (a + b == -1))) continue;
			x = r, y = c;
			for (int i = 1; i <= 8; i++) {
				x += a, y += b;
				if (!inBound(x, y)) break;
				if (isKiemsoat(x, y)) {
					kiemsoat.push_back(Point(x, y));
				}
			}
		}
	}
	return kiemsoat;
}
bool Xe::isKiemsoat(int x, int y) {	// can eat viral's king at (x, y)?
	if (isDie || !inBound(x, y)) return false;
	if (x == r && y == c) return false;
	Piece*** table = chessBoard->piece;
	int l, h;
	if (x == r) {
		l = min(c, y) + 1, h = max(c, y) - 1;
		for (int i = l; i <= h; i++) {
			if (table[r][i]) return false;
		}
		return true;
	}
	if (y == c) {
		l = min(x, r) + 1, h = max(x, r) - 1;
		for (int i = l; i <= h; i++) {
			if (table[i][c]) return false;
		}
		return true;
	}
	return false;
}
bool Xe::isTarget(int x, int y) { // co thi di den o (x, y) hay khong?
	if (!isKiemsoat(x, y)) return false;
	// o (x, y) chua quan minh dang dung:
	Piece* select = chessBoard->piece[x][y];
	if (select && select->team == team) return false;

	return Try(x, y);
}




