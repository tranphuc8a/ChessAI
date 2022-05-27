#include "../hdr/ChoosePlayerWindow.h"
#include "../hdr/View.h"
#include "../hdr/Node.h"
#include "../hdr/Scene.h"

ChoosePlayerWindow::ChoosePlayerWindow()
	:Window("Choose player", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 100){
	View * hmvshm = new View("images/hmvshm.png");
	View * hmvsai = new View("images/hmvsai.png");
	View * aivshm = new View("images/aivshm.png");
	View * aivsai = new View("images/aivsai.png");
	Node * choose1 = new Node(scene, hmvshm);
	choose1->set(0, 0, 100, 100);
	Node * choose2 = new Node(scene, hmvsai);
	choose2->set(100, 0, 100, 100);
	Node * choose3 = new Node(scene, aivshm);
	choose3->set(200, 0, 100, 100);
	Node * choose4 = new Node(scene, aivsai);
	choose4->set(300, 0, 100, 100);
	scene->add(choose1);
	scene->add(choose2);
	scene->add(choose3);
	scene->add(choose4);
}
ChoosePlayerWindow::~ChoosePlayerWindow(){}

int ChoosePlayerWindow::get(){
	render();
	int r, c;
	while (1){
		SDL_Event e;
		SDL_WaitEvent(&e);
		switch(e.type){
		case SDL_MOUSEBUTTONDOWN:
			r = e.button.y/100 + 1;
			c = e.button.x/100 + 1;
			if (r == 1){
				switch(c){
				case 1: return 1;
				case 2: return 2;
				case 3: return 3;
				case 4: return 4;
				}
			}
			break;	
		}
	}
}


