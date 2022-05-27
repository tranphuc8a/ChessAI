#include "../hdr/Window.h"
#include "../hdr/Scene.h"

Window::Window() {
	window = SDL_CreateWindow(title.c_str(), posx, posy, width, height, SDL_WINDOW_RESIZABLE);
	set("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400);
	setScene(new Scene(this));
	isRunning = 1;
}
Window::Window(string t, int x, int y, int w, int h) {
	window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_RESIZABLE);
	set(t, x, y, w, h);
	setScene(new Scene(this));
	isRunning = 1;
}
Window::~Window() {

}

void Window::init() {

}
void Window::destroy(){
	SDL_DestroyWindow(window);
}
void Window::set(string t, int x, int y, int w, int h) {
	setTitle(t);
	setSize(w, h);
	setPos(x, y);
}
void Window::show() {
	SDL_ShowWindow(window);
}
void Window::hide() {
	SDL_HideWindow(window);
}
void Window::setScene(Scene* scene) {
	this->scene = scene;
}
void Window::setTitle(string t) {
	title = t;
	SDL_SetWindowTitle(window, title.c_str());
}
void Window::setPos(int x, int y) {
	posx = x, posy = y;
	SDL_SetWindowPosition(window, x, y);
}
void Window::setSize(int w, int h) {
	width = w, height = h;
	SDL_SetWindowSize(window, w, h);
}
void Window::clear() {
	SDL_DestroyWindow(window);
}
void Window::handleEvent() {
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
				if (event.button.clicks == 1) {
					cout << "SINGLE CLICKS: ";
				}
				else {
					cout << "DOUBLE CLICKS: ";
				}
				cout << event.button.x << " - " << event.button.y << endl;
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
void Window::update() {

}
void Window::render() {
	scene->render();
}

void Window::run() {
	while (isRunning) {
		handleEvent();
		update();
		render();
	}
}


