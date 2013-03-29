#include "Calculator.h"


Calculator::Calculator(MainWindow *_parent)
: parent(_parent)
{
}

int Calculator::getPixel(float64* data) {
	int start, end;
	detectPic(data, start, end);
	std::cout << start << ";" << end << std::endl;
	return round((start+end)/2);
}

void Calculator::detectPic(float64* data, int &start, int &end) {
	start = 0;
	end = 0;
	float64 threshold = max(data)*(100-THRESHOLD_PIC_PERCENT)/100;
	for(int i=0; i<MAX_PIXEL; i++) {
		if (start == 0 && data[i] > threshold) {
			start = i+1;
		}
		if (start != 0 && end == 0 && data[i+1] < threshold) {
			end = i+1;
		}
	}
}

float64 Calculator::max(float64* data) {
	float64 max = 0;
	for(int i=0; i<MAX_PIXEL; i++) {
		if (data[i] > max) {
			max = data[i];
		}
	}
	return max;
}

int Calculator::round(double d) {
  return (int)floor(d + 0.5);
}

QString Calculator::getDist(int pixel) {
	if (pixel < 1 || pixel > MAX_PIXEL) {
		return "Invalid pixel ("+QString::number(pixel)+")";
	}
	double distance = 0;
	distance = (parent->getAxesGap()*GAP_UNIT*parent->getLensFocus()*FOCUS_UNIT) / (pixel*parent->getPixelWidth()*PIXEL_UNIT);
	return distToStr(distance);
}

QString Calculator::distToStr(double dist) {
	if (dist > 10) {
		return distWithUnit(dist, 1, "m");
	}
	else if (dist > 1) {
		return distWithUnit(dist, 2, "m");
	}
	else if (dist > 0.01) {
		return distWithUnit(dist*100, 1, "cm");
	}
	else {
		return distWithUnit(dist*1000, 0, "mm");
	}
}

QString Calculator::distWithUnit(double dist, short precision, QString unit) {
	return QString::number(dist, 'f', precision)+" "+unit;
}