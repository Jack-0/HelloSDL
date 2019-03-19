//
// Created by jack on 17/03/19.
//

#ifndef HELLOSDL_PLAYER_H
#define HELLOSDL_PLAYER_H

//#include "GameObject.h"
#include "SDLGameObject.h"
//#include <SDL2/SDL.h>

class Player : public SDLGameObject
{
public:
    // TODO should we be using virtual?
 //   void load(int x, int y, int w, int h, std::string id);
    Player(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    //virtual void clean();
};


#endif //HELLOSDL_PLAYER_H
