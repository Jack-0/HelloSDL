//
// Created by jack on 31/05/19.
//

#ifndef HELLOSDL_MAINMENUSTATE_H
#define HELLOSDL_MAINMENUSTATE_H

#include <vector>
#include "GameState.h"
#include "../entity/GameObject.h"
#include "MenuState.h"

class MainMenuState : public MenuState
{
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();


    virtual std::string getStateID() const {return s_menuID;}


private:

    virtual void setCallbacks(const std::vector<Callback>& callbacks);

    // functions used with button callbacks
    static void s_menuToPlay();
    static void s_exitFromMenu();

    static const std::string s_menuID;
    std::vector<GameObject*> m_gameObjects;

};


#endif //HELLOSDL_MAINMENUSTATE_H
