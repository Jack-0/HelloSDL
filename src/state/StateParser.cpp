//
// Created by jack on 27/07/19.
//

#include "StateParser.h"
#include "../graphics/TextureManager.h"
#include "../Game.h"

bool StateParser::parseState(const char *stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs)
{
    TiXmlDocument xmlDoc;

    if (!xmlDoc.LoadFile(stateFile))
    {
        std::cout << "XML File not found\n" ;
        return false;
    }

    TiXmlElement* pRoot = xmlDoc.RootElement();
    TiXmlElement* pStateRoot = 0;
    // state ROOT
    for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == stateID) {
            pStateRoot = e;
            break;
        }
    }

    // textures root
    TiXmlElement* pTextureRoot = 0;
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("TEXTURES")) {
            pTextureRoot = e;
            break;
        }
    }
    parseTextures(pTextureRoot, pTextureIDs);

    // objects root
    TiXmlElement* pObjectRoot = 0;
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("OBJECTS")) {
            pObjectRoot = e;
            break;
        }
    }

    parseObjects(pObjectRoot, pObjects);
    return true;
}

void StateParser::parseTextures(TiXmlElement* pStateRoot, std::vector<std::string> *pTextureIDs)
{
    std::cout << "State Parser :: parseTextures()\n";
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        std::string filenameAttribute = e->Attribute("filename");
        std::string idAttribute = e->Attribute("ID");
        pTextureIDs->push_back(idAttribute);
        if(!TheTextureManager::Instance()->load(filenameAttribute, idAttribute, TheGame::Instance()->getRenderer()))
            std::cout << "\tfailed to load texture\n";
        else
            std::cout << "\tparsed texture at " << filenameAttribute << " successfully\n";
    }
}

void StateParser::parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*> *pObjects)
{
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        int x, y, width, height, numFrames, callBackID, animSpeed;
        std::string textureID;

        e->Attribute("x", &x);
        e->Attribute("y", &y);
        e->Attribute("width", &width);
        e->Attribute("height", &height);
        e->Attribute("numFrames", &numFrames);
        e->Attribute("callbackID", &callBackID);
        e->Attribute("animSpeed", &animSpeed);
        textureID = e->Attribute("textureID");

        // draw x and y from the center of the screen,
        x = TheGame::Instance()->getScreenCenter().getX() + x;
        y = TheGame::Instance()->getScreenCenter().getY() + y;
        // ensure the sprite is centered by negating half it's width and height
        x = x - (width / 2);
        y = y - (height / 2);

        GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type"));
        pGameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callBackID, animSpeed));
        pObjects->push_back(pGameObject);
    }
}