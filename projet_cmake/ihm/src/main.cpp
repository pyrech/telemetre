#include <QApplication>
#include "MainWindow.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <boost/asio/serial_port.hpp> 
#include <boost/asio.hpp> 


using namespace boost;
using namespace std;


int main(int argc, char *argv[]){

	QApplication app(argc, argv);				

	MainWindow *telemetreWindow = new MainWindow;
	//execute the application

	return app.exec();	
}
