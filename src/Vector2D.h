//
// Created by jack on 21/03/19.
//

#ifndef HELLOSDL_VECTOR2D_H
#define HELLOSDL_VECTOR2D_H

#include <math.h>

class Vector2D
{
public:

    Vector2D(float x, float y) : m_x(x), m_y(y){};

    Vector2D operator+(const Vector2D &v2) const
    {
        return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
    }

    friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
    {
        v1.m_x += v2.m_x;
        v1.m_y += v2.m_y;
        return v1;
    };

    Vector2D operator*(float scalar)
    {
        return Vector2D(m_x * scalar, m_y * scalar);
    };

    Vector2D& operator*=(float scalar)
    {
        m_x *= scalar;
        m_y *= scalar;

        return *this;
    };

    Vector2D operator-(const Vector2D& v2) const
    {
        return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
    };

    friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
    {
        v1.m_x -= v2.m_x;
        v1.m_y -= v2.m_y;

        return v1;
    }

    Vector2D operator/(float scalar)
    {
        return Vector2D(m_x / scalar, m_y / scalar);
    }

    Vector2D& operator/=(float scalar)
    {
        m_x /= scalar;
        m_y /= scalar;

        return *this;
    }

    // set length equal to one, we can use this to find direction of a vector
    void noramalise()
    {
        float l = length();
        if(l > 0)
        {
            (*this) *= 1 / l;
        }
    }

    float length() {return sqrt(m_x * m_x + m_y * m_y);}

    float getX() {return m_x;}
    float getY() {return m_y;}

    void setX(float x) {m_x = x;}
    void setY(float y) {m_y = y;}




private:
    float m_x;
    float m_y;

};


#endif //HELLOSDL_VECTOR2D_H
