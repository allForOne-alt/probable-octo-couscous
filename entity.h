#include <SDL2/SDL.h>
#include <iostream>

class entity{
    protected:
    SDL_Rect rect;
    int velo_x, velo_y;

    public:
    entity(int x, int y, int h, int w);

    virtual void update() = 0;
    virtual bool checkCollision(entity& otherEntity);
    virtual bool render(SDL_Renderer* renderer) = 0; 
    SDL_Rect getRect();

    virtual ~entity(){
        std::cout << "entity destructor called" <<std::endl;
    }
};

class Player: public entity{

    public:
    Player(int x, int y, int h, int w): entity(x,  y,  h,  w){}

    void update() override{

    }
     
    bool checkCollision(entity& otherEntity) {
        SDL_Rect otherRect = otherEntity.getRect();
        SDL_Rect myRect = rect;

        if(myRect.x > otherRect.x + otherRect.w) {
            return false;
        }
        if(myRect.y > otherRect.y + otherRect.h){
            return false;
        }
        if(otherRect.x > myRect.x + myRect.w) {
            return false;
        }
        if(otherRect.y > myRect.y + myRect.h) {
            return false;
        }

        return true;
    }

    bool render(SDL_Renderer* renderer) {

        return true;
    }


};

class Enemy: public entity{
    public:
    Enemy(int x, int y , int h, int w): entity(x, y, h ,w){}
    void update() override{}
    bool render(SDL_Renderer* renderer){return true;}
};
    