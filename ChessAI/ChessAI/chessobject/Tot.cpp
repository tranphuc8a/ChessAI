#include "../hdr/Tot.h"
#include "../hdr/ChessBoard.h"
#include "../hdr/Point.h"
#include "../hdr/Move.h"
#include "../hdr/Player.h"
#include "../hdr/Game.h"
#include "../hdr/History.h"

Tot::Tot() : Piece() { cntMove = 0; }
Tot::Tot(Player* player) : Piece(player) { cntMove = 0; }
Tot::Tot(Player* player, int r, int c) : Piece(player, r, c) { cntMove = 0; }

void Tot::init() {
	string path;
	if (team == Player::WHITE) 	
		path = "images/" + to_string(Game::theme) + "/whitePawn.png";
	else 
		path = "images/" + to_string(Game::theme) + "/blackPawn.png";
	setView(new View(path));
	Piece::init();
	Piece::init();
}

Move Tot::move(int tr, int tc) {
	// move binh thuong, khong phai phong cap
	// eat:
	if (tc != c) {
		return eat(tr, tc);
	}
	// go straight:
	int lr = r, lc = c;
	Piece*** table = chessBoard->piece;
	table[r][c] = nullptr;
	table[tr][tc] = this;
	setPoint(tr, tc);
	cntMove++;
	return Move(0, this, lr, lc, r, c, Move::NORM);
}

Move Tot::eat(int tr, int tc) {
	Piece*** table = chessBoard->piece;
	if (!table[tr][tc]) return eatRoad(tr, tc);
	// normal eat:
	Piece* select = table[tr][tc];
	select->isDie = 1;
	Move mv(0, this, r, c, tr, tc, Move::KILL);
	mv.setKillBear(select, nullptr);
	table[tr][tc] = this;
	table[r][c] = nullptr;
	setPoint(tr, tc);
	cntMove++;
	return mv;
}
Move Tot::eatRoad(int tr, int tc) {
	// an tot qua duong
	Piece*** table = chessBoard->piece;
	Piece* select = table[r][tc];
	select->isDie = 1;
	Move mv(0, this, r, c, tr, tc, Move::SKILL);
	mv.setKillBear(select, nullptr);
	table[tr][tc] = this;
	table[r][c] = nullptr;
	table[r][tc] = nullptr;
	setPoint(tr, tc);
	cntMove++;
	return mv;
}
string Tot::getClassName() {
	return "i";
}


vector<Point> Tot::updateTarget() {
	if (isDie) return {};
	target.clear();
	int x, y;
	int a = 1;
	if (team == Player::WHITE) a = -1;
	x = r + a;
	y = c - 1;
	if (isTarget(x, y)) target.push_back(Point(x, y));
	y = c + 1;
	if (isTarget(x, y)) target.push_back(Point(x, y));
	y = c;
	x = r + a;
	if (isTarget(x, y)) target.push_back(Point(x, y));
	x = x + a;
	if (isTarget(x, y)) target.push_back(Point(x, y));
	return target;
}
vector<Point> Tot::updateKiemsoat() {
	if (isDie) return {};
	kiemsoat.clear();
	int x, y;
	int a = 1;
	if (team == Player::WHITE) a = -1;
	x = r + a;
	y = c - 1;
	if (isKiemsoat(x, y)) {
		kiemsoat.push_back(Point(x, y));
	}
	y = c + 1;
	if (isKiemsoat(x, y)) {
		kiemsoat.push_back(Point(x, y));
	}
	return kiemsoat;
}
bool Tot::isKiemsoat(int x, int y) { // can eat viral's king at (x, y)?
	if (isDie || !inBound(x, y)) return false;
	Piece*** table = chessBoard->piece;
	if (team == Player::WHITE) {
		return x + 1 == r && (c - 1 == y || c + 1 == y);
	}
	return x - 1 == r && (c - 1 == y || c + 1 == y);
}
bool Tot::isTarget(int x, int y) { // co thi di den o (x, y) hay khong?
	if (isDie || !inBound(x, y)) return false;
	Piece*** table = chessBoard->piece;
	if (y == c) { // di thang:
		// kiem tra abs(x - c) <= 2 && khong vuong quan nao
		if (table[x][y]) return false;
		if (team == Player::WHITE) {
			if (!(x + 1 == r || x + 2 == r)) return false;
			if (x + 2 == r) {
				if (table[x + 1][c]) return false;
				if (cntMove > 0) return false;
			}
		}
		else {
			if (!(x - 1 == r || x - 2 == r)) return false;
			if (x - 2 == r) {
				if (cntMove > 0) return false;
				if (table[x - 1][c]) return false;
			}
		}
		return Try(x, y);
	}
	// an cheo:
	if (!isKiemsoat(x, y)) return false;
	Piece* select = table[x][y];
	if (!select) { // an tot qua duong:
		Move befMove = player->game->history.top();
		if (!befMove.piece) return false;
		Piece* lastPiece = befMove.piece;
		if (lastPiece->getClassName() != "i") return false;
		if (lastPiece->cntMove != 1) return false;
		if (lastPiece->r != r || lastPiece->c != y) return false;
		return true;
	}
	else {
		// cung team:
		if (select->team == team) return false;
		return Try(x, y);
	}
}
