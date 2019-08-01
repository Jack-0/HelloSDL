//
// Created by jack on 31/05/19.
//

#include "Button.h"
#include "../utilities/SoundManager.h"

Button::Button() : SDLGameObject()
{
}

void Button::load(const LoaderParams *pParams)
{
    SDLGameObject::load(pParams);
    m_callbackID = pParams->getCallbackID();
    m_currentFrame = MOUSE_OUT;

}

void Button::draw()
{
    SDLGameObject::draw();
}

void Button::update()
{
    //Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();
    float mx = TheInputHandler::Instance()->getMouseX();
    float my = TheInputHandler::Instance()->getMouseY();


    if(mx < (m_pos.getX() + m_width)
    && mx > m_pos.getX()
    && my < (m_pos.getY() + m_height)
    && my > m_pos.getY() )
    {
        if(TheInputHandler::Instance()->getMouseButtonStates(LEFT) && m_bReleased)
        {
            m_currentFrame = CLICKED;
            m_callback(); // call out call back function
            m_bReleased = false;
            TheSoundManager::Instance()->play("bang");
        }
        else if (!TheInputHandler::Instance()->getMouseButtonStates(LEFT))
        {
            m_bReleased = true;
            m_currentFrame = MOUSE_OVER;
            if(!soundPlayedOnMouseOver)
            {
                TheSoundManager::Instance()->play("beep");
                soundPlayedOnMouseOver = true;
            }
        }
    }
    else
    {
        soundPlayedOnMouseOver = false;
        m_currentFrame = MOUSE_OUT;
    }
}

void Button::clean()
{
    SDLGameObject::clean();
}
