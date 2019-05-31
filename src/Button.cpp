//
// Created by jack on 31/05/19.
//

#include "Button.h"

Button::Button(const LoaderParams *pParams)
: SDLGameObject(pParams)
{
}

void Button::draw()
{
    SDLGameObject::draw();
}

void Button::update()
{
    SDLGameObject::update();
    SDLGameObject::changeFrame(1,1);
}