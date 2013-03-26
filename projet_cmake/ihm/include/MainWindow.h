#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_
#include <string>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QtCore/QList>
#include <iostream>
#include "Plotter.h"
#include "math.h"

//#include "qextserialenumerator.h"

class MainWindow : public QWidget{

private: 

	QComboBox *listePorts;

public:


	MainWindow();
	void DisplayPort();



};

#endif 