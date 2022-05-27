#include "../hdr/Human.h"
#include "../hdr/Move.h"
#include "../hdr/Game.h"
#include "../hdr/History.h"
#include "../hdr/Player.h"
#include "../hdr/Scene.h"
#include "../hdr/ChessBoard.h"
#include "../hdr/EventSolver.h"
#include "../hdr/Piece.h"

Human::Human() : Player() {
	eventSolver = nullptr;
}

Human::Human(int team, Game* game) : Human(){
	this->team = team;
	this->game = game;
}

void Human::init(ChessBoard* cb, Player* rv){
	Player::init(cb, rv);
	eventSolver = cb->game->eventSolver;
}

void Human::move() {
	SDL_Event event;
	int x, y;
	Piece* tmp = nullptr;
	while (1) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			game->exit();
			return;
		case SDL_MOUSEBUTTONDOWN:
			game->render();
			x = event.button.x;
			y = event.button.y;
			if (0 <= x && x <= 399) {
				if (0 <= y && y <= 399) {
					x /= 50, y /= 50;
//					cout << "r = " << y + 1 << ", " << "c = " << x + 1 << endl;
//					cout << "White: ";
//					for (auto it : chessBoard->kiemsoat[y + 1][x + 1][Player::WHITE]) cout << it->getClassName() << ", ";
//					cout << endl;
//					cout << "Black: ";
//					for (auto it : chessBoard->kiemsoat[y + 1][x + 1][Player::BLACK]) cout << it->getClassName() << ", ";
//					cout << endl;
					tmp = chessBoard->piece[(long long) y + 1][(long long) x + 1];
					if (selected == nullptr) {
						if (tmp == nullptr || tmp->team == team)
							selected = tmp;
					}
					else if (selected != tmp) {
						if (selected->isTarget(y + 1, x + 1)) {
							Move mv = chessBoard->move(selected->r, selected->c, y + 1, x + 1);
							cout << mv.to_string() << endl;
							game->history.push(mv);
							game->render();
							selected = nullptr;
							return;
						}
						selected = nullptr;
						if (tmp && tmp->team == team){
							selected = tmp;
						}
						
					}
				}
			}
			else if (400 <= x && x <= 449) {
				if (0 <= y && y <= 49) {
					cout << "new Game" << endl;
					game->newGame();
					return;
				}
				else if (50 <= y && y <= 99) {
					cout << "Back" << endl;
					game->back();
					game->render();
					return;
				}
				else if (100 <= y && y <= 149) {
					cout << "History" << endl;
					game->printHistory();
				}
				else if (150 <= y && y <= 199) {
					cout << "Theme" << endl;
					Game::changeTheme();
					for (Piece * it : Piece::lsPiece){
						it->init();
					}
					game->render();
				}
				else if (200 <= y && y <= 249) {
					cout << "Quit" << endl;
					game->exit();
					return;
				}
			}
		default:
			break;
		}
	}
	
}


string Human::getClassName() {
	return "Human";
}
