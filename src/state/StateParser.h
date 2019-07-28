//
// Created by jack on 27/07/19.
//

#ifndef HELLOSDL_STATEPARSER_H
#define HELLOSDL_STATEPARSER_H


#include <string>
#include <vector>
#include "../xml/tinyxml.h"
#include "../entity/GameObject.h"

class StateParser
{
public:
    bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs);

private:
    void parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*> *pObjects);
    void parseTextures(TiXmlElement* pStateRoot, std::vector<std::string> *pTextureIDs);
};


#endif //HELLOSDL_STATEPARSER_H
