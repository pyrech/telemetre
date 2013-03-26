#include "MainWindow.h"


MainWindow::MainWindow(){

	// create a window  
	this->setWindowTitle("PolyTelemetre");
	this->resize(1000,700);
	
	//layout the widgets
	QVBoxLayout *layout = new QVBoxLayout;
	plotter = new Plotter;	
	labelDistance = new QLabel("Distance");

	listePorts = new QComboBox(this);
	listePorts->addItem("USB1");
	listePorts->addItem("USB2");
	listePorts->addItem("USB3");
	listePorts->addItem("CD");
	
	//create the plotter and its data
	
	plotter->setPlotSettings(PlotSettings(0,20,-2,2));		
	
	for (float i=0;i<20;i+=0.1)
		data1.append(QPointF(i,sin(i)));

	plotter->setCurveData(0,data1);												
	
	//layout the widgets
	
	layout->addWidget(listePorts);
	layout->addWidget(plotter);
	layout->addWidget(labelDistance);
	this->setLayout(layout);
	//show the window
	this->show();
}


void MainWindow::DisplayPort(){


	/*$QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    //! [1]
    std::cout << "List of ports:";
    //! [2]
    foreach (QextPortInfo info, ports) {
        std::cout << "port name:"       << info.portName.toStdString();
        std::cout << "friendly name:"   << info.friendName.toStdString();
        std::cout << "physical name:"   << info.physName.toStdString();
        std::cout << "enumerator name:" << info.enumName.toStdString();
        std::cout << "vendor ID:"       << info.vendorID;
        std::cout << "product ID:"      << info.productID;

        std::cout << "==================================="<<std::endl;
    }
    */
}