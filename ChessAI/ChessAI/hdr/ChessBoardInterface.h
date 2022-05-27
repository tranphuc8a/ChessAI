#pragma once

#include "Window.h"
#include "Scene.h"
#include "View.h"

class EventSolver;

class ChessBoardInterface : public Window{
public:
	ChessBoardInterface();
	void createBoard();
	void run();
	void handleEvent() override;
	void update() override;
	void render() override;
	
public:
	EventSolver* es = nullptr;
	Scene* scene = nullptr;
	int FPS = 60;
};


