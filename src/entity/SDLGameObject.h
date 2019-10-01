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
    SDLGameObject();

    virtual void draw() override;
    virtual void update() override;
    virtual void clean();
    virtual void load(const LoaderParams* pParams);

    Vector2D& getPosition() {return m_pos;}
    int getWidth() {return m_width;}
    int getHeight() {return m_height;}

    // movement
    void setXvelocity(float x) { m_velocity.setX(x); }
    void setYvelocity(float y) { m_velocity.setY(y); }

    // set alive and check alive to see the state of the SDLGameObject
    void kill() { m_alive = false; }
    bool alive(){ return m_alive; }

protected:
    Vector2D m_pos = Vector2D(0, 0);
    Vector2D m_velocity = Vector2D(0, 0);
    Vector2D m_acceleration = Vector2D(0, 0);

    int m_width;
    int m_height;

    int m_numFrames;
    int m_animSpeed = 200;
    int m_currentRow;
    int m_currentFrame;

    float m_speed = 1.0f;

    bool m_alive = true;

    std::string m_texutreID;
};

#endif //HELLOSDL_SDLGAMEOBJECT_H
