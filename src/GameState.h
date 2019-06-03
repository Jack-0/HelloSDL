//
// Created by jack on 31/05/19.
//

#ifndef HELLOSDL_GAMESTATE_H
#define HELLOSDL_GAMESTATE_H

#include <string>

/**
 * Abstract class
 */
class GameState
{
public:
    virtual void update() =0;
    virtual void render() = 0;

    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;

    virtual std::string getStateID() const = 0;
};

#endif //HELLOSDL_GAMESTATE_H
