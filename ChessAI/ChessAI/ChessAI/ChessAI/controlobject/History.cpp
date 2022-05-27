#include "../hdr/History.h"
#include <stack>
#include <string>
#include <fstream>
#include "../hdr/Piece.h"

History::History() {
	move.clear();
}

void History::init() {

}

void History::free() {
	stack<string> lsmove;
	string tmp;
	while (size() > 0) {
		Move t = pop();
		tmp = t.src + "-" + t.tg;
		if (t.bear != NULL) tmp += t.bear->getClassName();
		lsmove.push(tmp);
	}
	fstream file;
	file.open("data/bienban.txt", ios::out);
	while (!lsmove.empty()) {
		file << lsmove.top() << endl;
		lsmove.pop();
	}
	file.close();
}

void History::push(Move mv) {
	if (!mv.piece) return;
	mv.id = size() + 1;
	move.push_back(mv);
}
Move History::pop() {
	if (empty()) return Move();
	Move t = move.back();
	move.pop_back();
	return t;
}
Move History::top() {
	if (empty()) return Move();
	return move.back();
}
int History::size() {
	return (int) move.size();
}
bool History::empty() {
	return move.empty();
}



