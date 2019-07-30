//
// Created by jack on 19/03/19.
//

#ifndef HELLOSDL_LOADERPARAMS_H
#define HELLOSDL_LOADERPARAMS_H

#include <string>

class LoaderParams
{
public:

    LoaderParams(int x, int y, int w, int h, std::string textureID, int numFrames, int callbackID=0, int animSpeed=0)
    :
    m_x(x),
    m_y(y),
    m_width(w),
    m_height(h),
    m_textureID(textureID),
    m_numFrames(numFrames),
    m_callbackID(callbackID),
    m_animSpeed(animSpeed)
    {
    }

    int getX() const {return m_x; }
    int getY() const {return m_y; }
    int getHeight() const {return m_height;}
    int getWidth() const {return m_width;}
    int getCallbackID() const {return m_callbackID;}
    int getNumFrames() const {return m_numFrames;}
    int getAnimSpeed() const {return m_animSpeed;}
    std::string getTextureID() const {return m_textureID;}


private:

    int m_x;
    int m_y;
    int m_height;
    int m_width;
    int m_numFrames;
    int m_callbackID;
    int m_animSpeed;
    std::string m_textureID;
};


#endif //HELLOSDL_LOADERPARAMS_H
