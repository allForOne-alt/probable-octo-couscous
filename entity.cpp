#include "entity.h"

entity::entity(int x, int y, int h, int w) {
    rect.x = x;
    rect.y = y;
    rect.h = h;
    rect.w = w;
    velo_x = 0;
    velo_y = 0;
}

bool entity::checkCollision(entity& otherEntity) {
    SDL_Rect otherrect = otherEntity.getRect();
    SDL_Rect eRect = rect;

    if(eRect.x > otherrect.x + otherrect.w){
        return false;
    }
    if(eRect.y > otherrect.y + otherrect.h){
        return false;
    }
    if(otherrect.x > eRect.x + eRect.w) {
        return false;
    }
    if(otherrect.y > eRect.x + eRect.h){
        return false;
    }
    return true;

}

collisionSides getCollidedSides(SDL_Rect a, SDL_Rect b) {

    // a-bottom-collision
    if(a.y < b.y && a.y + a.h >= b.y){
        return collisionSides::BOTTOM;
    }
    // a-top-collision
    if(b.y < a.y && a.y <= b.y + b.h) {
        return collisionSides::TOP;
    }
    // a-right-collisino
    if(a.x + a.w >= b.x && a.x < b.x + b.w){
        return collisionSides::RIGHT;
    }
    //a-left-collision
    if(a.x + a.w > b.x && a.x <= b.x + b.w){
        return collisionSides::LEFT;
    }

    return collisionSides::NONE;

} 

std::ostream& operator<<(std::ostream& out, const collisionSides sides) {
    out << sides;
    return out;
}


