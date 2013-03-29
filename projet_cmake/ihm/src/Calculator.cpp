#include "Calculator.h"


Calculator::Calculator(MainWindow *_parent)
: parent(_parent)
{
}

int Calculator::getPixel(QVector<QPointF> data) {
	return 0;
}

QString Calculator::getDist(int pixel) {
	if (pixel < 1 || pixel > MAX_PIXEL) {
		return "Invalid pixel ("+QString::number(pixel)+")";
	}
	double distance = 0;
	distance = (parent->getAxesGap()*parent->getLensFocus()) / (pixel*parent->getPixelWidth());
	return distToStr(distance);
}

QString Calculator::distToStr(double dist) {
	if (dist > 1) {
		return distWithUnit(dist, "m");
	}
	else if (dist > 0.01) {
		return distWithUnit(dist/100, "cm");
	}
	else {
		return distWithUnit(dist/1000, "mm");
	}
}

QString Calculator::distWithUnit(double dist, QString unit) {
	return QString::number(dist, 'g', DISTANCE_DECIMAL)+" "+unit;
}