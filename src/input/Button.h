//
// Created by jack on 31/05/19.
//

#ifndef HELLOSDL_BUTTON_H
#define HELLOSDL_BUTTON_H

#include "../entity/SDLGameObject.h"
#include "InputHandler.h"

class Button : public SDLGameObject
{
public:

    Button();

    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(const LoaderParams* pParams);

    void setCallBack(void(*callback) ()) { m_callback = callback; }
    int getCallbackID() { return m_callbackID; }

private:

    enum btn_state
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    void (*m_callback) ();

    int m_callbackID;
    bool m_bReleased;
    bool soundPlayedOnMouseOver = false;
};

class ButtonCreator : public BaseCreator
{
public:
    virtual GameObject* createGameObject() const
    {
        return new Button();
    }

};

#endif //HELLOSDL_BUTTON_H
