#include "../hdr/Tuong.h"
#include "../hdr/Move.h"
#include "../hdr/ChessBoard.h"
#include "../hdr/Point.h"
#include "../hdr/Player.h"
#include "../hdr/Game.h"

Tuong::Tuong() : Piece() {}
Tuong::Tuong(Player* player) : Piece(player) {}
Tuong::Tuong(Player* player, int r, int c) : Piece(player, r, c) {}

void Tuong::init() {
	string path;
	if (team == Player::WHITE) 	
		path = "images/" + to_string(Game::theme) + "/whiteBishop.png";
	else 
		path = "images/" + to_string(Game::theme) + "/blackBishop.png";
	setView(new View(path));
	Piece::init();
}

Move Tuong::move(int tr, int tc) {
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
	rs.setKillBear(select, NULL);
	cntMove++;
	return rs;
}
string Tuong::getClassName() {
	return "T";
}

vector<Point> Tuong::updateTarget() {
	if (isDie) return {};
	target.clear();
	int x, y;
	for (int a = -1; a <= 1; a += 2) {
		for (int b = -1; b <= 1; b += 2) {
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
vector<Point> Tuong::updateKiemsoat() {
	if (isDie) return {};
	kiemsoat.clear();
	int x, y;
	for (int a = -1; a <= 1; a += 2) {
		for (int b = -1; b <= 1; b += 2) {
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
bool Tuong::isKiemsoat(int x, int y) { // can eat viral's king at (x, y)?
	if (isDie || !inBound(x, y)) return false;
	if (x == r && y == c) return false;
	Piece*** table = chessBoard->piece;
	// check between this and (x, y)
	int l, h;
	if (x - y == r - c) {
		l = min(x, r) + 1, h = max(x, r) - 1;
		for (int i = l; i <= h; i++) {
			if (table[i][i + c - r]) return false;
		}
		return true;
	}
	if (x + y == r + c) {
		l = min(x, r) + 1, h = max(x, r) - 1;
		for (int i = l; i <= h; i++) {
			if (table[i][c + r - i]) return false;
		}
		return true;
	}
	return false;
}
bool Tuong::isTarget(int x, int y) { // co thi di den o (x, y) hay khong?
	if (!isKiemsoat(x, y)) return false;
	// o (x, y) chua quan minh dang dung:
	Piece* select = chessBoard->piece[x][y];
	if (select != NULL && select->team == team) return false;

	return Try(x, y);
}



