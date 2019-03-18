//
// Created by jack on 17/03/19.
//

#ifndef HELLOSDL_GAMEOBJECT_H
#define HELLOSDL_GAMEOBJECT_H


#include <iostream>
#include <SDL2/SDL.h>
#include "TextureManager.h"

class GameObject
{
public:

    // virtual: use definition from type of object itself not not the type of it's pointer
    virtual void load(int x, int y, int  w, int h, std::string id);
    virtual void draw(SDL_Renderer* prenderer);
    virtual void update();
    //virtual void clean();

protected:

    std::string m_texture_id;

    int m_currentFrame = 1;
    int m_currentRow = 1;

    int m_x;
    int m_y;

    int m_height;
    int m_width;

};


#endif //HELLOSDL_GAMEOBJECT_H
