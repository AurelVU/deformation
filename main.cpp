//#include <QCoreApplication>

#include <iostream>
#include <map>
#include <QVector>
#include <variable.h>
#include <test1.h>
#include <Eigen/Core>
#include <Eigen/LU>
#include <autodiftest.h>

using namespace std;
using namespace Eigen;


typedef Variable<Variable<float>> Variable2;
typedef Variable<float> Variablef;

void PrintVariable2(Variable2 var)
{
    cout << var.value.value << ' ' << var.value.derivative << ' ' << var.derivative.value << ' ' << var.derivative.derivative << endl;
}

/*
template <typename T>
Variable<T> fz(Variable<T> x, Variable<T> y)
{
    return x*x*y + y*y*x;

}*/



/*
template <typename T>
Variable<T> fz(Variable<T> x1, Variable<T> y1, Variable<T> x2, Variable<T> y2, Variable<T> x3, Variable<T> y3, Variable<T> x4, Variable<T> y4)
{
    Variable<T> l1 = (x3-x1)*(x3-x1) + (y3-y1)*(y3-y1);
    Variable<T> currentLength = ((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    Variable<T> dl = (currentLength-((x2-x4)*(x2-x4) + (y2-y4)*(y2-y4)));
    return  l1 + dl*dl;
}

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

    v[0] = fz(_x, _y, x2, y2, x3, y3, x4, y4).derivative;
    _x = Variablef(p1.x.value, 0);
    _y = Variablef(p1.y.value, 1);
    v[1] = fz(_x, _y, x2, y2, x3, y3, x4, y4).derivative;
    return v;
}
*/

void Correct(Point A, Point B, Point T)
{
    const Point C(A.x, A.y);
    //Vector2f dt = -ComputeHeissan(A, B, T, C).inverse() * Vect(A, B, T, C);
    auto H = ComputeHeissan(A, B, T, C);
    auto V = Vect(A, B, T, C);
    Vector2f dt = -H.inverse() * V;
    //dt = -Vect(A, B, T, Point(A.x.value, A.y.value));
    //float step = 1e-4;
    float step = 1;
    cout << A << ' ' << B << ' ' << T << endl;
    while((abs(dt[0]) + abs(dt[1])) > 0.1)
    {
        A.x.value += step * dt[0];
        A.y.value += step * dt[1];
       // dt = -Vect(A, B, T, Point(A.x.value, A.y.value));
        //dt = -ComputeHeissan(A, B, T, C).inverse() * Vect(A, B, T, C);
        H = ComputeHeissan(A, B, T, C);
        V = Vect(A, B, T, C);
        dt = -H.inverse() * V;

        cout << A << ' ' << B << ' ' << T << endl;
    }
    cout << dt[0] << ' ' << dt[1] << endl;
    cout << V[0] << ' ' << V[1] << endl;
    cout << A << ' ' << B << ' ' << T << endl;
}


int main()
{
    AutoDifTest ADTest;
    QTest::qExec(&ADTest);
    Point A(30, 0);
    Point B(0, 0);
    Point T(50, 50);
    Correct(A, B, T);
}





/*int main()
{
   // Test();
    Variable<Variable<float>> x(Variable<float>(5, 1), Variable<float>(1, 0));
    Variable<Variable<float>> y = x*x*x;
    cout << y.value.value << ' ' << y.value.derivative << ' ' << y.derivative.value << ' ' << y.derivative.derivative << ' ';*/
    /*Variable<Variable<float>> x(Variable<float>(5, 1), Variable<float>(1, 0));
    Variable<Variable<float>> y(Variable<float>(6, 0), Variable<float>(0, 0));
    Variable<Variable<float>> z = fz(x, y);
    PrintVariable2(z);
    x = Variable<Variable<float>>(Variable<float>(5, 1), Variable<float>(0, 0));
    y = Variable<Variable<float>>(Variable<float>(6, 0), Variable<float>(1, 0));
    z = fz(x, y);
    PrintVariable2(z);
    x = Variable<Variable<float>>(Variable<float>(5, 0), Variable<float>(1, 0));
    y = Variable<Variable<float>>(Variable<float>(6, 1), Variable<float>(0, 0));
    z = fz(x, y);
    PrintVariable2(z);
    x = Variable<Variable<float>>(Variable<float>(5, 0), Variable<float>(0, 0));
    y = Variable<Variable<float>>(Variable<float>(6, 1), Variable<float>(1, 0));
    z = fz(x, y);
    PrintVariable2(z);
}

*/
