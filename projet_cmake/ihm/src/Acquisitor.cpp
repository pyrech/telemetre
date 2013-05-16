#include "Acquisitor.h"

#ifdef WIN32
//Acquisitor* acquisitor_instance = NULL;

Acquisitor::Acquisitor(MainWindow *_parent)
: parent(_parent)
{
	//acquisitor_instance = this;
}

void Acquisitor::cleanup() {
	if (taskHandle!=0) {
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(taskHandle);
		DAQmxClearTask(taskHandle);
		taskHandle = 0;
	}
}

void Acquisitor::init(QString device) {
	int32       error=0;
	char        errBuff[2048]={'\0'};

	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
	DAQmxErrChk (DAQmxCreateTask("", &taskHandle));
	DAQmxErrChk (DAQmxCreateAIVoltageChan(taskHandle, QString(device+ACQ_CANAL_SIGNAL).toStdString().c_str(), "", DAQmx_Val_RSE, -10.0, 10.0, DAQmx_Val_Volts, NULL));
	DAQmxErrChk (DAQmxCfgSampClkTiming(taskHandle, "", 7000, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, NB_PIXEL));
	
	//DAQmxErrChk (DAQmxRegisterEveryNSamplesEvent(taskHandle, DAQmx_Val_Acquired_Into_Buffer, ACQ_CALLBACK_EVERY_N_SAMPLE, 0, everyNCallback, NULL));
	//DAQmxErrChk (DAQmxRegisterDoneEvent(taskHandle, 0, doneCallback, NULL));

	//DAQmxCfgDigEdgeStartTrig(taskHandle, ACQ_CANAL_TRIGGER, startEdge);  

	/*********************************************/
	// DAQmx Start Code
	/*********************************************/

Error:
	if( DAQmxFailed(error) )
		DAQmxGetExtendedErrorInfo(errBuff, 2048);

	//this->cleanup();
	
	if( DAQmxFailed(error) ) {
		QString str = "DAQmx Error: %1";
		str = str.arg(errBuff);
		this->log(str);
	}
	return;
}

void Acquisitor::log(QString msg) {
	//this->parent->log("[Acquisitor] "+msg);
}

void Acquisitor::trigger() {
	int32       error=0;
	char        errBuff[2048]={'\0'};
	static int  totalRead=0;
	int32       read=0;
	float64     data[NB_PIXEL];

	/*********************************************/
	// DAQmx Read Code
	/*********************************************/
	//DAQmx_Val_GroupByChannel ou DAQmx_Val_GroupByScanNumber
	DAQmxErrChk (DAQmxStartTask(taskHandle));
	DAQmxErrChk (DAQmxReadAnalogF64(taskHandle, NB_PIXEL, 10.0, DAQmx_Val_GroupByChannel, data, NB_PIXEL, &read, NULL));
	DAQmxStopTask(taskHandle);
	
	if(read > 0) {
		#ifdef VERBOSE
		this->log("receive "+QString::number(read)+" samples");
		//this->log("total samples received: "+QString::number(totalRead+=read));
		#endif
		this->parent->receiveData(data, read);
	}

Error:
	if( DAQmxFailed(error) ) {
		DAQmxGetExtendedErrorInfo(errBuff,2048);
		this->cleanup();
		QString str = "DAQmx Error: %1";
		str = str.arg(errBuff);
		this->log(str);
	}
}
/*
int32 CVICALLBACK doneCallback(TaskHandle taskHandle, int32 status, void *callbackData) {
	int32   error=0;
	char    errBuff[2048]={'\0'};

	// Check to see if an error stopped the task.
	DAQmxErrChk (status);

Error:
	if( DAQmxFailed(error) ) {
		acquisitor_instance->cleanup();
		QString str = "DAQmx Error: %1";
		str = str.arg(errBuff);
		acquisitor_instance->log(str);
	}
	return 0;
}*/

#endif