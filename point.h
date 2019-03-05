#ifndef POINT_H
#define POINT_H
#include <variable.h>
#include <iostream>
#include <QVector>

//#define NO 0
//#define X 1
//#define Y 2

class Point
{
public:
    Variable<float> x;
    Variable<float> y;
    Point(const float _x, const float _y):x(_x, 0),  y(_y, 0){}
    Point(const Variable<float> _x, const Variable<float> _y):x(_x.value, _x.derivative),  y(_y.value, _y.derivative){}
    static Variable<float> sqr(Point p)
    {
        return p.x * p.x + p.y * p.y;
    }
    void setDif(int i)
    {
        switch (i)
        {
            case 0:
                this->x.derivative = 0;
                this->y.derivative = 0;
                break;
            case 1:
                this->x.derivative = 1;
                this->y.derivative = 0;
                break;
            case 2:
                this->y.derivative = 1;
                this->x.derivative = 0;
                break;
            default:{}
        }
    }
    void Correct(QVector<float> grad, float step)
    {
        x.value -= grad[0] * step;
        y.value -= grad[1] * step;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p)
    {
        os << "|x: " << p.x.value << " |y: " << p.y.value << " ";
        return os;
    }
};

inline
Point operator+(Point a, Point b)
{
    return Point(a.x + b.x, a.y + b.y);
}


inline
Point operator-(Point a, Point b)
{
    return Point(a.x - b.x, a.y - b.y);
}


#endif // POINT_H
