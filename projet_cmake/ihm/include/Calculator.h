#ifndef CALCULATOR_H_
#define CALCULATOR_H_
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <iostream>
#include <QtGui>
#include <QtCore/QList>

typedef double float64;

class Calculator {

private: 

public:

  Calculator();
  int getPixel(QVector<QPointF> data);
  QString getDist(int pixel);

};

#endif 