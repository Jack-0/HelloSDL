//
// Created by jack on 20/07/19.
//

#ifndef HELLOSDL_ANIMATEDGRAPHIC_H
#define HELLOSDL_ANIMATEDGRAPHIC_H


#include "SDLGameObject.h"
#include "../factory/GameObjectFactory.h"

class AnimatedGraphic : public SDLGameObject
{
public:
    AnimatedGraphic();

    virtual void load(const LoaderParams *pParams);
    virtual void update();
    virtual void draw();
    virtual void clean();
private:
    int m_animSpeed;
    int m_numFrames = 2;
};

class AnimatedGraphicCreator : public BaseCreator
{
public:
    virtual GameObject* createGameObject() const
    {
        return new AnimatedGraphic();
    }

};

#endif //HELLOSDL_ANIMATEDGRAPHIC_H
