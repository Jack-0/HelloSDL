//
// Created by jack on 31/05/19.
//

#ifndef HELLOSDL_BUTTON_H
#define HELLOSDL_BUTTON_H

#include "SDLGameObject.h"
#include "InputHandler.h"

class Button : public SDLGameObject
{
public:

    Button(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    //virtual void clean();
};


#endif //HELLOSDL_BUTTON_H
