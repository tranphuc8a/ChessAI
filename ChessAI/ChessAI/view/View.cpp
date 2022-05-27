#include "../hdr/View.h"
#include "../hdr/Scene.h"
#include "SDL_TTF.h"

View::View() {

}

View::View(string path) {
	loadImage(path);
}

View::~View() {
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void View::setScene(Scene* scene) {
	this->scene = scene;
	if (scene != nullptr) {
		SDL_DestroyTexture(texture);
		texture = SDL_CreateTextureFromSurface(scene->renderer, surface);
	}
}

void View::loadImage(string path) {
	SDL_Surface* s = IMG_Load(path.c_str());
	if (s) {
		if (surface != nullptr)
			SDL_FreeSurface(surface);
		surface = s;
		if (scene != nullptr) {
			SDL_DestroyTexture(texture);
			texture = SDL_CreateTextureFromSurface(scene->renderer, surface);
		}
	}
	else {
		cout << IMG_GetError() << endl;
	}
}
void View::loadText(string text) {
	TTF_Font* Sans = TTF_OpenFont("Font/arial.ttf", 30);
	if (Sans) cout << "load font done" << endl;
	else cout << TTF_GetError() << endl;
	SDL_Color White = { 0, 0, 0 };
	SDL_Surface* s = TTF_RenderText_Solid(Sans, text.c_str(), White);

	if (s) {
		if (surface != nullptr)
			SDL_FreeSurface(surface);
		surface = s;
		if (scene != nullptr) {
			SDL_DestroyTexture(texture);
			texture = SDL_CreateTextureFromSurface(scene->renderer, surface);
		}
		cout << "load text done" << endl;
	}
	else {
		cout << TTF_GetError() << endl;
	}
}

