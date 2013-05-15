#ifndef ACQUISITOR_H_
#define ACQUISITOR_H_
#include <string>
#include <iostream>
#include <QtGui>
#include <QtCore/QList>
#include "MainWindow.h"

#ifdef WIN32
#include <stdio.h>
#include <NIDAQmx.h>
#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else
#endif

#define ACQ_CALLBACK_EVERY_N_SAMPLE 50
#define ACQ_DEVICE "Dev3"
#define ACQ_CANAL_SIGNAL ACQ_DEVICE "/ai0"
#define ACQ_CANAL_TRIGGER ACQ_DEVICE "/ai5"

typedef double float64;

class Acquisitor : public QObject {

private:
	TaskHandle taskHandle;
	MainWindow *parent;
	void trigger();
	friend int32 CVICALLBACK everyNCallback(TaskHandle taskHandle, int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData);
	friend int32 CVICALLBACK doneCallback(TaskHandle taskHandle, int32 status, void *callbackData);

public:
	Acquisitor(MainWindow *_parent);
	void init();
	void cleanup();
	void log(QString msg);
};

int32 CVICALLBACK everyNCallback(TaskHandle taskHandle, int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData);
int32 CVICALLBACK doneCallback(TaskHandle taskHandle, int32 status, void *callbackData);

#endif 