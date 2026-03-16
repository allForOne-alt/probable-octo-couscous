#include <SDL2/SDL.h>
#include <iostream>

enum class collisionSides{
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    NONE
};

collisionSides getCollidedSides(SDL_Rect a, SDL_Rect b);
std::ostream& operator<<(std::ostream& out, const collisionSides sides);

class  entity{
    protected:
    SDL_Rect rect;
    int velo_x, velo_y;

    public:
    entity(int x, int y, int h, int w);

    virtual void update() = 0;
    virtual bool checkCollision(entity& otherEntity);
    virtual bool render(SDL_Renderer* renderer) = 0; 
    SDL_Rect getRect(){return rect;}

    virtual ~entity(){
        std::cout << "Called entity Destructor" <<std::endl;
    }
};

class Player: public entity{

    public:
    Player(int x, int y, int h, int w): entity(x,  y,  h,  w){}

    void update() override{}
     
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
    
    int xPosition() {
        return rect.x;
    }
    
    int yPosition() {
        return rect.y;
    }

    bool render(SDL_Renderer* renderer) override {
        SDL_SetRenderDrawColor(renderer, 0,0, 255, 255);
        SDL_RenderDrawRect(renderer, &rect);
        return true;
    }
    
    void setPosition(int x, int y) {
        rect.x = x;
        rect.y = y;
    }
};

class Enemy: public entity{
    public:
    Enemy(int x, int y , int h, int w): entity(x, y, h, w){}

    void update() override{}
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
    
    int xPosition(){
        return rect.x;
    }

    int yPosition() {
        return rect.y;
    }
    void setPosition(int x, int y) {
        rect.x = x;
        rect.y = y;
    }
 
    bool render(SDL_Renderer* renderer) override {
        SDL_SetRenderDrawColor(renderer, 255, 0 ,255, 0);
        SDL_RenderDrawRect(renderer, &rect);
        return true;
    }
};
    