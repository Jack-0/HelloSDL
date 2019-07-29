//
// Created by jack on 25/07/19.
//

#include "GameObjectFactory.h"


GameObjectFactory* GameObjectFactory::s_pInstance = 0; // singleton

bool GameObjectFactory::registerType(std::string typeID, BaseCreator* pCreator)
{
        std::cout << "GOF in register typeID is" << typeID << "\n";
        std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
        // if the type is already registered do nothing
        if(it != m_creators.end())
        {
            delete pCreator;
            return false;
        }

        m_creators[typeID] = pCreator;

        return true;
}


GameObject* GameObjectFactory::create(std::string typeID)
{
        std::cout << "GameObjectFactory :: create() \n";
        std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

        if(it == m_creators.end())
        {
            std::cout << "\tcould not find type: " << typeID << "\n";
            return NULL;
        }
        std::cout << "\tfound: " << typeID << "\n";

        BaseCreator* pCreator = (*it).second;
        //std::cout << "it.second = " << &pCreator << "\n";
        return pCreator->createGameObject();
}
