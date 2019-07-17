//
// Created by jack on 31/05/19.
//

#ifndef HELLOSDL_PLAYSTATE_H
#define HELLOSDL_PLAYSTATE_H

#include <vector>
#include <random>
#include "GameState.h"
#include "../entity/GameObject.h"

class PlayState : public GameState
{
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string getStateID() const {return s_playID;}

private:
    int getRandom(int, int);
    void createAndAddBalloon();

    std::random_device dev;
    static const std::string s_playID;
    std::vector<GameObject*> m_gameObjects;
};


#endif //HELLOSDL_PLAYSTATE_H
