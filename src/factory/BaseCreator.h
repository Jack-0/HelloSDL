//
// Created by jack on 23/07/19.
//

#ifndef HELLOSDL_BASECREATOR_H
#define HELLOSDL_BASECREATOR_H

#endif //HELLOSDL_BASECREATOR_H

#include <string>
#include <map>
#include "../entity/GameObject.h"

class BaseCreator
{
public:
    virtual GameObject* createGameObject() const = 0;
    virtual ~BaseCreator() {}
};