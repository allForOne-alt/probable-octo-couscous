#include "entity.h"

bool init();
void close();
 
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* surfaceScreen = NULL;

Player player(320, 210, 80, 80);
Enemy enemy(230, 220, 90, 90);

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
            SDL_Event e;
            bool quit =false;
            while(quit == false){
                while(SDL_PollEvent (&e)){
                    if(e.type == SDL_QUIT){
                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN){
                        switch(e.key.keysym.sym){
                            case SDLK_UP:
                            player.setPosition(player.getRect().x, player.getRect().y - 30);
                            break;

                            case SDLK_DOWN:
                            player.setPosition(player.getRect().x, player.getRect().y + 30);
                            break;

                            case SDLK_LEFT:
                            player.setPosition(player.getRect().x - 30, player.getRect().y);
                            break;

                            case SDLK_RIGHT:
                            player.setPosition(player.getRect().x + 30, player.getRect().y);
                            break;

                            case SDLK_w:
                            enemy.setPosition(enemy.getRect().x, player.getRect().y - 30);
                            break;
                            
                            case SDLK_s:
                            enemy.setPosition(enemy.getRect().x, enemy.getRect().y + 30);
                            break;

                            case SDLK_a:
                            enemy.setPosition(enemy.getRect().x - 30, enemy.getRect().y);
                            break;

                            case SDLK_d:
                            enemy.setPosition(enemy.getRect().x + 30, enemy.getRect().y);
                            break;

                            default:
                            break;
                        }
                }
            }
                std::cout << "Player x : "<<player.xPosition() <<" y: "<<player.yPosition()<<std::endl;

                collisionSides playerCollision = getCollidedSides(player.getRect(), enemy.getRect());
                if(player.checkCollision(enemy)) {
                    std::cout << "Collision from : " << playerCollision;
                }
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);

                player.render(renderer);
                enemy.render(renderer);

                SDL_RenderPresent(renderer);
            }
        }
   close();
   return 0;
}

