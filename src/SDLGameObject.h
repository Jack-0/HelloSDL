//
// Created by jack on 19/03/19.
//

#ifndef HELLOSDL_SDLGAMEOBJECT_H
#define HELLOSDL_SDLGAMEOBJECT_H

#include "GameObject.h"
#include "TextureManager.h"
#include "Vector2D.h"

/// SDLGameObject interfaces GameObject and is a specific case that uses SDL

class SDLGameObject : public GameObject
{
public:
    SDLGameObject(const LoaderParams* pParams);

    virtual void draw() override;
    virtual void update() override;
    //virtual void clean();

    // animate and draw a certain frame
    void drawGiven(std::string texID, int frame);
    void changeFrame(int frames, int speed);

    // movement
    void setXvelocity(float x){
        std::cout << "x set call with" << x <<"\n";
        m_velocity.setX(x);}
    void setYvelocity(float y){
        std::cout << "y set call with" << y <<"\n";
        m_velocity.setY(y);}

    void setXacceleration(float x){m_acceleration.setX(x);}
    void setYacceleration(float y){m_acceleration.setY(y);}


private:
    Vector2D m_pos;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    int m_width;
    int m_height;

    int m_currentRow;
    int m_currentFrame;

    std::string m_texutreID;

};

#endif //HELLOSDL_SDLGAMEOBJECT_H
