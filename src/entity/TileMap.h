//
// Created by jack on 30/09/19.
//

#ifndef HELLOSDL_TILEMAP_H
#define HELLOSDL_TILEMAP_H

#include <vector>
#include "SDLGameObject.h"


class TileMap
{
public:
    TileMap();
    void render();

private:

    std::vector<SDLGameObject*> m_tiles;

};

#endif //HELLOSDL_TILEMAP_H
