#pragma once
#include "AI.h"

class AINegamax : public AI {
public:
	AINegamax();
	AINegamax(int team, Game* game);
	AINegamax(int team, Game* game, int maxdepth);
public:
	virtual SimpleMove thinking() override;
	// AINegamax.cpp
	SimpleMove negamaxDecision();
	SimpleMove negamax(int maxdepth, int alpha, int beta, int color, Player* ply);
	SimpleMove negamaxTime(int maxdepth, int maxTime, int alpha, int beta, int color, Player* ply);
};


