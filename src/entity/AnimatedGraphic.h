//
// Created by jack on 20/07/19.
//

#ifndef HELLOSDL_ANIMATEDGRAPHIC_H
#define HELLOSDL_ANIMATEDGRAPHIC_H


#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject
{
public:
    AnimatedGraphic(const LoaderParams* params, int animSpeed);
    virtual void update();
    virtual void draw();
    virtual void clean();
private:
    int m_animSpeed;
    int m_numFrames = 2;
};


#endif //HELLOSDL_ANIMATEDGRAPHIC_H
