#ifndef TEST1_H
#define TEST1_H
#include <variable.h>
#include <point.h>
#include <iostream>

using namespace std;
Variable<float> computeError(Point& P1, Point& P2, Point& P1_o, Point& P2_o, Point& T)
{
    const auto diff = T - P2;
    Variable<float> dN = Point::sqr(diff);
    Variable<float> dP = Point::sqr(P2 - P1 - (P2_o - P1_o));
    Variable<float> E = dN + dP;

    return E;
}

double dE(Variable<float>& E, Point& P1, Point& P2, Point& P1_o, Point& P2_o, Point& T, QVector<QVector<float>>& _grad)
{
//    QVector<QVector<float>> grad;
//    Variable<float> dN(0, 0);
//    Variable<float> dP(0, 0);

//    QVector<float> p1;
//    P1.setDif(X);
//    P2.setDif(NO);
//    E = computeError(P1, P2, P1_o, P2_o, T);
//    p1.append(E.derivative);

//    P1.setDif(Y);
//    P2.setDif(NO);
//    E = computeError(P1, P2, P1_o, P2_o, T);
//    p1.append(E.derivative);

//    QVector<float> p2;
//    P1.setDif(NO);
//    P2.setDif(X);
//    E = computeError(P1, P2, P1_o, P2_o, T);
//    p2.append(E.derivative);

//    P1.setDif(NO);
//    P2.setDif(Y);
//    E = computeError(P1, P2, P1_o, P2_o, T);
//    p2.append(E.derivative);

//    grad.append(p1);
//    grad.append(p2);
//    //grad.append(E.derivative);

//    //P1.derivative = 0;
//    //P2.derivative = 1;
//    //E = computeError(P1, P2, P1_o, P2_o, T);
//    //grad.append(E.derivative);

//    _grad = grad;
//    return E.value;
}


int Test()
{
//    Point T(50, 50);
//    T.setDif(NO);
//    Point P1(30, 0);
//    P1.setDif(X);
//    Point P2(0, 0);
//    P2.setDif(NO);
//    Point P1_o(30, 0);
//    P1_o.setDif(NO);
//    Point P2_o(0, 0);
//    P2_o.setDif(NO);
//    float step = 0.0001f;
//    double Err = 0;

//    Variable<float> E = Point::sqr(T - P2) + Point::sqr((P2 - P1) - (P2_o - P1_o));
//    Err = E.value;
//    QVector<QVector<float>> grad;
//    int i = 0;
//    while(Err > 0.01f && i < 100)
//    {
//        //++i;
//        //if (i > 100) step *= 10;
//        Err = dE(E, P1, P2, P1_o, P2_o, T, grad);
//        P1.Correct(grad[0], step);
//        P2.Correct(grad[1], step);
//        cout << E.value << ' ' << P1  << grad[0][0] << ' ' <<  grad[0][1] << ' ' << P2 << grad[1][0] << ' ' << grad[1][1] << endl;
//    }
}

#endif // TEST1_H
