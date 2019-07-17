//
// Created by jack on 05/06/19.
//

#ifndef HELLOSDL_PAUSESTATE_H
#define HELLOSDL_PAUSESTATE_H


#include <vector>
#include "GameState.h"
#include "../entity/GameObject.h"

class PauseState : public GameState
{
public:

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_pauseID; }

private:

    bool end = false; // solves the issues with pausing, sometimes causing a seg fault crash

    static void s_pauseToMain();
    static void s_resumePlay();

    static const std::string s_pauseID;

    std::vector<GameObject*> m_gameObjects;

};


#endif //HELLOSDL_PAUSESTATE_H
