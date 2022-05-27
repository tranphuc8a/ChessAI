#pragma once

#include "SDL.h"
#include <iostream>
#include <vector>
using namespace std;


class Window;
class Node;

class Scene {
public:
	Scene();
	Scene(Window* par);
	~Scene();


	void setColor(int red, int green, int blue, int alpha);
	void clear();
	void update();
	void render();
	void add(Node* node);
	void remove(Node* node);
	void clearChild();
public:
	SDL_Renderer* renderer = nullptr;
	Window* window;
	vector<Node*> child;
};


