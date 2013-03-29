#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QtCore/QList>
#include <QDoubleValidator>
#include <iostream>
#include "Plotter.h"


#define PLOTTER_CURVE_ID 0
#define MAX_PIXEL 2048
#define MODE_DIRECT 1
#define MODE_ACQUISITION 2
#define FOCUS_UNIT 0.001
#define GAP_UNIT 0.001
#define PIXEL_UNIT 0.000001
#define MIN_PIC_VALUE 1
#define THRESHOLD_PIC_PERCENT 10

typedef double float64;
//#include "qextserialenumerator.h"

class Calculator;

class MainWindow : public QWidget {
	Q_OBJECT

private:
	QLineEdit *conf_edit_focus;
	QLineEdit *conf_edit_gap;
	QLineEdit *conf_edit_pixel;
	QList<QString> ports_found;
    //QList<QextPortInfo> ports
	QComboBox *acq_ports;
	QComboBox *dir_ports;
	QLineEdit *acq_edit_distance;
	QLineEdit *dir_edit_distance;
	Plotter *plotter;
	Calculator *calculator;
	QVector<QPointF> acq_data;

    void updatePortAcq(QString &text);
    void updatePortDir(QString &text);
    void fillPort(QComboBox *cur_port, QComboBox *other_port);
	void drawPlotter();
	void updateDistance(int mode, QString dist);

public:
	MainWindow();
    ~MainWindow();
	void searchPorts();
	void receiveData(float64* data);
	void receivePixel(int pixel);
	
public slots:
	void selectedAcqPort(int selected);
	void selectedDirPort(int selected);
	float getAxesGap();
	float getPixelWidth();
	float getLensFocus();

};

#endif 