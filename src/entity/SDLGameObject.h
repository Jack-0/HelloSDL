//
// Created by jack on 19/03/19.
//

#ifndef HELLOSDL_SDLGAMEOBJECT_H
#define HELLOSDL_SDLGAMEOBJECT_H

#include "GameObject.h"
#include "../graphics/TextureManager.h"
#include "../utilities/Vector2D.h"

/// SDLGameObject interfaces GameObject and is a specific case that uses SDL

class SDLGameObject : public GameObject
{
public:
    SDLGameObject(const LoaderParams* pParams);

    virtual void draw() override;
    virtual void update() override;
    virtual void clean();

    // animate and draw a certain frame
    // TODO these need to go we change frame with m_currentFrame
    void drawGiven(std::string texID, int frame);
    void changeFrame(int frames, int speed);


    Vector2D& getPosition() {return m_pos;}
    int getWidth() {return m_width;}
    int getHeight() {return m_height;}

    // movement
    void setXvelocity(float x){
        m_velocity.setX(x);
    }
    void setYvelocity(float y){
        m_velocity.setY(y);
    }

    void setXacceleration(float x){m_acceleration.setX(x);}
    void setYacceleration(float y){m_acceleration.setY(y);}




protected:
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
