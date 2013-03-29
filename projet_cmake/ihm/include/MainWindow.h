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
#include <iostream>
#include "Plotter.h"
#include "Calculator.h"

#define PLOTTER_CURVE_ID 0
#define NUMBER_SAMPLE 1000
#define MODE_DIRECT 1
#define MODE_ACQUISITION 2

typedef double float64;
//#include "qextserialenumerator.h"

class MainWindow : public QWidget {
	Q_OBJECT

private: 
	QLabel *acq_label_port;
	QLabel *dir_label_port;
	QList<QString> ports_found;
    //QList<QextPortInfo> ports
	QComboBox *acq_ports;
	QComboBox *dir_ports;
	QLabel *acq_label_distance;
	QLabel *dir_label_distance;
	QLineEdit *acq_edit_distance;
	QLineEdit *dir_edit_distance;
	Plotter *plotter;
	Calculator *calculator;
	QVector<QPointF> acq_data;

	void cleanPointer(void* pointer);
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



};

#endif 