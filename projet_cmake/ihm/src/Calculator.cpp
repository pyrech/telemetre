#include "Calculator.h"


Calculator::Calculator(MainWindow *_parent)
: parent(_parent)
{
}

int Calculator::getPixel(float64* data) {
	int start, end;
	// Detect start and end pixel of the pic
	detectPic(data, start, end);
	return round((start+end)/2); // The central pixel is the one we want
}

void Calculator::detectPic(float64* data, int &start, int &end) {
	start = 0;
	end = 0;
	float64 min = 10;
	int pixel = 0;
	for(int i=0; i<NB_PIXEL; i++) {
		if (data[i] < min) {
			min = data[i];
			pixel = i;
		}
	}
	start = pixel;
	end = pixel;
	return;
	// No longer use the pic center
	float64 min_signal = minValue(data);
	// If max is not high enough, there must be not relevant pic to detect
	if (min_signal < MIN_PIC_VALUE) {
		log("Pic not enough low ("+QString::number(min_signal)+")");
		return;
	}
	// Threshold which determinate where the pic starts and ends
	float64 threshold = min_signal*(100-THRESHOLD_PIC_PERCENT)/100;
	for(int i=0; i<(NB_PIXEL-1); i++) {
		// Search for start if we haven't find it yet
		if (start == 0 && end == 0 && data[i] < threshold) {
			start = i+1;
		}
		// Search for end if start found and end not yet found
		if (start != 0 && end == 0 && data[i+1] > threshold) {
			end = i+1;
		}
		// If another pics, we can't know which is right
		if (start != 0 && end != 0 && data[i+1] < threshold) {
			start = 0;
			end = 0;
			log("Many pics");
			return;
		}
	}
}

float64 Calculator::minValue(float64* data) {
	float64 min = 10;
	for(int i=0; i<NB_PIXEL; i++) {
		if (data[i] < min) {
			min = data[i];
		}
	}
	return min;
}

int Calculator::round(double d) {
  return (int)floor(d + 0.5);
}

QString Calculator::getDist(int pixel) {
	if (pixel < 1 || pixel > NB_PIXEL) {
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

void Calculator::log(QString msg) {
	this->parent->log("[Calculator] "+msg);
}