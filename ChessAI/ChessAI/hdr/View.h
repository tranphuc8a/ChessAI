#pragma once

#include "SDL.h"
#include "SDL_Image.h"
#include <iostream>

using namespace std;

class Scene;
class View {
public:
	View();
	View(string path);
	~View();

	void loadImage(string path);
	void loadText(string text);
	void setScene(Scene* scene);
public:
	Scene* scene = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = nullptr;
};



