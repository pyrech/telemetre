#include <QApplication>
#include "MainWindow.h"


int main(int argc, char *argv[]){

	QApplication app(argc, argv);				

	MainWindow *telemetreWindow = new MainWindow;

	//execute the application
	return app.exec();	
	
}
