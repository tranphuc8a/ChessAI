#include "../hdr/Hau.h"
#include "../hdr/Point.h"
#include "../hdr/Player.h"
#include "../hdr/ChessBoard.h"
#include "../hdr/Move.h"
#include "../hdr/Game.h"

Hau::Hau() : Piece() {}
Hau::Hau(Player* player) : Piece(player) {
	if (team == Player::BLACK) {
		r = 1, c = 4;
	}
	else {
		r = 8, c = 4;
	}
}
Hau::Hau(Player* player, int r, int c) : Piece(player, r, c) {}
void Hau::init() {
	string path;
	if (team == Player::WHITE) 	
		path = "images/" + to_string(Game::theme) + "/whiteQueen.png";
	else 
		path = "images/" + to_string(Game::theme) + "/blackQueen.png";
	setView(new View(path));
	Piece::init();
}

Move Hau::move(int tr, int tc) {
	// update for chessBoard, killed Piece, this piece and create a Move
	int lr = r, lc = c;
	Piece*** table = chessBoard->piece;
	Piece* select = table[tr][tc];
	int type = Move::NORM;
	if (select) {
		select->isDie = 1;
		type = Move::KILL;
	}
	table[r][c] = NULL;
	table[tr][tc] = this;
	setPoint(tr, tc);
	cntMove++;

	Move rs(0, this, lr, lc, r, c, type);
	rs.setKillBear(select, NULL);
	return rs;
}
string Hau::getClassName() {
	return "H";
}

vector<Point> Hau::updateTarget() {
	if (isDie) return {};
	target.clear();
	int x, y;
	for (int a = -1; a <= 1; a++) {
		for (int b = -1; b <= 1; b++) {
			if (!a && !b) continue;
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
vector<Point> Hau::updateKiemsoat() {
	if (isDie) return {};
	kiemsoat.clear();
	int x, y;
	for (int a = -1; a <= 1; a++) {
		for (int b = -1; b <= 1; b++) {
			if (!a && !b) continue;
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
bool Hau::isKiemsoat(int x, int y) {
	if (isDie || !inBound(x, y)) return false;
	if (x == r && y == c) return false;
	Piece*** table = chessBoard->piece;
	int l, h;
	if (x == r) {
		l = min(c, y) + 1;
		h = max(c, y) - 1;
		for (int i = l; i <= h; i++) {
			if (table[r][i]) return false;
		}
		return true;
	}
	if (y == c) {
		l = min(x, r) + 1;
		h = max(x, r) - 1;
		for (int i = l; i <= h; i++) {
			if (table[i][c]) return false;
		}
		return true;
	}
	if (x - y == r - c) {
		l = min(x, r) + 1;
		h = max(x, r) - 1;
		for (int i = l; i <= h; i++) {
			if (table[i][i + c - r]) return false;
		}
		return true;
	}
	if (x + y == r + c) {
		l = min(x, r) + 1;
		h = max(x, r) - 1;
		for (int i = l; i <= h; i++) {
			if (table[i][c + r - i]) return false;
		}
		return true;
	}
	return false;
}
bool Hau::isTarget(int x, int y) { // co thi di den o (x, y) hay khong?
	if (!isKiemsoat(x, y)) return false;
	// o (x, y) chua quan minh dang dung:
	Piece* select = chessBoard->piece[x][y];
	if (select && select->team == team) return false;

	return Try(x, y);
}



