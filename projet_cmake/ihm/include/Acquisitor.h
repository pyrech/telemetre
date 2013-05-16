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
#define ACQ_CANAL_SIGNAL "/ai0"
#define ACQ_CANAL_TRIGGER "/ai5"

typedef double float64;

class Acquisitor : public QObject {
	#ifdef WIN32
		private:
			TaskHandle taskHandle;
			MainWindow *parent;
			void trigger();
			friend int32 CVICALLBACK everyNCallback(TaskHandle taskHandle, int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData);
			friend int32 CVICALLBACK doneCallback(TaskHandle taskHandle, int32 status, void *callbackData);

		public:
			Acquisitor(MainWindow *_parent);
			void init(QString device);
			void cleanup();
			void log(QString msg);
	#endif
};

#ifdef WIN32
	int32 CVICALLBACK everyNCallback(TaskHandle taskHandle, int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData);
	int32 CVICALLBACK doneCallback(TaskHandle taskHandle, int32 status, void *callbackData);
#endif
#endif 