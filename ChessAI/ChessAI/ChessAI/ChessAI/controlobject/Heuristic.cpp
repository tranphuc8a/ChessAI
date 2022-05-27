#include "../hdr/AI.h"
#include <algorithm>
#include "../hdr/Piece.h"
#include "../hdr/ChessBoard.h"
#include "../hdr/Game.h"
#include "../hdr/Vua.h"
#include "../hdr/History.h"

int pawntable[9][9] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{0, 5, 10, 10, 0, 0, 10, 10, 5},
	{0, 10, 0, 0, 10, 10, 0, 0, 10},
	{0, 5, 0, 0, 20, 20, 0, 0, 5},
	{0, 5, 5, 10, 25, 25, 10, 5, 5},
	{0, 10, 10, 20, 30, 30, 20, 10, 10},
	{0, 50, 50, 50, 50, 50, 50, 50, 50},
	{0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int knightstable[9][9] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 2, 1, 0, 5, 5, 0, 1, 2},
	{0, 2, 3, 5, 10, 10, 5, 3, 2},
	{0, 2, 0, 10, 15, 15, 10, 0, 2},
	{0, 2, 5, 10, 15, 15, 10, 5, 2},
	{0, 2, 0, 5, 15, 15, 5, 0, 2},
	{0, 3, 3, 3, 3, 3, 3, 3, 3},
	{0, 0, 2, 3, 3, 3, 3, 2, 0}
};

int bishopstable[9][9] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 5, 2, 0, 0, 2, 5, 0},
	{0, 0, 10, 10, 10, 10, 10, 10, 0},
	{0, 0, 10, 10, 10, 10, 10, 10, 0},
	{0, 0, 10, 10, 10, 10, 10, 10, 0},
	{0, 0, 0, 5, 10, 10, 5, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int rookstable[9][9] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{0, -5, 2, 5, 10, 10, 5, 2, -5},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 5, 10, 10, 10, 10, 10, 10, 5},
	{0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int queenstable[9][9] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{0, 0, 1, 1, 2, 2, 1, 1, 0},
	{0, 1, 1, 2, 3, 3, 2, 1, 1},
	{0, 1, 5, 5, 5, 5, 5, 0, 1},
	{0, 2, 0, 5, 5, 5, 5, 0, 2},
	{0, 2, 0, 5, 5, 5, 5, 0, 2},
	{0, 1, 0, 5, 5, 5, 5, 0, 1},
	{0, 1, 0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 2, 2, 0, 0, 0}
};

int kingstable[9][9] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{0, 20, 30, 10, 0, 0, 10, 30, 20},
	{0, 10, 0, 0, 0, 0, 0, 0, 10},
	{0, -10, -20, -20, -20, -20, -20, -20, -10},
	{0, -20, -30, -30, -40, -40, -30, -30, -20},
	{0, -30, -40, -40, -50, -50, -40, -40, -30},
	{0, -30, -40, -40, -50, -50, -40, -40, -30},
	{0, -30, -40, -40, -50, -50, -40, -40, -30},
	{0, -30, -40, -40, -50, -50, -40, -40, -30}
};

int pointable[9][9] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{0, 3, 5, 10, 20, 20, 10, 5, 3 },
	{0, 5, 10, 20, 30, 30, 20, 10, 5 },
	{0, 5, 10, 20, 30, 30, 20, 10, 5 },
	{0, 3, 5, 10, 20, 20, 10, 5, 3 },
	{0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{0, 0, 0, 0, 0, 0, 0, 0, 0 },
};


int AI::chatluongquan(Player* player) {
	if (!player) return 0;
	int pnt = 0, add = 0, r, c, minP;
	int maxRev = 0;
	vector<Piece *> &piece = player->piece;
//	vector<int> decrease;
	for (int i = 1; i <= 16; i++) {
		if (!piece[i]->isDie) {
			r = piece[i]->r, c = piece[i]->c;
			auto& table = chessBoard->kiemsoat[r][c];
			switch (piece[i]->getClassName().front()) {
			case 'H': add = 900; break;
			case 'X': add = 500; break;
			case 'M': add = 300; break;
			case 'T': add = 300; break;
			case 'i': add = 100; break;
//			case 'V': pnt += 1000; break;
			}
			pnt += add;
			minP = 100000;
			for (Piece * it : table[player->rival->team]) {
				minP = min(minP, pieceVal[it->getClassName().front()]);
			}
			if (minP < 100000) {
				if (!table[player->team].empty()){
					pnt += min(minP - add, 0);
					maxRev = max(add - minP, maxRev);
				}
				else {
					pnt -= add;
					maxRev = max(add, maxRev);
				}
			}
//			if (minP < 100000){
//				if (!table[player->team].empty()){
//					decrease.push_back(min(add - minP, 0));
//				} else {
//					decrease.push_back(add);
//				}
//			}
		}
	}
	if (cur == player) pnt += maxRev;
//	sort(begin(decrease), end(decrease));
//	if (cur == player){
//		if (!decrease.empty())
//			decrease.pop_back();
//	} 
//	if (!decrease.empty()){
//		pnt -= decrease.back();
//	}
	return pnt;
}
int AI::vitriquan(Player* player) {
	int n = game->history.size();
	if (!player) return 0;
	int pnt = 0, r, c;
	char tmp;
	vector<Piece *> &piece = player->piece;
	for (int i = 1; i <= 16; i++) {
		if (piece[i] && !piece[i]->isDie) {
			r = piece[i]->r, c = piece[i]->c;
			if (piece[i]->team == Player::WHITE) r = 9 - r;
			tmp = piece[i]->getClassName().front();
			switch (tmp) {
			case 'H':
				if (n >= 20) continue;
				pnt += queenstable[r][c]; break;
			case 'X': pnt += rookstable[r][c]; break;
			case 'M': pnt += knightstable[r][c]; break;
			case 'T': pnt += bishopstable[r][c]; break;
			case 'i': pnt += pawntable[r][c]; break;
			case 'V':
				if (n <= 40) pnt += kingstable[r][c];
				break;
			}
			pnt += piece[i]->target.size();
			//			if (n <= 50){
			//				for (auto it : player->piece[i]->kiemsoat){
			//					pnt += pointable[it.r][it.c] - pieceVal[tmp];
			//				}
			//			}
		}
	}
	//	if (player->piece[1]->vua->beChecking()) pnt -= 30;
	return pnt;
}

