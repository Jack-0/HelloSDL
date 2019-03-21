//
// Created by jack on 19/03/19.
//

#ifndef HELLOSDL_SDLGAMEOBJECT_H
#define HELLOSDL_SDLGAMEOBJECT_H

#include "GameObject.h"

/// SDLGameObject interfaces GameObject and is a specific case that uses SDL

class SDLGameObject : GameObject
{
public:
    SDLGameObject(const LoaderParams* pParams);

    virtual void draw() override;
    virtual void update() override;
    //virtual void clean();

    //void moveLeft();
    void moveRight ();
    void changeFrame();

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
