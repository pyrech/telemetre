#include <QApplication>
#include "MainWindow.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>


using namespace std;

int main(int argc, char *argv[]){

	QApplication app(argc, argv);				

	MainWindow *telemetreWindow = new MainWindow;

	//execute the application
	return app.exec();	

}
