#ifndef CALCULATOR_H_
#define CALCULATOR_H_
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <iostream>
#include <QtGui>
#include <QtCore/QList>
#include "MainWindow.h"

typedef double float64;

class Calculator {

private:
	MainWindow *parent;
    QString distWithUnit(double dist, QString unit);

public:
	Calculator(MainWindow *_parent);
	int getPixel(QVector<QPointF> data);
	QString getDist(int pixel);
	QString distToStr(double dist);

};

#endif 