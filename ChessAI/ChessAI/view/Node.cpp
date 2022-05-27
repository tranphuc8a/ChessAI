#include "../hdr/Node.h"
#include "../hdr/View.h"
#include "../hdr/Scene.h"
#include <algorithm>

Node::Node() {
	set(0, 0, 0, 0);
	scene = nullptr;
	window = nullptr;
}
Node::Node(Scene* scene) : Node() {
	if (scene == nullptr) return;
	else setScene(scene);
}
Node::Node(Scene* scene, View* view) : Node(scene) {
	setView(view);
}
Node::~Node() {
	
}

void Node::setScene(Scene* scene) {
	if (!scene) return;
	this->scene = scene;
	this->window = scene->window;
	if (view != nullptr) {
		view->setScene(scene);
	}
}

void Node::setSize(int w, int h) {
	this->w = w;
	this->h = h;
}
void Node::setPos(int x, int y) {
	this->x = x;
	this->y = y;
}
void Node::set(int x, int y, int w, int h) {
	setSize(w, h);
	setPos(x, y);
}

void Node::setView(View* view) {
	this->view = view;
	if (view != nullptr) {
		view->setScene(scene);
	}
}

void Node::update() {
	// update this
	for (auto it : this->child) {
		it->update();
	}
}
void Node::render() {
	SDL_RenderCopy(scene->renderer, view->texture, NULL, this);
	for (auto &it : this->child) {
		it->render();
	}
}
void Node::add(Node* node) {
	if (!node) return;
	child.push_back(node);
	node->setScene(scene);
}
void Node::remove(Node* node) {
	std::remove(begin(child), end(child), node);
}

void Node::clearChild(){
	child.clear();
}



