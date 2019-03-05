#include "autodiftest.h"

float sqr(float a)
{
    return a*a;
}

AutoDifTest::AutoDifTest()
{

}

void AutoDifTest::Test01()
{
    QVERIFY(qFuzzyCompare(sqr(2.0f), 4.0f));
    QVERIFY(qFuzzyCompare(fz(Variable<float>(30, 1), Variable<float>(0, 0), Variable<float>(0, 0), Variable<float>(0, 0),
               Variable<float>(50, 0), Variable<float>(50, 0), Variable<float>(30, 0), Variable<float>(0, 0)).value, 2900.0f));
    qDebug() <<  fz(Variable<float>(30, 1), Variable<float>(0, 0), Variable<float>(0, 0), Variable<float>(0, 0),
                                  Variable<float>(50, 0), Variable<float>(50, 0), Variable<float>(30, 0), Variable<float>(0, 0)).derivative;
    QVERIFY(qFuzzyCompare(fz(Variable<float>(30, 1), Variable<float>(0, 0), Variable<float>(0, 0), Variable<float>(0, 0),
                Variable<float>(50, 0), Variable<float>(50, 0), Variable<float>(30, 0), Variable<float>(0, 0)).derivative, -60));
}
