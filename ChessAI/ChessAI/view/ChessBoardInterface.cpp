#include "../hdr/ChessBoardInterface.h"
#include "../hdr/Node.h"
#include "../hdr/EventSolver.h"

ChessBoardInterface::ChessBoardInterface() : Window() {
	setTitle("CHESSAI");
	scene = new Scene(this);
	FPS = 60;

	createBoard();

	View* vUndo = new View("images/undo.png");
	View* vQuit = new View("images/quit.png");
	Node* undo = new Node(scene, vUndo);
	undo->set(410, 0, 75, 50);
	Node* quit = new Node(scene, vQuit);
	quit->set(500, 0, 75, 52);
	scene->add(undo);
	scene->add(quit);

	es = new EventSolver();
//	es->setChessBoard(this);
	render();
}

void ChessBoardInterface::createBoard() {
	View* viewChessBoard = new View("images/chessBoard5.png");

	View* viewWhiteKing = new View("images/whiteKing.png");
	View* viewWhiteQueen = new View("images/whiteQueen.png");
	View* viewWhiteBishop1 = new View("images/whiteBishop.png");
	View* viewWhiteBishop2 = new View("images/whiteBishop.png");
	View* viewWhiteKnight1 = new View("images/whiteKnight.png");
	View* viewWhiteKnight2 = new View("images/whiteKnight.png");
	View* viewWhiteRook1 = new View("images/whiteRook.png");
	View* viewWhiteRook2 = new View("images/whiteRook.png");

	View* viewWhitePawn[8];
	for (int i = 0; i < 8; i++) {
		viewWhitePawn[i] = new View("images/whitePawn.png");
	}

	///////////////////////////////////////////////////////////////////////////
	View* viewBlackKing = new View("images/blackKing.png");
	View* viewBlackQueen = new View("images/blackQueen.png");
	View* viewBlackBishop1 = new View("images/blackBishop.png");
	View* viewBlackBishop2 = new View("images/blackBishop.png");
	View* viewBlackKnight1 = new View("images/blackKnight.png");
	View* viewBlackKnight2 = new View("images/blackKnight.png");
	View* viewBlackRook1 = new View("images/blackRook.png");
	View* viewBlackRook2 = new View("images/blackRook.png");
	View* viewBlackPawn[8];
	for (int i = 0; i < 8; i++) {
		viewBlackPawn[i] = new View("images/blackPawn.png");
	}

	Node* chessBoard = new Node(scene, viewChessBoard);
	chessBoard->set(0, 0, 400, 400);
	Node* whiteKing = new Node(scene, viewWhiteKing);
	whiteKing->set(150, 350, 50, 50);
	Node* whiteQueen = new Node(scene, viewWhiteQueen);
	whiteQueen->set(200, 350, 50, 50);
	Node* whiteBishop1 = new Node(scene, viewWhiteBishop1);
	whiteBishop1->set(100, 350, 50, 50);
	Node* whiteBishop2 = new Node(scene, viewWhiteBishop2);
	whiteBishop2->set(250, 350, 50, 50);
	Node* whiteKnight1 = new Node(scene, viewWhiteKnight1);
	whiteKnight1->set(50, 350, 50, 50);
	Node* whiteKnight2 = new Node(scene, viewWhiteKnight2);
	whiteKnight2->set(300, 350, 50, 50);
	Node* whiteRook1 = new Node(scene, viewWhiteRook1);
	whiteRook1->set(0, 350, 50, 50);
	Node* whiteRook2 = new Node(scene, viewWhiteRook2);
	whiteRook2->set(350, 350, 50, 50);
	Node* whitePawn[8];
	for (int i = 0; i < 8; i++) {
		whitePawn[i] = new Node(scene, viewWhitePawn[i]);
		whitePawn[i]->set(50 * i, 300, 50, 50);
	}

	Node* blackKing = new Node(scene, viewBlackKing);
	blackKing->set(150, 0, 50, 50);
	Node* blackQueen = new Node(scene, viewBlackQueen);
	blackQueen->set(200, 0, 50, 50);
	Node* blackBishop1 = new Node(scene, viewBlackBishop1);
	blackBishop1->set(100, 0, 50, 50);
	Node* blackBishop2 = new Node(scene, viewBlackBishop2);
	blackBishop2->set(250, 0, 50, 50);
	Node* blackKnight1 = new Node(scene, viewBlackKnight1);
	blackKnight1->set(50, 0, 50, 50);
	Node* blackKnight2 = new Node(scene, viewBlackKnight2);
	blackKnight2->set(300, 0, 50, 50);
	Node* blackRook1 = new Node(scene, viewBlackRook1);
	blackRook1->set(0, 0, 50, 50);
	Node* blackRook2 = new Node(scene, viewBlackRook2);
	blackRook2->set(350, 0, 50, 50);
	Node* blackPawn[8];
	for (int i = 0; i < 8; i++) {
		blackPawn[i] = new Node(scene, viewBlackPawn[i]);
		blackPawn[i]->set(50 * i, 50, 50, 50);
	}

	scene->add(chessBoard);
	scene->add(whiteKing);
	scene->add(whiteQueen);
	scene->add(whiteBishop1);
	scene->add(whiteBishop2);
	scene->add(whiteKnight1);
	scene->add(whiteKnight2);
	scene->add(whiteRook1);
	scene->add(whiteRook2);
	for (int i = 0; i < 8; i++) {
		scene->add(whitePawn[i]);
	}
	scene->add(blackKing);
	scene->add(blackQueen);
	scene->add(blackBishop1);
	scene->add(blackBishop2);
	scene->add(blackKnight1);
	scene->add(blackKnight2);
	scene->add(blackRook1);
	scene->add(blackRook2);
	for (int i = 0; i < 8; i++) {
		scene->add(blackPawn[i]);
	}
}

void ChessBoardInterface::run() {
	int frameTime = 1000 / FPS, lastTime, now;
	while (running()) {
		lastTime = SDL_GetTicks() + frameTime;

		handleEvent();
		update();
		render();

		now = SDL_GetTicks();
		if (now < lastTime) SDL_Delay(lastTime - now);
	}
}

void ChessBoardInterface::handleEvent() {
	SDL_Event event;
	if (SDL_WaitEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = 0;
			break;
		case SDL_MOUSEMOTION:

			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				es->click(event.button.x, event.button.y);
			}
			break;
		case SDL_KEYDOWN:
			cout << "KEY DOWN: " << event.key.keysym.sym << endl;
			break;
		case SDL_KEYUP:
			cout << "KEY UP: " << event.key.keysym.sym << endl;
			break;
		}
	}
}

void ChessBoardInterface::update() {

}

void ChessBoardInterface::render() {
	scene->render();
}





