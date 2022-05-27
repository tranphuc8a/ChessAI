#include "../hdr/Trongtai.h"
#include "../hdr/Player.h"
#include "../hdr/Piece.h"
#include "../hdr/Vua.h"

int Trongtai::NORM = 0;
int Trongtai::MATE = 1;
int Trongtai::DRAW = 2;

Trongtai::Trongtai() {}
Trongtai::Trongtai(Game* game) {
	this->game = game;
}

void Trongtai::init() {

}

void Trongtai::free() {

}

bool Trongtai::checkNuocdi(string& src, string& tg) {
	// check src:
	if (src.size() != 2) return false;
	if (!((src[0] >= 'a' && src[0] <= 'h') || (src[0] >= 'A' && src[0] <= 'H')))
		return false;
	if (src[0] >= 'A' && src[0] <= 'H') src[0] += ('a' - 'A');

	// check tg:
	if (tg.size() != 2 && tg.size() != 3) return false;
	if (!((tg[0] >= 'a' && tg[0] <= 'h') || (tg[0] >= 'A' && tg[0] <= 'H')))
		return false;
	if (tg[0] >= 'A' && tg[0] <= 'H') tg[0] += ('a' - 'A');

	if (tg.size() == 3) {
		bool ok = false;
		for (char mauquan : quan) {
			if (tg[2] == mauquan)
				return true;
		}
	}
	return true;
}

int Trongtai::checkMate(Player* player) {
	int cntMove = 0;
	auto& vec = player->piece;
	if (vec[1]->vua->isDie) return Trongtai::MATE;
	for (int i = 1; i <= 16; i++) {
		if (vec[i] != NULL && !vec[i]->isDie) {
			cntMove += vec[i]->updateTarget().size();
		}
	}
	if (cntMove == 0) {
		if (vec[1]->vua->beChecking())
			return Trongtai::MATE;
		return Trongtai::DRAW;
	}
	return Trongtai::NORM;
}


