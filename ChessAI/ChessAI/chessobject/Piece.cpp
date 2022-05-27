#include "../hdr/Piece.h"
#include "../hdr/Player.h"
#include "../hdr/ChessBoard.h"
#include "../hdr/Game.h"
#include "../hdr/Vua.h"
#include "../hdr/Point.h"

vector<Piece *> Piece::lsPiece;

Piece::Piece() {
	cntMove = 0;
	isDie = false;
	lsPiece.push_back(this);
}

Piece::Piece(Player* player) : Piece() {
	cntMove = 0;
	if (player == NULL) return;
	this->player = player;
	this->team = player->team;
}
Piece::Piece(Player* player, int r, int c) : Piece(player) {
	cntMove = 0;
	this->r = r;
	this->c = c;
	this->team = player->team;
};

void Piece::init() {
	if (player){
		this->setScene(player->game->scene);
	}
	int zoom = 50;
	set(zoom * (c - 1), zoom * (r - 1), zoom, zoom);
}

void Piece::setPoint(int x, int y) {
	r = x, c = y;
	set(50 * (c - 1), 50 * (r - 1), 50, 50);
}

vector<Point> Piece::updateTarget() {
	target.clear();
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (isTarget(i, j)) {
				target.push_back(Point(i, j));
			}
		}
	}
	return target;
};

vector<Point> Piece::updateKiemsoat() {
	vector<Point> kiemsoat;
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (isKiemsoat(i, j)) {
				kiemsoat.push_back(Point(i, j));
			}
		}
	}
	return kiemsoat;
}

void Piece::reupdate() {
//	auto& ks = chessBoard->kiemsoat;
//	auto& tg = chessBoard->target;
//	for (auto pnt : kiemsoat) {
//		ks[pnt.r][pnt.c][team].erase(this);
//		tg[pnt.r][pnt.c][team].erase(this);
//	}
}

void Piece::die() {
	this->isDie = 1;
	reupdate();
}

void Piece::alive() {
	this->isDie = 0;
	update();
	chessBoard->piece[r][c] = this;
}

void Piece::update() {
	updateKiemsoat();
	updateTarget();
}


bool Piece::inBound(int x, int y) {
	return 1 <= x && x <= 8 && 1 <= y && y <= 8;
}

int Piece::t = 0;
bool Piece::Try(int x, int y) {
//	t++;
	Piece*** table = chessBoard->piece;
	// cho di thu va kiem tra vua khong bi checking:
	// luu bien truoc khi thu
	int lr = r, lc = c;
	Piece* l1 = table[r][c], * l2 = table[x][y];
	// di thu:
	if (l2) l2->isDie = 1;
	table[x][y] = this, table[r][c] = nullptr;
	r = x, c = y;
	// kiem tra xem vua co bi chieu?
	bool ok = !vua->beChecking();
//	vector<Piece*> rival = player->rival->piece;
//	for (int i = 1; i <= 16; i++) {
//		if (rival[i] && !rival[i]->isDie) {
//			if (rival[i]->isKiemsoat(vua->r, vua->c)) {
//				ok = false;
//				break;
//			}
//		}
//	}
	// phuc hoi:
	r = lr, c = lc;
	if (l2) l2->isDie = 0;
	table[x][y] = l2, table[r][c] = l1;
	return ok;
}



