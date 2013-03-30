#ifndef ACQUISITOR_H_
#define ACQUISITOR_H_
#include <string>
#include <iostream>
#include <QtGui>
#include <QtCore/QList>
#include "MainWindow.h"

typedef double float64;

class Acquisitor : public QObject {

private:
	MainWindow *parent;

public:
	Acquisitor(MainWindow *_parent);
};

#endif 