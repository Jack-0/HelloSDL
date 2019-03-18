//
// Created by jack on 18/03/19.
//

#ifndef HELLOSDL_ENEMY_H
#define HELLOSDL_ENEMY_H

#import "GameObject.h"

class Enemy : public GameObject
{
public:

    //void load(int x, int y, int w, int h, std::string id);
    //void draw(SDL_Renderer* pRenderer);
    void update();

};


#endif //HELLOSDL_ENEMY_H
