//
// Created by jack on 19/03/19.
//

#ifndef HELLOSDL_SDLGAMEOBJECT_H
#define HELLOSDL_SDLGAMEOBJECT_H

//#include "Game.h"
#include "GameObject.h"

class SDLGameObject : GameObject
{
public:
    SDLGameObject(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    //virtual void clean();

    //void moveLeft();
    void moveRight();

private:
    int m_x;
    int m_y;

    int m_width;
    int m_height;

    int m_currentRow;
    int m_currentFrame;

    std::string m_texutreID;

};


#endif //HELLOSDL_SDLGAMEOBJECT_H
