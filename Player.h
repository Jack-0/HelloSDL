//
// Created by jack on 17/03/19.
//

#ifndef HELLOSDL_PLAYER_H
#define HELLOSDL_PLAYER_H

#include "GameObject.h"
#include <SDL2/SDL.h>

class Player : public GameObject // Player inherits from GameObject
{
public:
    // TODO should we be using virtual?
    void load(int x, int y, int w, int h, std::string id);
    void draw(SDL_Renderer* pRenderer);
    void update();
    void clean();
};


#endif //HELLOSDL_PLAYER_H
