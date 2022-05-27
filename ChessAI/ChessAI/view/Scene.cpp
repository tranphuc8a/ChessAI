#include "../hdr/Scene.h"
#include "../hdr/Window.h"
#include "../hdr/Node.h"
#include "../hdr/View.h"
#include <algorithm>

Scene::Scene() {
	window = nullptr;

}
Scene::Scene(Window* par) {
	window = par;
	renderer = SDL_CreateRenderer(par->window, -1, 0);
	setColor(255, 255, 255, 255);
	if (window->scene == nullptr) {
		window->setScene(this);
	}
}

Scene::~Scene() {

}

void Scene::add(Node* node) {
	child.push_back(node);
	node->setScene(this);
}
void Scene::remove(Node* node) {
	std::remove(begin(child), end(child), node);
}
void Scene::clearChild(){
	child.clear();
}
void Scene::update() {

}

void Scene::render() {
	SDL_RenderClear(renderer);
	for (auto it : child) {
		SDL_RenderCopy(renderer, it->view->texture, NULL, it);
	}
	SDL_RenderPresent(renderer);
}

void Scene::setColor(int red, int green, int blue, int alpha) {
	SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
}


void Scene::clear() {
	SDL_DestroyRenderer(renderer);
}



