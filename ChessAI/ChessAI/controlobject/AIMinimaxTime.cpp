#include "../hdr/AIMinimax.h"
#include "../hdr/Game.h"
#include "../hdr/Trongtai.h"
#include "../hdr/History.h"
#include "../hdr/ChessBoard.h"
#include "time.h"

AI::SimpleMove AIMinimax::minimaxTime() {
	srand(time(0));
	int averageTime = 3; // seconds
	int limit = rand() % 3 + averageTime;

	int maxTime = time(0) + limit;
	SimpleMove rs = maxValue(3, INT_MIN, INT_MAX), tmp;
	cout << "depth:3, point:" << rs.point << ", t:" << t << ", hr:" << hr << endl;
	for (int d = 4; time(0) <= maxTime; d++) {
		tmp = maxValueTime(d, maxTime, INT_MIN, INT_MAX);
		if (tmp.sr > 0 && tmp.point < 1000000) {
			rs = tmp;
		}
		else continue;
		cout << "depth:" << d << ", point:" << rs.point << ", t:" << t << ", hr:" << hr << endl;
	}
	return rs;
}
AI::SimpleMove AIMinimax::maxValueTime(int maxdepth, int maxTime, int alpha, int beta) {
	t++;
	SimpleMove result, tmp;
	if (game->trongtai->checkMate(this) == Trongtai::MATE) {
		result.point = -30000 + game->history.size();
		return result;
	}
	else if (game->trongtai->checkMate(this) == Trongtai::DRAW) {
		result.point = 0;
		return result;
	}
	else if (maxdepth <= 0) {
		result.point = heuristic(this) - game->history.size();
		return result;
	}
	else if (time(0) > maxTime) {
		if (maxdepth <= 0) {
			result.point = heuristic(this) - game->history.size();
			return result;
		}
		else {
			result.point = alpha;
			return result;
		}
	}
	vector<SimpleMove> listMove = getMove(this);
	int n = listMove.size();
	int val = INT_MIN;

	result.point = val;
	for (auto &it : listMove) {
		Move mv = chessBoard->move(it.sr, it.sc, it.tr, it.tc, it.pc);
		if (!mv.piece) continue;
		game->currentPlayer = game->currentPlayer->rival;
		game->history.push(mv);

		tmp = minValueTime((maxdepth - 1), maxTime, alpha, beta);
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
	return result;
}
AI::SimpleMove AIMinimax::minValueTime(int maxdepth, int maxTime, int alpha, int beta) {
	t++;
	SimpleMove result, tmp;
	if (game->trongtai->checkMate(rival) == Trongtai::MATE) {
		result.point = 30000 - game->history.size();
		return result;
	}
	else if (game->trongtai->checkMate(rival) == Trongtai::DRAW) {
		result.point = 0;
		return result;
	}
	else if (maxdepth <= 0) {
		result.point = heuristic(rival) + game->history.size();
		return result;
	}
	else if (time(0) > maxTime) {
		if (maxdepth <= 0) {
			result.point = heuristic(rival) + game->history.size();
			return result;
		}
		else {
			result.point = beta;
			return result;
		}
	}
	vector<SimpleMove> listMove = getMove(rival);
	int n = listMove.size();
	int val = INT_MAX;
	result.point = val;
	for (auto &it : listMove) {
		Move mv = chessBoard->move(it.sr, it.sc, it.tr, it.tc, it.pc);
		if (!mv.piece) continue;
		game->history.push(mv);
		game->currentPlayer = game->currentPlayer->rival;

		tmp = maxValueTime((maxdepth - 1), maxTime, alpha, beta);
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
	return result;
}