int AI::nearKing(Player* player) {
	if (player == NULL) return 0;
	Vua* vua = player->piece[1]->vua;
	Vua* rvua = player->rival->piece[1]->vua;
	int n = game->history.size();
	int pnt = 0, r, c;
	for (int i = 1; i <= 16; i++) {
		if (!player->piece[i]->isDie) {
			r = player->piece[i]->r, c = player->piece[i]->c;
			if (player->piece[i]->team == Player::WHITE) r = 9 - r;
			switch (player->piece[i]->getClassName().front()) {
			case 'H':
				pnt -= (abs(r - rvua->r) + abs(c - rvua->c));
				pnt -= (abs(r - vua->r) + abs(c - vua->c));
				break;
			case 'X':
				pnt -= (abs(r - rvua->r) + abs(c - rvua->c));
				pnt -= (abs(r - vua->r) + abs(c - vua->c));
				break;
			case 'M':
				pnt -= (abs(r - rvua->r) + abs(c - rvua->c));
				pnt -= (abs(r - vua->r) + abs(c - vua->c));
				break;
			case 'T': break;
			case 'i':
				pnt -= (abs(r - rvua->r) + abs(c - rvua->c));
				pnt -= (abs(r - vua->r) + abs(c - vua->c));
				break;
			case 'V':
				if (n >= 70)
					pnt -= (abs(r - rvua->r) + abs(c - rvua->c));
				break;
			}
		}
	}
	return pnt;
}

int AI::space(Player* player) {
	if (player == NULL) return 0;
	int pnt = 0, r, c;
	for (int i = 1; i <= 16; i++) {
		if (!player->piece[i]->isDie) {
			r = player->piece[i]->r, c = player->piece[i]->c;
			if (player->piece[i]->team == Player::WHITE) r = 9 - r;
			switch (player->piece[i]->getClassName().front()) {
			case 'H': pnt += r; pnt += 5 * player->piece[i]->kiemsoat.size(); break;
			case 'X': pnt += r; pnt += 5 * player->piece[i]->kiemsoat.size(); break;
			case 'M': pnt += r; pnt += 5 * player->piece[i]->kiemsoat.size(); break;
			case 'T': pnt += r; pnt += 5 * player->piece[i]->kiemsoat.size(); break;
			case 'i': pnt += r * r * r / 3; break;
			case 'V':
				break;
			}
		}
	}
	return pnt;
}

int AI::lienketquan() {
	auto& table = game->chessBoard->kiemsoat;
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			table[i][j][Player::WHITE].clear();
			table[i][j][Player::BLACK].clear();
		}
	}
	update();
	rival->update();
//	chessBoard->updateTarget();
	chessBoard->updateKiemsoat();
	
//	return 0;

	int pnt1 = 0, pnt2 = 0, r, c, thispoint;
	for (int i = 1; i <= 16; i++) {
		if (piece[i] && !piece[i]->isDie) {
			r = piece[i]->r, c = piece[i]->c;
			thispoint = pieceVal[piece[i]->getClassName().front()];
			auto us = table[r][c][team], them = table[r][c][rival->team];
			for (auto it : us) {
				pnt1 += 10 - pieceVal[it->getClassName().front()] / 100;
			}
			for (auto it : them) {
				pnt1 -= 10 - pieceVal[it->getClassName().front()] / 100;
			}
		}
		if (rival->piece[i] && !rival->piece[i]->isDie) {
			r = rival->piece[i]->r, c = rival->piece[i]->c;
			thispoint = pieceVal[rival->piece[i]->getClassName().front()];
			auto us = table[r][c][team], them = table[r][c][rival->team];
			for (auto it : them) {
				pnt2 += 10 - pieceVal[it->getClassName().front()] / 100;
			}
			for (auto it : us) {
				pnt2 -= 10 - pieceVal[it->getClassName().front()] / 100;
			}
		}
	}

	return (pnt1 - pnt2);
}

int AI::heuristic(Player* cur) {
	hr++;
	this->cur = cur;
	int pnt = 0;
	pnt += lienketquan();
	pnt += (chatluongquan(this) - chatluongquan(rival));
	pnt += (vitriquan(this) - vitriquan(rival));
	pnt += (space(this) - space(rival));
	pnt += (nearKing(this) - nearKing(rival));

	return pnt;
}

