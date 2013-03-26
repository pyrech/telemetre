#include "MainWindow.h"


MainWindow::MainWindow(){

	// create a window  
	this->setWindowTitle("PolyTelemetre");
	this->resize(500,500);
	
	//layout the widgets
	QVBoxLayout *layout = new QVBoxLayout;

	listePorts = new QComboBox(this);
	listePorts->addItem("Paris");
	listePorts->addItem("Londres");
	listePorts->addItem("Singapour");
	listePorts->addItem("Tokyo");
	
	//create the plotter and its data
	Plotter *plotter = new Plotter;	
	plotter->setPlotSettings(PlotSettings(0,20,-2,2));		
	
	QVector<QPointF> data1;
	for (float i=0;i<20;i+=0.1)
		data1.append(QPointF(i,sin(i)));
	QVector<QPointF> data2;
	for (float i=0;i<20;i+=0.1)
		data2.append(QPointF(i,sin(i/2)));
	
	plotter->setCurveData(0,data1);							
	plotter->setCurveData(1,data2);							
	
	//layout the widgets
	layout->addWidget (plotter);
	layout->addWidget(listePorts);
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