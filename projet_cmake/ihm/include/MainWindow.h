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
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <boost/asio/serial_port.hpp> 
#include <boost/asio.hpp> 
#include <pthread.h>
#include <ctime>
#include "SimpleSerial.h"
#include "Tools.h"
#include "Plotter.h"

#define PLOTTER_CURVE_ID 0
#define NB_PIXEL 2048
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
#include <boost/asio.hpp>


#ifdef WIN32
	//#include <stdio.h>
	#include <windows.h>
	//#include <string.h>
#endif

class Calculator;
class Acquisitor;

class MainWindow : public QWidget {
	Q_OBJECT

private:
	QLineEdit *conf_edit_focus;
	QLineEdit *conf_edit_gap;
	QLineEdit *conf_edit_pixel;
	QList<QString> ports_found;
	QComboBox *ctrl_ports;
	QComboBox *acq_devices;
	QLineEdit *ctrl_edit_pixel;
	QLineEdit *acq_edit_distance;
	QLineEdit *ctrl_edit_distance;
	QTextEdit *log_edit;
	Plotter *plotter;
	Calculator *calculator;
	Acquisitor *acquisitor;
	QVector<QPointF> acq_data;

	QTimer* timer;

    void updatePortController(QString &text);
	void updateDistance(int mode, QString dist);
	void * start_serial_communication();//void *arguments

    static void *start_serial_communication_helper(void *context)
    {
        return ((MainWindow *)context)->start_serial_communication();
    }

public:
	MainWindow();
    ~MainWindow();
	void searchPorts();
	void receiveData(float64* data, int count);
	void receivePixel(int pixel);
	float getAxesGap();
	float getPixelWidth();
	float getLensFocus();
	void log(QString str);
	
public slots:
	void selectedControllerPort(int selected);
	void selectedAcquisitionDevice(int selected);
};

#endif 