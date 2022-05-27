#include "../hdr/AINegamax.h"
#include "../hdr/Trongtai.h"
#include "../hdr/Game.h"
#include "../hdr/ChessBoard.h"
#include "../hdr/History.h"
#include "time.h"
#include "../hdr/Piece.h"

AINegamax::AINegamax() : AI(){
	
}
AINegamax::AINegamax(int team, Game* game) : AI(team, game){
	
}
AINegamax::AINegamax(int team, Game* game, int maxdepth) : AI(team, game, maxdepth){
	
}

AI::SimpleMove AINegamax::thinking(){
	cout << "AI thinking..." << endl;
	cout << "Try: " << Piece::t << endl;
	t = 0;
	hr = 0;
	return negamaxDecision();
}

AI::SimpleMove AINegamax::negamaxDecision() {
	int maxdepth = 3, alpha = INT_MIN, beta = INT_MAX, color = 1;
	SimpleMove rs = negamax(maxdepth, alpha, beta, color, this);
	cout << "p = " << rs.point << ", t = " << t;
	return rs;
}

AI::SimpleMove AINegamax::negamax(int maxdepth, int alpha, int beta, int color, Player* ply) {
	t++;
	SimpleMove result, tmp;
	if (game->trongtai->checkMate(this) == Trongtai::MATE) {
		result.point = -30000 * color;// - maxdepth;
		return result;
	}
	else if (game->trongtai->checkMate(rival) == Trongtai::MATE) {
		result.point = 30000 * color;// - maxdepth;
		return result;
	}
	else if (game->trongtai->checkMate(this) == Trongtai::DRAW ||
		game->trongtai->checkMate(rival) == Trongtai::DRAW) {
		result.point = 0;
		return result;
	}
	else if (maxdepth <= 0) {
		result.point = color * heuristic(ply);// + maxdepth;
		return result;
	}
	vector<SimpleMove> listMove = getMove(ply);
	int n = listMove.size();
	int val = INT_MIN;

	result.point = val;
	for (auto& it : listMove) {
		Move mv = chessBoard->move(it.sr, it.sc, it.tr, it.tc, it.pc);
		if (!mv.piece) {
			cout << "mv = NULL" << endl;
			continue;
		}
		game->currentPlayer = game->currentPlayer->rival;
		game->history.push(mv);

		tmp = negamax(maxdepth - 1, -beta, -alpha, -color, ply->rival);
		tmp.point *= -1;
		if (result.point <= tmp.point) {
			result = it;
			result.point = tmp.point;
		}

		game->currentPlayer = game->currentPlayer->rival;
		chessBoard->back();
		game->history.pop();

		alpha = max(result.point, alpha);
		if (alpha >= beta) break;
	}
	return result;
}

AI::SimpleMove AINegamax::negamaxTime(int maxdepth, int maxTime, int alpha, int beta, int color, Player* ply) {
	t++;
	SimpleMove result, tmp;
	if (game->trongtai->checkMate(this) == Trongtai::MATE) {
		result.point = -30000 + game->history.size();
		result.point *= color;
		return result;
	}
	else if (game->trongtai->checkMate(this) == Trongtai::DRAW) {
		result.point = 0;
		return result;
	}
	else if (maxdepth <= 0) {
		result.point = heuristic(ply) - game->history.size();
		result.point *= color;
		return result;
	}
	else if (time(0) > maxTime) {
		if (maxdepth <= 0) {
			result.point = heuristic(ply) - game->history.size();
			result.point *= color;
			return result;
		}
		else {
			result.point = alpha;
			result.point *= color;
			return result;
		}
	}
	vector<SimpleMove> listMove = getMove(ply);
	int n = listMove.size();
	int val = INT_MIN;

	result.point = val;
	for (auto &it : listMove) {
		Move mv = chessBoard->move(it.sr, it.sc, it.tr, it.tc, it.pc);
		if (!mv.piece) continue;
		game->currentPlayer = game->currentPlayer->rival;
		game->history.push(mv);

		tmp = negamaxTime(maxdepth - 1, maxTime, -beta, -alpha, -color, ply->rival);
		tmp.point *= -1;
		if (result.point <= tmp.point) {
			result = it;
			result.point = tmp.point;
		}

		game->currentPlayer = game->currentPlayer->rival;
		chessBoard->back();
		game->history.pop();

		alpha = max(result.point, alpha);
		if (alpha >= beta) break;
	}
	return result;
}




