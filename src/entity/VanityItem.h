//
// Created by jack on 10/08/19.
//

#ifndef HELLOSDL_VANITYITEM_H
#define HELLOSDL_VANITYITEM_H


#include "SDLGameObject.h"

class VanityItem : SDLGameObject
{
public:
    VanityItem();

    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(const LoaderParams* pParams);

    void setPos(int x, int y)
    {
        m_pos.setX(x);
        m_pos.setY(y);
    }
};


#endif //HELLOSDL_VANITYITEM_H
