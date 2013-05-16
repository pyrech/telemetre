#include <QApplication>
#include "MainWindow.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <boost/asio/serial_port.hpp> 
#include <boost/asio.hpp> 
#include <pthread.h>
#include <ctime>
#include "SimpleSerial.h"

using namespace boost;
using namespace std;


//MainWindow * telemetreWindow
static void * start_serial_communication(void *p_data){

    //SimpleSerial serial("/dev/cu.usbserial-FTFO53KG",9200);
    while(1){


        cout<<"ok"<<endl;
        usleep(1000);

       /* try {

            telemetreWindow->receivePixel(atoi(serial.readLine().c_str()));
            cout<<serial.readLine()<<endl;
        }
        catch(boost::system::system_error& e)
        {
            cout<<"Error: "<<e.what()<<endl;
        }*/
    }
}


int main(int argc, char *argv[]){

	QApplication app(argc, argv);				

	MainWindow *telemetreWindow = new MainWindow;
	//execute the application



    pthread_t thSerialCom;
    pthread_create (&thSerialCom, NULL, start_serial_communication, NULL);

	return app.exec();	
}
