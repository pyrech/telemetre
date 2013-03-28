#include "MainWindow.h"


MainWindow::MainWindow() {

	// create a window  
	this->setWindowTitle("PolyTelemetre");
	this->resize(800,400);

	/*
	caseCheckBox = new QCheckBox(tr("Match &case"));
	backwardCheckBox = new QCheckBox(tr("Search &backward"));
	findButton = new QPushButton(tr("&Find"));
	findButton->setDefault(true);
	findButton->setEnabled(false);
	closeButton = new QPushButton(tr("Close"));
	*/

	// Acquisition - ports
	acq_label_port = new QLabel(tr("Port :"));
	acq_ports = new QComboBox(this);
	acq_label_port->setBuddy(acq_ports);
	
	// Acquisition - Top layout (ports)
	QHBoxLayout *acq_top_port_layout = new QHBoxLayout;
	acq_top_port_layout->addWidget(acq_label_port);
	acq_top_port_layout->addWidget(acq_ports);

	// Acquisition - distance
	acq_label_distance = new QLabel(tr("Distance :"));
	acq_edit_distance = new QLineEdit;
	acq_edit_distance->setReadOnly(true);
	acq_label_distance->setBuddy(acq_edit_distance);
	
	// Acquisition - Top layout (distance)
	QHBoxLayout *acq_top_dist_layout = new QHBoxLayout;
	acq_top_dist_layout->addWidget(acq_label_distance);
	acq_top_dist_layout->addWidget(acq_edit_distance);

	// Acquisition - Plotter
	plotter = new Plotter;
	plotter->setPlotSettings(PlotSettings(1,NUMBER_SAMPLE,-2,2));

	// Acquisition - Layout (ports, distance, plotter)
	QVBoxLayout *acq_layout = new QVBoxLayout;
    acq_layout->setAlignment(Qt::AlignTop);
	acq_layout->addLayout(acq_top_port_layout);
	acq_layout->addLayout(acq_top_dist_layout);
	acq_layout->addStretch();
	acq_layout->addWidget(plotter);
	
	// Acquistion - Group box
	QGroupBox *acq_group_box = new QGroupBox(tr("Carte d'acquisition"));
	acq_group_box->setLayout(acq_layout);

	// Direct - ports
	dir_label_port = new QLabel(tr("Port :"));
	dir_ports = new QComboBox(this);
	dir_label_port->setBuddy(dir_ports);
	
	// Direct - Top layout (ports)
	QHBoxLayout *dir_top_port_layout = new QHBoxLayout;
	dir_top_port_layout->addWidget(dir_label_port);
	dir_top_port_layout->addWidget(dir_ports);

	// Direct - distance
	dir_label_distance = new QLabel(tr("Distance :"));
	dir_edit_distance = new QLineEdit;
	dir_edit_distance->setReadOnly(true);
	dir_label_distance->setBuddy(dir_edit_distance);

	// Direct - Top layout (distance)
	QHBoxLayout *dir_top_dist_layout = new QHBoxLayout;
	dir_top_dist_layout->addWidget(dir_label_distance);
	dir_top_dist_layout->addWidget(dir_edit_distance);

	// Direct - Layout (ports, distance)
	QVBoxLayout *dir_layout = new QVBoxLayout;
    dir_layout->setAlignment(Qt::AlignTop);
	dir_layout->addLayout(dir_top_port_layout);
	dir_layout->addLayout(dir_top_dist_layout);
	
	// Direct - Group box
	QGroupBox *dir_group_box = new QGroupBox(tr("Microcontroleur"));
	dir_group_box->setLayout(dir_layout);

	// Main layout (acquisition and direct)
	QHBoxLayout *main_layout = new QHBoxLayout;
	main_layout->addWidget(acq_group_box);
	main_layout->addWidget(dir_group_box);
	this->setLayout(main_layout);

	this->searchPorts();
	QString default_port = "";
	this->updatePortAcq(default_port);
	this->updatePortDir(default_port);

	QObject::connect(acq_ports, SIGNAL(currentIndexChanged(int)), this, SLOT(selectedAcqPort(int)));
	QObject::connect(dir_ports, SIGNAL(currentIndexChanged(int)), this, SLOT(selectedDirPort(int)));

	/*test*/
	float64 data[1000];
	for (int i=0; i<NUMBER_SAMPLE; i+=1)
	data[i] = sin(2*M_PI*10*i/NUMBER_SAMPLE);
	this->receiveData(data);
	this->receivePixel(50);
	
	// Show the window
	this->show();
}

void MainWindow::searchPorts() {
	ports_found.append("USB1");
	ports_found.append("USB2");
	ports_found.append("USB3");
	ports_found.append("USB4");
	ports_found.append("CD");
	//ports_found = QextSerialEnumerator::getPorts();
}

void MainWindow::updatePortAcq(QString &text) {
	this->fillPort(acq_ports, dir_ports);
}

void MainWindow::updatePortDir(QString &text) {
	this->fillPort(dir_ports, acq_ports);
}

void MainWindow::fillPort(QComboBox *cur_port, QComboBox *other_port) {
	QString port_selected = other_port->currentText();
	cur_port->clear();
	cur_port->addItem("");
    foreach (QString port, ports_found) {
		if (port_selected != port) {
			cur_port->addItem(port);
		}
	}
    /*std::cout << "List of ports:";
    foreach (QextPortInfo info, ports_found) {
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

void MainWindow::selectedAcqPort(int selected) {
	QString dir_port_selected = dir_ports->currentText();
	if (selected == 0) {
		// disabled some fields ?
	}
	this->updatePortDir(dir_port_selected);
}
void MainWindow::selectedDirPort(int selected) {
	QString acq_port_selected = acq_ports->currentText();
	if (selected == 0) {
		// disabled some fields ?
	}
	this->updatePortAcq(acq_port_selected);
}

void MainWindow::drawPlotter() {
  plotter->setCurveData(PLOTTER_CURVE_ID, acq_data);
}

void MainWindow::updateDistance(int mode, QString dist) {
	switch(mode) {
		case MODE_ACQUISITION: {
			this->acq_edit_distance->setText(dist);
			break;
		}
		case MODE_DIRECT: {
			this->dir_edit_distance->setText(dist);
			break;
		}
	}
}

void MainWindow::receiveData(float64* data) {
  acq_data.erase(acq_data.begin(), acq_data.end());
  plotter->clearCurve(PLOTTER_CURVE_ID);
  for (int i=0; i<NUMBER_SAMPLE; i+=1) {
    acq_data.append(QPointF(i, data[i]));
  }
  this->drawPlotter();
  int pixel = 500;
  QString dist = "10 m";
  // pixel = this->calculator->getPixel(acq_data);
  // dist = this->calculator->getDist(pixel);
  this->updateDistance(MODE_ACQUISITION, dist);
}

void MainWindow::receivePixel(int pixel) {
  QString dist = "15 m";
  //dist = this->calculator->getDist(pixel);
  this->updateDistance(MODE_DIRECT, dist);
}