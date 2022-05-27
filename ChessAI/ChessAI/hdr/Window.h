#pragma once

#include "SDL.h"
#include <iostream>
#include <string>
using namespace std;

class Scene;

class Window {
public:
	Window();
	Window(string t, int x, int y, int w, int h);
	~Window();

	void init();
	void show();
	void hide();
	void setScene(Scene* scene);
	void set(string t, int x, int y, int w, int h);
	void setTitle(string t);
	void setPos(int x, int y);
	void setSize(int w, int h);
	void clear();
	void destroy();
	virtual void handleEvent();
	bool running() { return isRunning; }
	virtual void update();
	virtual void render();
	virtual void run();
public:
	bool isRunning = 0;
	SDL_Window* window = nullptr;
	Scene* scene = nullptr;
	int posx, posy, width, height;
	string title;
};



