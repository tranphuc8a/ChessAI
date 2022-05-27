
#include "../hdr/Vua.h"
#include "../hdr/Player.h"
#include "../hdr/ChessBoard.h"
#include "../hdr/Move.h"
#include "../hdr/Point.h"
#include "../hdr/Game.h"


Vua::Vua() : Piece() {};
Vua::Vua(Player* player) : Piece(player) {
	cntMove = 0;
	team = player->team;
	if (team == Player::WHITE) {
		r = 8, c = 5;
	}
	else {
		r = 1, c = 5;
	}
};
Vua::Vua(Player* player, int r, int c) : Piece(player, r, c) {};

void Vua::init() {
	string path;
	if (team == Player::WHITE) 	
		path = "images/" + to_string(Game::theme) + "/whiteKing.png";
	else 
		path = "images/" + to_string(Game::theme) + "/blackKing.png";
	setView(new View(path));
	Piece::init();
}

Move Vua::move(int tr, int tc) {
	// update for chessBoard, killed Piece, this piece and create a Move
	if (abs(tc - c) == 2) {
		return nhapthanh(tr, tc);
	}
	int lr = r, lc = c;

	Piece* select = chessBoard->piece[tr][tc];
	int type = Move::NORM;
	if (select) type = Move::KILL;
	Move rs(0, this, r, c, tr, tc, type);

	chessBoard->piece[r][c] = nullptr;
	chessBoard->piece[tr][tc] = this;
	setPoint(tr, tc);

	if (select) select->die();
	rs.setKillBear(select, NULL);
	cntMove++;

	return rs;
}

Move Vua::nhapthanh(int tr, int tc) {
	Piece*** table = chessBoard->piece;
	int lr = r, lc = c;
	Piece* xe = nullptr;
	if (tc + 2 == c) { // Nhap thanh trai
		xe = chessBoard->piece[tr][1];
		xe->setPoint(tr, c - 1);
		table[r][c - 1] = xe;
		table[r][1] = nullptr;
		xe->cntMove++;
	}
	else if (tc == c + 2) { // Nhap thanh phai
		xe = chessBoard->piece[tr][8];
		xe->setPoint(tr, c + 1);
		table[r][c + 1] = xe;
		table[r][8] = nullptr;
		xe->cntMove++;
	}	
	table[r][c] = nullptr;
	table[tr][tc] = this;
	setPoint(tr, tc);
	cntMove++;
	return Move(0, this, lr, lc, r, c, Move::INN);
}


bool Vua::beChecking() {
//	vector<Piece*> rivals = player->rival->piece;
//	for (int i = 1; i <= 16; i++) {
//		if (rivals[i] && !rivals[i]->isDie && rivals[i]->isKiemsoat(r, c))
//			return true;
//	}
//	return false;
	// check pawn:
	auto &table = chessBoard->piece;
	int x, y, rs;
	if (team == Player::WHITE){
		x = r - 1;	
	} else {
		x = r + 1;
	}
	for (y = c - 1; y <= c + 1; y += 2){
		if (inBound(x, y)){
		if (table[x][y] && table[x][y]->team != team
			&& table[x][y]->getClassName() == "i")
				return 1;
		}
	}
	// check bishop, queen, rook:
	for (int a = -1; a <= 1; a++){
		for (int b = -1; b <= 1; b++){
			rs = a*a + b*b;
			if (rs == 1){ // check rook, queen
 				for (int i = 1; i <= 8; i++){
 					x = r + a*i, y = c + b*i;
					if (!inBound(x, y)) break;
					if (table[x][y]){
						if (table[x][y]->team != team && ( 
							table[x][y]->getClassName().front() == 'H' ||
							table[x][y]->getClassName().front() == 'X'
							) ) return 1;
						else break;
					}
				}
			} else if (rs == 2){ // check bishop, queen
				for (int i = 1; i <= 8; i++){
					x = r + a*i, y = c + b*i;
					if (!inBound(x, y)) break;
					if (table[x][y]){
						if (table[x][y]->team != team && ( 
							table[x][y]->getClassName().front() == 'H' ||
							table[x][y]->getClassName().front() == 'T'
							) ) return 1;
						else break;
					}
				}
			}
		}
	}
	// check knight:
	for (int a = -2; a <= 2; a++){
		if (!a) continue;
		for (int b = -1; b <= 1; b += 2){
			x = r + a;
			y = c + b*(3 - abs(a));
			if (inBound(x, y) && table[x][y]){
				if (table[x][y]->team != team && 
				table[x][y]->getClassName().front() == 'M')
					return 1;
			}
		}
	}
	return 0;
}

