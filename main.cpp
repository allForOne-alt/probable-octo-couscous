#include <SDL2/SDL.h>
#include <iostream>
#include <string>

bool init();
bool loadMedia();
void close();
 
enum class KeyPressSurfaces {
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* surfaceScreen = NULL;
//rectange ko specs
SDL_Rect rect = {320, 210, 200, 200};

SDL_Surface* imageSurface = NULL;
SDL_Surface* KeyPressSurface[static_cast<int>(KeyPressSurfaces::KEY_PRESS_SURFACE_TOTAL)];

bool init() {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 420;
    bool success =  true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize video!" <<std::endl;
        success = false;
    }
    else {
        window = SDL_CreateWindow("Base Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(window== NULL && renderer == NULL) {
            std::cerr << "Unable to create window and/or renderer! SDL_Error : "<<SDL_GetError()<<std::endl; 
            success = false;
        }
        else {
            surfaceScreen = SDL_GetWindowSurface(window);
        }
    }
    return success;
}

bool loadMedia() {
    bool success = true;
    //set drawing color for the backgound ( white)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    if(SDL_RenderClear(renderer) < 0) {
        std::cerr << "Unable to clear the old frame! SDL_Error : "<<SDL_GetError() <<std::endl;
        success = false;
    } 
    else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        if(SDL_RenderDrawRect(renderer, &rect) < 0) {
            std::cerr << "Couldnt Draw the rectangle! SDL_Error : " <<SDL_GetError()<<std::endl;
            success = false;
        }
    }
    return success;
}

void close() {
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

int main(int argc, char* argv[]){
    if(!init()){
        std::cerr <<"Failed to initialize! SDL_Error : "<<SDL_GetError() <<std::endl;
    }
    else {
        if(!loadMedia()) {
            std::cerr << "Failed to load image! SDL_Error : "<<SDL_GetError() <<std::endl;
        }
        else{
            SDL_Event e;
            bool quit =false;
            while(quit == false){
                while(SDL_PollEvent (&e)){
                    if(e.type == SDL_QUIT){
                        quit = true;
                    }
                }
            }
        }
   }
   close();
   return 0;
}

