#ifndef ERROR_FUNC_H
#define ERROR_FUNC_H
#include <QDebug>
#include <variable.h>
#include <Eigen/Core>
#include <Eigen/LU>
#include <point.h>
#include <iostream>

using namespace Eigen;

typedef Variable<Variable<float>> Variable2;
typedef Variable<float> Variablef;

template <typename T>
QString variableToString(const Variable<T> &var);

template <>
inline QString variableToString<float>(const Variable<float> &var)
{
    return QString("(val=%1, der=%2)").arg(var.value).arg(var.derivative);
}

template <>
inline QString variableToString<Variable<float>>(const Variable<Variable<float>> &var)
{
    return QString("(val=%1, der=%2)").arg(variableToString(var.value)).arg(variableToString(var.derivative));
}

template <typename T>
Variable<T> fz(Variable<T> x1, Variable<T> y1, Variable<T> x2, Variable<T> y2, Variable<T> x3, Variable<T> y3, Variable<T> x4, Variable<T> y4)
{
    qDebug() << "x1: " << variableToString(x1);
    qDebug() << "y1: " << variableToString(y1);
    qDebug() << "x2: " << variableToString(x2);
    qDebug() << "y2: " << variableToString(y2);
    qDebug() << "x3: " << variableToString(x3);
    qDebug() << "y3: " << variableToString(y3);
    qDebug() << "x4: " << variableToString(x4);
    qDebug() << "y4: " << variableToString(y4);
    Variable<T> l1 = (x3-x1)*(x3-x1) + (y3-y1)*(y3-y1);
    qDebug() << "l1: " << variableToString(l1);
    //Variable<T> currentLength = ((x2-x1) + (y2-y1));
    //qDebug() << "currentLength: " << variableToString(currentLength);
    //Variable<T> dl = (currentLength-((x2-x4) + (y2-y4)));
    //qDebug() << "dl: " << variableToString(dl);
    Variable<T> dx = ((x2-x1) - (x2-x4));
    Variable<T> dy = ((y2-y1) - (y2-y4));
    return  l1 + dx*dx + dy*dy;;
}

inline
Matrix2f ComputeHeissan(Point p1, Point p2, Point p3, Point p4)
{
    float x = p1.x.value;
    float y = p1.y.value;

    Matrix2f h;
    Variable<Variable<float>> _x(Variable<float>(x, 1), Variable<float>(1, 0));
    Variable<Variable<float>> _y(Variable<float>(y, 0), Variable<float>(0, 0));

    Variable<Variable<float>> x2(Variable<float>(p2.x.value, 0), Variable<float>(0, 0));
    Variable<Variable<float>> y2(Variable<float>(p2.y.value, 0), Variable<float>(0, 0));
    Variable<Variable<float>> x3(Variable<float>(p3.x.value, 0), Variable<float>(0, 0));
    Variable<Variable<float>> y3(Variable<float>(p3.y.value, 0), Variable<float>(0, 0));
    Variable<Variable<float>> x4(Variable<float>(p4.x.value, 0), Variable<float>(0, 0));
    Variable<Variable<float>> y4(Variable<float>(p4.x.value, 0), Variable<float>(0, 0));


    /*
     * QVector<Variable<float>> vars()....
     * for(int varInd = 0; varInd < nVars; ++varInd){
     *     vars[varInd].derivative = 1;
     *     result = fz(vars);
     *     gradient[varInd] = result.derivative
     *
     * }
    */

    h(0, 0) = fz(_x, _y, x2, y2, x3, y3, x4, y4).derivative.derivative;
    _x = Variable2(Variable<float>(x, 1), Variable<float>(0, 0));
    _y = Variable2(Variable<float>(y, 0), Variable<float>(1, 0));
    h(1, 0) = fz(_x, _y, x2, y2, x3, y3, x4, y4).derivative.derivative;
    _x = Variable2(Variable<float>(x, 0), Variable<float>(1, 0));
    _y = Variable2(Variable<float>(y, 1), Variable<float>(0, 0));
    h(0, 1) = fz(_x, _y, x2, y2, x3, y3, x4, y4).derivative.derivative;
    _x = Variable2(Variable<float>(x, 0), Variable<float>(0, 0));
    _y = Variable2(Variable<float>(y, 1), Variable<float>(1, 0));
    h(1, 1) = fz(_x, _y, x2, y2, x3, y3, x4, y4).derivative.derivative;
    return h;
}

inline
Vector2f Vect(Point p1, Point p2, Point p3, Point p4)
{
    Vector2f v;
    Variablef _x = Variablef(p1.x.value, 1);
    Variablef _y = Variablef(p1.y.value, 0);

    Variablef x2 = Variablef(p2.x.value, 0);
    Variablef y2 = Variablef(p2.y.value, 0);
    Variablef x3 = Variablef(p3.x.value, 0);
    Variablef y3 = Variablef(p3.y.value, 0);
    Variablef x4 = Variablef(p4.x.value, 0);
    Variablef y4 = Variablef(p4.y.value, 0);
    std::cout << "ERROR " << fz(_x, _y, x2, y2, x3, y3, x4, y4).value;
    v[0] = fz(_x, _y, x2, y2, x3, y3, x4, y4).derivative;
    _x = Variablef(p1.x.value, 0);
    _y = Variablef(p1.y.value, 1);
    v[1] = fz(_x, _y, x2, y2, x3, y3, x4, y4).derivative;
    return v;
}


class error_func
{
public:
    error_func();
};

#endif // ERROR_FUNC_H
