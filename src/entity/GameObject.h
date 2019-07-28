//
// Created by jack on 17/03/19.
//

#ifndef HELLOSDL_GAMEOBJECT_H
#define HELLOSDL_GAMEOBJECT_H


#include "../utilities/LoaderParams.h"

/// GameObject is an abstract class that represent the abstract concept of a game object (interface)

class GameObject
{
public:

    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;
    virtual void load(const LoaderParams* pParams) = 0;

protected:

    GameObject() {}
    virtual ~GameObject() {}
};


#endif //HELLOSDL_GAMEOBJECT_H
