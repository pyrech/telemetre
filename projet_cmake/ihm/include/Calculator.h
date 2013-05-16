#ifndef CALCULATOR_H_
#define CALCULATOR_H_
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <QtGui>
#include <QtCore/QList>
#include "MainWindow.h"

typedef double float64;

class Calculator {

private:
	MainWindow *parent;
    QString distWithUnit(double dist, short precision, QString unit);
	void detectPic(float64* data, int &start, int &end);
	float64 maxValue(float64* data);
	void log(QString msg);

public:
	Calculator(MainWindow *_parent);
	int getPixel(float64* data);
	QString getDist(int pixel);
	QString distToStr(double dist);
	int round(double d);
};

#endif 