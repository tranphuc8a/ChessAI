#include "../hdr/Game.h"
#include "../hdr/Trongtai.h"
#include "../hdr/ChessBoard.h"
#include "../hdr/History.h"
#include "../hdr/Player.h"
#include "../hdr/Piece.h"
#include "../hdr/Move.h"
#include "../hdr/Human.h"
#include "../hdr/AI.h"
#include "../hdr/AIMinimax.h"
#include "../hdr/AINegamax.h"
#include "../hdr/View.h"
#include "../hdr/Scene.h"
#include "../hdr/EventSolver.h"
#include "../hdr/PhongCapWindow.h"
#include "../hdr/ChoosePlayerWindow.h"
#include <fstream>
#include <thread>
using namespace std;

int Game::theme = 1;

Game::Game() : Window("ChessAI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 450, 400) { 
	choose = 2;
}

void Game::init() {
	initInterface();
	trongtai = new Trongtai(this);
	if (choose == 1){
		white = new Human(Player::WHITE, this);
		black = new Human(Player::BLACK, this);
	} else if (choose == 2){
		white = new Human(Player::WHITE, this);
		black = new AIMinimax(Player::BLACK, this, 3);
	} else if (choose == 3){
		white = new AIMinimax(Player::WHITE, this, 3);
		black = new Human(Player::BLACK, this);
	} else {
		white = new AIMinimax(Player::WHITE, this, 3);
		black = new AINegamax(Player::BLACK, this, 3);
	}
	chessBoard = new ChessBoard(this);
	history = History();
	eventSolver = new EventSolver(this);

	trongtai->init();
	white->init(chessBoard, black);
	black->init(chessBoard, white);
	chessBoard->init();
	history.init();
	eventSolver->init();
	

	turn = Player::WHITE;
	check = Trongtai::NORM;
	isEnd = false;
	currentPlayer = white;

	scene->add(chessBoard);
	render();
}

void Game::initInterface() {
	View* vUndo = new View("images/undo.png");
	View* vNewgame = new View("images/newgame.png");
	View* vQuit = new View("images/quit.png");
	View* vHtr = new View("images/history.png");
	View* vThm = new View("images/theme.png");
	
	undo = new Node(scene, vUndo);
	newgame = new Node(scene, vNewgame);
	quit = new Node(scene, vQuit);
	htr = new Node(scene, vHtr);
	thm = new Node(scene, vThm);
	
	newgame->set(400, 0, 50, 50);
	undo->set(400, 50, 50, 50);
	htr->set(400, 100, 50, 50);
	thm->set(400, 150, 50, 50);
	quit->set(400, 200, 50, 50);
	
	scene->add(newgame);
	scene->add(undo);
	scene->add(htr);
	scene->add(quit);
	scene->add(thm);
}

void Game::gameloop() {
	int sum = Player::WHITE + Player::BLACK;
	while (!isEnd) {
//		thread t(Game::waitAI, this);
		if (history.empty()) currentPlayer = white;
		else currentPlayer = history.top().piece->player->rival;
		
		currentPlayer->move();
		
		if (isEnd) break;
		render();
		
		check = trongtai->checkMate(currentPlayer->rival);
		if (check == Trongtai::MATE) {
			win(currentPlayer);
		}
		else if (check == Trongtai::DRAW) {
			draw();
		}
//		t.join();
	}
}

void Game::start() {
	
	gameloop();

	free();

}

void Game::waitback() {
	SDL_Event event;
	int x, y;
	while (1) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			exit();
			return;
		case SDL_MOUSEBUTTONDOWN:
			x = event.button.x;
			y = event.button.y;
			if (400 <= x && x <= 449) {
				if (0 <= y && y <= 49) {
					cout << "new Game" << endl;
					newGame();
					return;
				}
				else if (50 <= y && y <= 99) {
					cout << "Back" << endl;
					back();
					render();
					return;
				}
				else if (100 <= y && y <= 149) {
					cout << "History" << endl;
					printHistory();
				}
				else if (150 <= y && y <= 199) {
					cout << "Theme" << endl;
					Game::changeTheme();
					for (Piece * it : Piece::lsPiece){
						it->init();
					}
					render();
				}
				else if (200 <= y && y <= 249) {
					cout << "Quit" << endl;
					exit();
					return;
				}
			}
		}
	}
}

void Game::waitAI(){
	SDL_Event e;
	while (currentPlayer->getClassName() == "AI"){
		SDL_WaitEvent(&e);
		cout << "Created thread" << endl;
		switch (e.type){
			case SDL_MOUSEBUTTONDOWN:
				cout << "Event" << endl;
				break;
		}
	}
}

void Game::printHistory(){
	fstream file;
	file.open("data/bienban.txt", ios::out);
	for (Move it : history.move){
		file << it.to_string() << endl;
	}
	file.close();
	system("start data/bienban.txt");
}

void Game::win(Player* player) {
	// show win
	if (player->team == Player::WHITE){
		cout << "White win" << endl;
	} else {
		cout << "Black win" << endl;
	}
	waitback();
}
void Game::draw() {
	//show draw
	cout << "Draw" << endl;
	waitback();
}

void Game::exit() {
	isEnd = 1;
}

void Game::free() {
	history.free();
	chessBoard->free();
	std::free(chessBoard);
	white->free();
	black->free();
	std::free(white);
	std::free(black);
	trongtai->free();
	std::free(trongtai);
}

void Game::newGame() {
	exit();
	scene->clearChild();
	ChoosePlayerWindow q = ChoosePlayerWindow();
	choose = q.get();
	SDL_DestroyRenderer(q.scene->renderer);
	std::free(q.scene);
	SDL_DestroyWindow(q.window);
	init();
	start();
}

void Game::back() {
	if (history.empty()) return;
	if (check == Trongtai::MATE) {		
		check = Trongtai::NORM;
	}
	Piece*** table = chessBoard->piece;
	for (int i = 1; i <= 2; i++) {
		Move top = history.top();

		Piece* piece = top.piece;
		Piece* kill = top.kill;
		Piece* bear = top.bear;

		chessBoard->back();

		history.pop();
		if (history.empty()) break;
		if (history.top().piece->player->rival->getClassName() != "AI") break;
	}
}

void Game::render() {
//	cout << "renderring... ";
	SDL_RenderClear(scene->renderer);
	for (auto& it : scene->child)
		it->render();
	SDL_RenderPresent(scene->renderer);
//	cout << "done" << endl;
}
void Game::update() {

}
void Game::handleEvent() {

}
