//
// Created by jack on 17/03/19.
//

#ifndef HELLOSDL_PLAYER_H
#define HELLOSDL_PLAYER_H

#include "../SDLGameObject.h"
#include "../../input/InputHandler.h"

class Player : public SDLGameObject
{
public:

    Player(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

private:
    int speed = 4;
};


#endif //HELLOSDL_PLAYER_H
