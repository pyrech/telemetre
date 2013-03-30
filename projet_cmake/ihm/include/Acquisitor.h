#ifndef ACQUISITOR_H_
#define ACQUISITOR_H_
#include <string>
#include <iostream>
#include <QtGui>
#include <QtCore/QList>
#include "MainWindow.h"

#include <stdio.h>
#include <NIDAQmx.h>

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

#define CANAL_SIGNAL "Dev1/ai0"
#define CANAL_TRIGGER "Dev1/ai5"

typedef double float64;

class Acquisitor : public QObject {

private:
	MainWindow *parent;
	void process();

public:
	Acquisitor(MainWindow *_parent);
};

#endif 