#pragma once
#include "AI.h"

class AIMinimax : public AI {
public:
	// constructor:
	AIMinimax();
	AIMinimax(int team, Game* game);
	AIMinimax(int team, Game* game, int maxdepth);
public:
	virtual SimpleMove thinking() override;
	// minimax algorithm:
	// AIMinimax.cpp:
	SimpleMove minimaxDecision();
	SimpleMove maxValue(int maxdepth, int alpha, int beta);
	SimpleMove minValue(int maxdepth, int alpha, int beta);
	// AIMinimaxTime.cpp
	SimpleMove minimaxTime();
	SimpleMove maxValueTime(int maxdepth, int maxTime, int alpha, int beta);
	SimpleMove minValueTime(int maxdepth, int maxTime, int alpha, int beta);
};


