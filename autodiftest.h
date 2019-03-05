#ifndef AUTODIFTEST_H
#define AUTODIFTEST_H

#include <QTest>
#include <error_func.h>
#include <variable.h>

class AutoDifTest : public QObject
{
    Q_OBJECT
public:
    AutoDifTest();
private slots:
    void Test01();
};

#endif // AUTODIFTEST_H
