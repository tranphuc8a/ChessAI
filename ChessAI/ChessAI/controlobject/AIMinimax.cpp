#include "../hdr/AIMinimax.h"
#include "../hdr/Game.h"
#include "../hdr/Trongtai.h"
#include "../hdr/Move.h"
#include "../hdr/ChessBoard.h"
#include "../hdr/History.h"
#include "../hdr/Piece.h"

AIMinimax::AIMinimax() : AI(){
	
}
AIMinimax::AIMinimax(int team, Game* game) : AI(team, game){
	
}
AIMinimax::AIMinimax(int team, Game* game, int maxdepth) : AI(team, game, maxdepth){
	
}

AI::SimpleMove AIMinimax::thinking(){
	cout << "AI thinking..." << endl;
//	cout << "Try: " << Piece::t << endl;
	t = 0;
	hr = 0;
//	return minimaxDecision();
	return minimaxTime();
}

AI::SimpleMove AIMinimax::minimaxDecision() {
	int maxdepth = 3;
	int alpha = INT_MIN, beta = INT_MAX;
	SimpleMove rs = maxValue(maxdepth, alpha, beta);
	cout << "depth:3, point:" << rs.point << ", t:" << t << ", hr:" << hr << endl;
//	tree[maxdepth] = rs;
//	for (int i = maxdepth; i >= 0; i--){
//		cout << tree[i].sr << tree[i].sc << "-" << tree[i].tr << tree[i].tc << "-" << tree[i].point << endl;
//	}
	return rs;
}

AI::SimpleMove AIMinimax::maxValue(int maxdepth, int alpha, int beta) {
	t++;
	SimpleMove result, tmp;
	if (game->trongtai->checkMate(this) == Trongtai::MATE) {
		result.point = -30000;// - maxdepth;
		return result;
	}
	else if (game->trongtai->checkMate(this) == Trongtai::DRAW) {
		result.point = 0;
		return result;
	}
	else if (maxdepth <= 0) {
		result.point = heuristic(this);// + maxdepth;
		return result;
	}
	vector<SimpleMove> listMove = getMove(this);
	size_t n = listMove.size();
	int val = INT_MIN;

	result.point = val;
	for (auto& it : listMove) {
		Move mv = chessBoard->move(it.sr, it.sc, it.tr, it.tc, it.pc);
		if (!mv.piece) continue;
		game->currentPlayer = game->currentPlayer->rival;
		game->history.push(mv);

		tmp = minValue((maxdepth - 1), alpha, beta);
		if (result.point <= tmp.point) {
			result = it;
			result.point = tmp.point;
		}

		game->currentPlayer = game->currentPlayer->rival;
		chessBoard->back();
		game->history.pop();

		if (result.point > beta) break;
		alpha = max(result.point, alpha);
	}
//	tree[maxdepth] = result;
	return result;
}

AI::SimpleMove AIMinimax::minValue(int maxdepth, int alpha, int beta) {
	t++;
	SimpleMove result, tmp;
	if (game->trongtai->checkMate(rival) == Trongtai::MATE) {
		result.point = 30000;// + maxdepth;
		return result;
	}
	else if (game->trongtai->checkMate(rival) == Trongtai::DRAW) {
		result.point = 0;
		return result;
	}
	else if (maxdepth <= 0) {
		result.point = heuristic(rival);// - maxdepth;
		return result;
	}
	vector<SimpleMove> listMove = getMove(rival);
	size_t n = listMove.size();
	int val = INT_MAX;
	result.point = val;
	for (auto &it : listMove) {
		Move mv = chessBoard->move(it.sr, it.sc, it.tr, it.tc, it.pc);
		if (!mv.piece) continue;
		game->history.push(mv);
		game->currentPlayer = game->currentPlayer->rival;

		tmp = maxValue((maxdepth - 1), alpha, beta);
		if (result.point >= tmp.point) {
			result = it;
			result.point = tmp.point;
		}

		game->currentPlayer = game->currentPlayer->rival;
		chessBoard->back();
		game->history.pop();

		if (result.point < alpha) break;
		beta = min(result.point, beta);
	}
//	tree[maxdepth] = result;
	return result;
}


