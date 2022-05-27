#include "../hdr/Move.h"
#include "../hdr/Piece.h"

//const int Move::NORM = 1;
//const int Move::KILL = 2;
//const int Move::INN  = 3;
//const int Move::UPP  = 4;
//const int Move::SKILL= 5;


Move::Move() {}

Move::Move(int id, Piece* piece, int sr, int sc, int tr, int tc, int type) {
	this->id = id;
	this->piece = piece;
	this->sr = sr;
	this->sc = sc;
	this->tr = tr;
	this->tc = tc;
	this->type = type;
	kill = bear = NULL;
	src = tg = "";
	src += char(sc - 1 + 'a');
	src += char(9 - sr + '0');
	tg += char(tc - 1 + 'a');
	tg += char(9 - tr + '0');
}

void Move::setKillBear(Piece* kill, Piece* bear = NULL) {
	this->kill = kill;
	this->bear = bear;
	if (type == Move::UPP && bear != NULL) {
		tg += bear->getClassName();
	}
}

string Move::to_string(){
	string tmp = "";
	src = tg = "";
	src += char(sc - 1 + 'a');
	src += char(9 - sr + '0');
	tg += char(tc - 1 + 'a');
	tg += char(9 - tr + '0');
	if (piece) {
		tmp += piece->getClassName().front();
		tmp += ": " + src + " - " + tg;
		if (bear) {
			tmp += bear->getClassName().front();
		}
	}
	return tmp;
}




