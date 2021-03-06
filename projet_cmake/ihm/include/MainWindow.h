#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QTime>
#include <QtCore/QList>
#include <QDoubleValidator>
#include <iostream>
#include "Plotter.h"


#define PLOTTER_CURVE_ID 0
#define MAX_PIXEL 2048
#define MODE_CONTROLLER 1
#define MODE_ACQUISITION 2
#define FOCUS_UNIT 0.001
#define GAP_UNIT 0.001
#define PIXEL_UNIT 0.000001
#define MIN_PIC_VALUE 1
#define THRESHOLD_PIC_PERCENT 10
#define VERBOSE

typedef double float64;
//#include "qextserialenumerator.h"

class Calculator;
class Acquisitor;

class MainWindow : public QWidget {
	Q_OBJECT

private:
	QLineEdit *conf_edit_focus;
	QLineEdit *conf_edit_gap;
	QLineEdit *conf_edit_pixel;
	QList<QString> ports_found;
    //QList<QextPortInfo> ports
	QComboBox *ctrl_ports;
	QLineEdit *ctrl_edit_pixel;
	QLineEdit *acq_edit_distance;
	QLineEdit *ctrl_edit_distance;
	QTextEdit *log_edit;
	Plotter *plotter;
	Calculator *calculator;
	Acquisitor *acquisitor;
	QVector<QPointF> acq_data;

    void updatePortController(QString &text);
	void drawPlotter();
	void updateDistance(int mode, QString dist);

public:
	MainWindow();
    ~MainWindow();
	void searchPorts();
	void receiveData(float64* data);
	void receivePixel(int pixel);
	float getAxesGap();
	float getPixelWidth();
	float getLensFocus();
	void log(QString str);
	
public slots:
	void selectedControllerPort(int selected);

};

#endif 