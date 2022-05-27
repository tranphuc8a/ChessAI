#include "../hdr/AI.h"
#include "../hdr/Game.h"
#include "../hdr/Piece.h"
#include "../hdr/ChessBoard.h"
#include "../hdr/Point.h"
#include "../hdr/History.h"
#include "time.h"
#include <algorithm>

AI::AI() : Player() {
	depth = 3;
	pieceVal['V'] = 0;
	pieceVal['H'] = 900;
	pieceVal['X'] = 500;
	pieceVal['M'] = 300;
	pieceVal['T'] = 300;
	pieceVal['i'] = 100;
}

AI::AI(int team, Game* game) : AI() {
	chessBoard = nullptr;
	this->team = team;
	this->game = game;
}

AI::AI(int team, Game* game, int maxdepth) : AI(team, game) {
	depth = maxdepth;
}

string AI::getClassName() {
	return "AI";
}

vector<AI::SimpleMove> AI::getMove(Player* pl) {
	if (!pl) return {};
	vector<SimpleMove> listMove;
	vector<Piece *> piece = pl->piece;
	vector<Point> vec;
//	Piece*** table = chessBoard->piece;
//	int p;
	int r, c;
//	Piece* P;
	for (int i = 1; i <= 16; i++) {
		if (piece[i] && (!piece[i]->isDie)) {
			r = piece[i]->r, c = piece[i]->c;
			vec = piece[i]->updateTarget();
			for (auto &jt : vec) {
				if (piece[i]->getClassName() == "i" && (jt.r == 1 || jt.r == 8)) {
					listMove.push_back(SimpleMove(r, c, jt.r, jt.c, 'H', pieceVal['H']));
					listMove.push_back(SimpleMove(r, c, jt.r, jt.c, 'X', pieceVal['X']));
					listMove.push_back(SimpleMove(r, c, jt.r, jt.c, 'T', pieceVal['T']));
					listMove.push_back(SimpleMove(r, c, jt.r, jt.c, 'M', pieceVal['M']));
				}
				else {
//					p = 0;
//					P = table[jt.r][jt.c];
//					if (P) p = pieceVal[P->getClassName().front()];
					listMove.push_back(SimpleMove(r, c, jt.r, jt.c, 0));
				}
			}
		}
	}
//	sort(begin(listMove), end(listMove));
	return listMove;
}

void AI::move() {
	cur = this;
	SimpleMove rs = thinking();
	Move mv = chessBoard->move(rs.sr, rs.sc, rs.tr, rs.tc, rs.pc);
	//	if (mv == NULL) {
	//		cout << rs.sr << rs.sc << rs.tr << rs.tc << " ";
	//		return;
	//	}
	game->render();
	game->history.push(mv);
	cout << mv.to_string() << endl;
	
	// degbug:
//	auto& table = game->chessBoard->kiemsoat;
//	for (int i = 1; i <= 8; i++) {
//		for (int j = 1; j <= 8; j++) {
//			table[i][j][Player::WHITE].clear();
//			table[i][j][Player::BLACK].clear();
//		}
//	}
//	update();
//	rival->update();
//	chessBoard->updateKiemsoat();
}

AI::SimpleMove AI::random() {
	srand((time_t) time(NULL));
	int id = 0;
	do {
		id = rand() % 16 + 1;
	} while (piece[id] == NULL or piece[id]->isDie or piece[id]->updateTarget().empty());
	auto vec = piece[id]->updateTarget();
	int id2 = rand() % vec.size();
	int pc = 0;
	if (piece[id]->getClassName() == "i" && (vec[id2].r == 1 or vec[id2].r == 8)) {
		pc = "HXMT"[rand() % 4];
	}
	return SimpleMove(piece[id]->r, piece[id]->c, vec[id2].r, vec[id2].c, (char)pc);
}

AI::SimpleMove AI::thinking() {
	cout << "AI thinking..." << endl;
	cout << "Try: " << Piece::t << endl;
	t = 0;
	hr = 0;
	return random();
}

