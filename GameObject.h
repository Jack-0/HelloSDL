//
// Created by jack on 17/03/19.
//

#ifndef HELLOSDL_GAMEOBJECT_H
#define HELLOSDL_GAMEOBJECT_H


#include "LoaderParams.h"

class GameObject
{
public:

    //virtual void load() = 0;
    virtual void draw() = 0;
    virtual void update() = 0;
    //virtual void clean() = 0;

protected:

    GameObject(const LoaderParams* pParams) {}
    virtual ~GameObject() {}

};


#endif //HELLOSDL_GAMEOBJECT_H
