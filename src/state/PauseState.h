//
// Created by jack on 05/06/19.
//

#ifndef HELLOSDL_PAUSESTATE_H
#define HELLOSDL_PAUSESTATE_H


#include <vector>
#include "GameState.h"
#include "../entity/GameObject.h"
#include "MenuState.h"

class PauseState : public MenuState
{
public:

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_pauseID; }

private:

    virtual void setCallbacks(const std::vector<Callback>& callbacks);

    static void s_pauseToMain();
    static void s_resumePlay();

    static const std::string s_pauseID;

    std::vector<GameObject*> m_gameObjects;

};


#endif //HELLOSDL_PAUSESTATE_H
