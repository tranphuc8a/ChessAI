#include "../hdr/PhongCapWindow.h"
#include "../hdr/Xe.h"
#include "../hdr/Ma.h"
#include "../hdr/Tuong.h"
#include "../hdr/Hau.h"
#include "SDL.h"
#include "../hdr/Scene.h"

PhongCapWindow::PhongCapWindow(Player * player) 
	: Window("Phong cap", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 200, 50){
	piece[1] = new Hau(player, 1, 1);
	piece[2] = new Xe(player, 1, 2);
	piece[3] = new Ma(player, 1, 3);
	piece[4] = new Tuong(player, 1, 4);
	for (int i = 1; i <= 4; i++){
		piece[i]->init();
		piece[i]->setScene(scene);
		scene->add(piece[i]);
	}
}
PhongCapWindow::~PhongCapWindow(){
	
}

char PhongCapWindow::getPiece(){
	render();
	int r, c;
	while (1){
		SDL_Event e;
		SDL_WaitEvent(&e);
		switch(e.type){
		case SDL_MOUSEBUTTONDOWN:
			r = e.button.y/50 + 1;
			c = e.button.x/50 + 1;
			if (r == 1){
				switch(c){
				case 1: return 'H';
				case 2: return 'X';
				case 3: return 'M';
				case 4: return 'T';
				}
			}
			break;	
		}
	}
}


