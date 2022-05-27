#include "../hdr/EventSolver.h"
#include "../hdr/Node.h"
#include "../hdr/ChessBoard.h"
#include "../hdr/AI.h"
#include "../hdr/Game.h"

EventSolver::EventSolver(){
	game = nullptr; chessBoard = nullptr;
	selected = nullptr;
}

EventSolver::EventSolver(Game* game){
	this->game = game;
	setChessBoard(game->chessBoard);
	selected = nullptr;
}

void EventSolver::init() {
	if (game) {
		setChessBoard(game->chessBoard);
	}
}

spMove EventSolver::getMove(){
	return spMove();
}

void EventSolver::setChessBoard(ChessBoard* cb) {
	if (!cb) return;
	selected = nullptr;
	this->chessBoard = cb;
}

Point EventSolver::click(int a, int b) {
	return Point(a, b);
}

