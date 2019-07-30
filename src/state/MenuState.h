//
// Created by jack on 28/07/19.
//

#ifndef HELLOSDL_MENUSTATE_H
#define HELLOSDL_MENUSTATE_H

#include <vector>
#include "GameState.h"

class MenuState : public GameState
{
protected:
    typedef void(*Callback) ();
    virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;

    std::vector<Callback> m_callbacks;
};


#endif //HELLOSDL_MENUSTATE_H
