//
// Created by jack on 23/07/19.
//

#include <string>
#include <iostream>
#include <map>
#include "../entity/GameObject.h"

#ifndef HELLOSDL_GAMEOBJECTFACTORY_H
#define HELLOSDL_GAMEOBJECTFACTORY_H

class BaseCreator
{
public:
    virtual GameObject* createGameObject() const = 0;
    virtual ~BaseCreator() {}
};


class GameObjectFactory
{
public:

    /// Ensure game is a singleton
    static GameObjectFactory* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new GameObjectFactory();
            return s_pInstance;
        }
    }

    bool registerType(std::string typeID, BaseCreator* pCreator);
    GameObject* create(std::string typeID);




private:
    std::map<std::string, BaseCreator*> m_creators;
    static GameObjectFactory* s_pInstance;
};

typedef GameObjectFactory TheGameObjectFactory;

#endif //HELLOSDL_GAMEOBJECTFACTORY_H
