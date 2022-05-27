#include "../hdr/ChessBoard.h"
#include "../hdr/Player.h"
#include "../hdr/Game.h"
#include "../hdr/Piece.h"
#include "../hdr/Move.h"
#include "../hdr/History.h"
#include "../hdr/Vua.h"
#include "../hdr/Hau.h"
#include "../hdr/Xe.h"
#include "../hdr/Tuong.h"
#include "../hdr/Ma.h"
#include "../hdr/View.h"
#include "../hdr/PhongCapWindow.h"
#include "../hdr/Scene.h"

template <class T = Piece*>
void remove(vector<T>& a, T val) {
	int n = count(begin(a), end(a), val);
	remove(begin(a), end(a), val);
	a.resize(a.size() - n);
}

ChessBoard::ChessBoard() {
	piece = new Piece**[9];
	for (int i = 1; i <= 8; i++){
		piece[i] = new Piece*[9];
		fill(piece[i], piece[i] + 9, nullptr);
	}
//	piece = vector<vector<Piece*>>(9, vector<Piece*>(9, nullptr));
}
ChessBoard::ChessBoard(Game* game) : ChessBoard() {
	this->game = game;
	
}

void ChessBoard::init() {
	setView(new View("images/chessBoard5.png"));
	set(0, 0, 400, 400);
	Player* pl1 = game->white, * pl2 = game->black;
	setScene(game->scene);

	if (pl1 != nullptr)
		for (int i = 1; i <= 16; i++) {
			auto p = pl1->piece[i];
			if (p != nullptr) {
				piece[p->r][p->c] = p;
				p->chessBoard = this;
				p->setScene(scene);
			}
		}
	if (pl2 != nullptr)
		for (int i = 1; i <= 16; i++) {
			auto p = pl2->piece[i];
			if (p != nullptr) {
				piece[p->r][p->c] = p;
				p->chessBoard = this;
				p->setScene(scene);
			}
		}
}

void ChessBoard::free() {}

Move ChessBoard::move(int sr, int sc, int tr, int tc) {
	Piece* select = piece[sr][sc];
//	if (select == nullptr || select->isDie || !(game->currentPlayer->contains(select)))
//		return Move();

	// check select can go:
//	if (!select->isTarget(tr, tc))
//		return Move();

	// OK:
	// phong cap:
	if (select->getClassName() == "i" && (tr == 1 || tr == 8))
		return phongcap(select, tr, tc);
	// Normal
	Move mv = select->move(tr, tc);
	return mv;
}

Move ChessBoard::move(int sr, int sc, int tr, int tc, char pc) {
	if (!(pc == 'H' or pc == 'X' or pc == 'M' or pc == 'T'))
		return move(sr, sc, tr, tc);
	return phongcap(piece[sr][sc], tr, tc, pc);
}

Move ChessBoard::move(string src, string tg) {
	// translate src & tg;
	int sr = 9 - (src[1] - '0'), sc = src[0] - 'a' + 1;
	int tr = 9 - (tg[1] - '0'), tc = tg[0] - 'a' + 1;
	// check select:
	Piece* select = piece[sr][sc];

//	if (!select || select->isDie || !(game->currentPlayer->contains(select)))
//		return Move();
//	if (select->getClassName() == "i" && tg.size() == 2 && (tr == 1 || tr == 8)) 
//		return Move();

	// check select can go:
//	if (!select->isTarget(tr, tc))
//		return Move();
	// OK:
	// phong cap:
	if (tg.size() == 3)
		return phongcap(select, tr, tc, tg[2]);
	// Normal
	Move mv = select->move(tr, tc);
	return mv;
}

Move ChessBoard::phongcap(Piece* select, int tr, int tc) {
	// char newPiece = select->player->game->pointer->getPhongcap();
	// getPhongcap cho char newPiece
	PhongCapWindow p(select->player);
	char newPiece = p.getPiece();
	SDL_DestroyRenderer(p.scene->renderer);
	std::free(p.scene);
	SDL_DestroyWindow(p.window);
	return phongcap(select, tr, tc, newPiece);
}

Move ChessBoard::phongcap(Piece* select, int tr, int tc, char newPiece) {
	Move mv(0, select, select->r, select->c, tr, tc, Move::UPP);
	Piece* kill = nullptr;
	if (select->isKiemsoat(tr, tc) && piece[tr][tc]) {
		piece[tr][tc]->isDie = 1;
		kill = piece[tr][tc];
	}
	Piece* newP = nullptr;
	switch (newPiece) {
	case 'H': case 'h':
		newP = new Hau(select->player, tr, tc);
		break;
	case 'X': case 'x':
		newP = new Xe(select->player, tr, tc);
		break;
	case 'M': case 'm':
		newP = new Ma(select->player, tr, tc);
		break;
	case 'T': case 't':
		newP = new Tuong(select->player, tr, tc);
		break;
	default:
		return Move();
	}
	newP->init();
	select->cntMove++;
	newP->id = select->id;
	newP->vua = select->vua;
	newP->chessBoard = this;
	select->player->piece[select->id] = newP;
	select->isDie = 1;
	piece[tr][tc] = newP;
	piece[select->r][select->c] = nullptr;
	select->setPoint(tr, tc);
	mv.setKillBear(kill, newP);
	return mv;
}

void ChessBoard::back() {
	Move top = game->history.top();
	top.piece->cntMove--;
	top.piece->setPoint(top.sr, top.sc);
	piece[top.sr][top.sc] = top.piece;
	piece[top.tr][top.tc] = nullptr;

	if (top.kill) {
		top.kill->isDie = 0;
		piece[top.kill->r][top.kill->c] = top.kill;
	}

	Piece* xe = nullptr;
	switch (top.type) {
	case Move::INN:
		if (top.tc > top.sc) { // Nhap thanh phai:
			xe = piece[top.sr][top.sc + 1];
			xe->setPoint(top.sr, 8);
			piece[top.sr][8] = xe;
			piece[top.sr][top.sc + 1] = nullptr;
		}
		else { // nhap thanh trai
			xe = piece[top.sr][top.sc - 1];
			xe->setPoint(top.sr, 1);
			piece[top.sr][1] = xe;
			piece[top.sr][top.sc - 1] = nullptr;
		}
		if (xe) xe->cntMove = 0;
		break;
	case Move::UPP:
		Piece* act = top.piece;
		act->player->piece[act->id] = act;
		act->isDie = 0;
//		::free(top.bear);
		break;
	}
}

void ChessBoard::update() {
	// update;
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (piece[i][j])
				piece[i][j]->update();
		}
	}
}
void ChessBoard::render() {
	// render;
	Node::render();
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (piece[i][j] != nullptr) {
				piece[i][j]->render();
			}
		}
	}
}

void ChessBoard::updateTarget(){
	for (int i = 1; i <= 8; i++){
		for (int j = 1; j <= 8; j++){
			Piece * p = piece[i][j];
			if (p){
				for (auto& it : p->target){
					target[p->r][p->c][p->team].push_back(p);
				}
			}
		}
	}
}
void ChessBoard::updateKiemsoat(){
	for (int i = 1; i <= 8; i++){
		for (int j = 1; j <= 8; j++){
			Piece * p = piece[i][j];
			if (p){
				for (auto& it : p->kiemsoat){
					kiemsoat[it.r][it.c][p->team].push_back(p);
				}
			}
		}
	}
}


