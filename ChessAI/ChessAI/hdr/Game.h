#pragma once
#include "SDL.h"
#include "Window.h"
#include "History.h"

class Player;
class Trongtai;
class ChessBoard;
class Node;
class EventSolver;

class Game : public Window {
public:
	Player* white = nullptr, * black = nullptr;
	Trongtai* trongtai = nullptr;
	ChessBoard* chessBoard = nullptr;
	History history = History();
public:
	int choose = 2;
	int check = 0;
	int turn = 0;
	bool isEnd = 0;
	static int theme;
	Player * currentPlayer = nullptr;
public:
	EventSolver* eventSolver = nullptr;
	Node* undo		= nullptr;
	Node* newgame	= nullptr;
	Node* quit		= nullptr;
	Node* htr		= nullptr;
	Node* thm		= nullptr;
public:
	Game();
public:
	void init();
	void free();
	void initInterface();
	void start();
	void gameloop();
	void exit();
	void back();
	void newGame();
	void win(Player* player);
	void draw();
	void waitback();
	void waitAI();
	void printHistory();
	
	static void changeTheme(){
		theme++;
		if (theme > 7) theme = 1;
	}
	void render() override;
	void update() override;
	void handleEvent() override;
};



