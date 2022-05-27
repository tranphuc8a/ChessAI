#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "hdr/Game.h"
#include "hdr/PhongCapWindow.h"
#include "hdr/Human.h"

using namespace std;

int main(int argc, char ** argv){
    TTF_Init();
    SDL_Init(SDL_INIT_EVERYTHING);
        
    Game * game = new Game();
    game->init();

    game->start();
    
    return 0;
}
