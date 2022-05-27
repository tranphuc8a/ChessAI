#pragma once

#include "SDL.h"
#include <iostream>
#include <vector>
using namespace std;

class Scene;
class Window;
class View;


class Node : public SDL_Rect {
public:
	Node();
	Node(Scene* scene);
	Node(Scene* scene, View* view);
	~Node();

	void setSize(int w, int h);
	void setPos(int x, int y);
	void set(int x, int y, int w, int h);
	void setScene(Scene* scene);
	void setView(View* view);
	virtual void update();
	virtual void render();
	void add(Node*);
	void remove(Node*);
	void clearChild();
public:
	Scene* scene = nullptr;
	Window* window = nullptr;
	View* view = nullptr;
	vector<Node*> child;
};


