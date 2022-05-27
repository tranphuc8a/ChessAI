#pragma once
#include <vector>
#include "Move.h"
using namespace std;

class History {
public:
	vector<Move> move;
public:
	History();
	void init();
public:
	void push(Move);
	Move pop();
	Move top();
	int size();
	bool empty();
	void free();
};