vector<Piece*> Vua::getChecking() {
	vector<Piece*> res;
	vector<Piece*> rivals = player->rival->piece;
	for (int i = 1; i <= 16; i++) {
		if (rivals[i] != NULL && !rivals[i]->isDie && rivals[i]->isKiemsoat(r, c))
			res.push_back(rivals[i]);
	}
	return res;
	//	auto &vec = chessBoard->kiemsoat[r][c][player->rival->team];
	//	for (auto it : vec)
	//		res.push_back(it);
	//	return res;
}

string Vua::getClassName() {
	return "V";
}

vector<Point> Vua::updateTarget() {
	if (isDie) return {};
	int x = r, y = c;
	target.clear();
	for (int a = -1; a <= 1; a++) {
		for (int b = -1; b <= 1; b++) {
			if (!a && !b) continue;
			x = r + a, y = c + b;
			if (isTarget(x, y))
				target.push_back(Point(x, y));
		}
	}
	if (cntMove == 0) {
		if (canNhapthanhtrai()) {
			target.push_back(Point(r, c - 2));
		}
		if (canNhapthanhphai()) {
			target.push_back(Point(r, c + 2));
		}
	}
	return target;
}
vector<Point> Vua::updateKiemsoat() {
	if (isDie) return {};
	int x = r, y = c;
	kiemsoat.clear();
	for (int a = -1; a <= 1; a++) {
		for (int b = -1; b <= 1; b++) {
			if (!a && !b) continue;
			x = r + a, y = c + b;
			if (isKiemsoat(x, y))
				kiemsoat.push_back(Point(x, y));
		}
	}
	return kiemsoat;
}
bool Vua::isKiemsoat(int x, int y) {
	if (!inBound(x, y)) return false;
	return abs(x - r) <= 1 && abs(y - c) <= 1;
}
bool Vua::isTarget(int x, int y) {
	if (!inBound(x, y)) return false;
	if (!isKiemsoat(x, y)) {
		if (x != r) return false;
		if (y == c + 2) return canNhapthanhphai();
		if (y == c - 2) return canNhapthanhtrai();
		return false;
	}
	vector<Piece*> rivals = player->rival->piece;
	for (int i = 1; i <= 16; i++) {
		if (rivals[i] && !rivals[i]->isDie && rivals[i]->isKiemsoat(x, y)) {
			return false;
		}
		else {
			bool cango = Try(x, y);
			if (!cango) return false;
		}
	}
	Piece* select = chessBoard->piece[x][y];
	if (select && select->team == team) return false;
	return true;
}
bool Vua::canNhapthanhtrai() {
	if (cntMove > 0) return false;
	if (beChecking()) return false;
	Piece*** table = chessBoard->piece;
	Piece* xe = table[r][1];
	if (!xe || xe->cntMove > 0) return false;
	for (int i = 2; i <= c - 1; i++) {
		if (table[r][i]) return false;
		vector<Piece*> rivals = player->rival->piece;
		for (int j = 1; j <= 16; j++) {
			if (rivals[j] && rivals[j]->isKiemsoat(r, i))
				return false;
		}
	}
	return true;
}
bool Vua::canNhapthanhphai() {
	if (cntMove > 0) return false;
	if (beChecking()) return false;
	Piece*** table = chessBoard->piece;
	Piece* xe = table[r][8];
	if (!xe || xe->cntMove > 0) return false;
	for (int i = c + 1; i <= 7; i++) {
		if (table[r][i]) return false;
		vector<Piece*> rivals = player->rival->piece;
		for (int j = 1; j <= 16; j++) {
			if (rivals[j] && rivals[j]->isKiemsoat(r, i))
				return false;
		}
	}
	return true;
}





