//
// Created by jack on 30/09/19.
//

#include "TileMap.h"
#include "../Game.h"

TileMap::TileMap()
{
    // TODO refactor here
    TheTextureManager::Instance()->load("../res/groundtiles.png", "tiles", TheGame::Instance()->getRenderer());

    int tileW = 256;
    int tileH = 128;

    //
    int rows = ((TheGame::Instance()->getScreenHeight() / tileH ) * 2 ) + 2;
    int cols =  (TheGame::Instance()->getScreenWidth() / tileW ) + 1;

    int tileX = 0;
    int tileY = 0;
    int xOffset = 0;

    for(int i = -tileH; i < rows; i++)
    {
        if(i%2 != 0)  // odd number
            xOffset = tileW / 2;
        else
            xOffset = 0;

        for(int j = -tileW; j < cols; j++)
        {
            tileX = (j* tileW) + xOffset;
            tileY = i * tileH / 2;


            SDLGameObject* temp =  new SDLGameObject();
            temp->load(new LoaderParams(tileX,tileY,256,128,"tiles",4));
            temp->changeFrame(TheGame::Instance()->getRandom(0,3));

            m_tiles.push_back(temp);
        }
    }
}

void TileMap::render()
{
    for(int i = 0; i < m_tiles.size(); i++)
        m_tiles[i]->draw();
}

