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

    void draw(SDL_Renderer* prenderer);
    void load(int x, int y, int  w, int h, std::string id);
    void update();
    void clean();

protected:

    std::string texture_id;

    int m_currentFrame = 1;
    int m_currentRow = 1;

    int m_x;
    int m_y;

    int m_height;
    int m_width;

};


#endif //HELLOSDL_GAMEOBJECT_H
