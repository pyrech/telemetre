#include "MainWindow.h"
#include "Calculator.h"
#include "Acquisitor.h"


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

	// Configuration - Focus
	QLabel *conf_label_focus = new QLabel(tr("Foyer (mm) :"));
	conf_edit_focus = new QLineEdit;
	conf_edit_focus->setFixedWidth(50);
	conf_edit_focus->setValidator(new QDoubleValidator(0, 100, 2, this));
	conf_edit_focus->setText("110");
	conf_label_focus->setBuddy(conf_edit_focus);
	
	// Configuration - Focus Layout
	QHBoxLayout *conf_focus_layout = new QHBoxLayout;
	conf_focus_layout->addWidget(conf_label_focus);
	conf_focus_layout->addWidget(conf_edit_focus);

	// Configuration - Gap
	QLabel *conf_label_gap= new QLabel(tr("Ecart axes (mm) :"));
	conf_edit_gap = new QLineEdit;
	conf_edit_gap->setFixedWidth(50);
	conf_edit_gap->setValidator(new QDoubleValidator(0, 100, 2, this));
	conf_edit_gap->setText("50");
	conf_label_gap->setBuddy(conf_edit_gap);
	
	// Configuration - Gap Layout
	QHBoxLayout *conf_gap_layout = new QHBoxLayout;
	conf_gap_layout->addWidget(conf_label_gap);
	conf_gap_layout->addWidget(conf_edit_gap);
	
	// Configuration - Pixel
	QLabel *conf_label_pixel = new QLabel(tr("Largeur pixel (µm) :"));
	conf_edit_pixel = new QLineEdit;
	conf_edit_pixel->setFixedWidth(50);
	conf_edit_pixel->setValidator(new QDoubleValidator(0, 100, 2, this));
	conf_edit_pixel->setText("14");
	conf_label_pixel->setBuddy(conf_edit_pixel);
	
	// Configuration - Pixel Layout
	QHBoxLayout *conf_pixel_layout = new QHBoxLayout;
	conf_pixel_layout->addWidget(conf_label_pixel);
	conf_pixel_layout->addWidget(conf_edit_pixel);

	// Configuration - Main layout
	QHBoxLayout *conf_layout = new QHBoxLayout;
	conf_layout->addLayout(conf_focus_layout);
	conf_layout->addLayout(conf_gap_layout);
	conf_layout->addLayout(conf_pixel_layout);
	
	// Configuration - Group box
	QGroupBox *conf_group_box = new QGroupBox(tr("Configuration"));
	conf_group_box->setLayout(conf_layout);

	// Acquisition - ports
	QLabel *acq_label_port = new QLabel(tr("Port :"));
	acq_ports = new QComboBox(this);
	acq_label_port->setBuddy(acq_ports);
	
	// Acquisition - Top layout (ports)
	QHBoxLayout *acq_top_port_layout = new QHBoxLayout;
	acq_top_port_layout->addWidget(acq_label_port);
	acq_top_port_layout->addWidget(acq_ports);

	// Acquisition - distance
	QLabel *acq_label_distance = new QLabel(tr("Distance :"));
	acq_edit_distance = new QLineEdit;
	acq_edit_distance->setReadOnly(true);
	acq_label_distance->setBuddy(acq_edit_distance);
	
	// Acquisition - Top layout (distance)
	QHBoxLayout *acq_top_dist_layout = new QHBoxLayout;
	acq_top_dist_layout->addWidget(acq_label_distance);
	acq_top_dist_layout->addWidget(acq_edit_distance);

	// Acquisition - Plotter
	plotter = new Plotter;
	plotter->setPlotSettings(PlotSettings(1,MAX_PIXEL,-2,2));

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
	QLabel *dir_label_port = new QLabel(tr("Port :"));
	dir_ports = new QComboBox(this);
	dir_label_port->setBuddy(dir_ports);
	
	// Direct - Top layout (ports)
	QHBoxLayout *dir_top_port_layout = new QHBoxLayout;
	dir_top_port_layout->addWidget(dir_label_port);
	dir_top_port_layout->addWidget(dir_ports);

	// Direct - distance
	QLabel *dir_label_distance = new QLabel(tr("Distance :"));
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

	// Mesure layout (acquisition and direct)
	QHBoxLayout *mesure_layout = new QHBoxLayout;
	mesure_layout->addWidget(acq_group_box);
	mesure_layout->addWidget(dir_group_box);

	// Main layout (configuration and mesure)
	QVBoxLayout *main_layout = new QVBoxLayout;
	main_layout->addWidget(conf_group_box);
	main_layout->addLayout(mesure_layout);
	this->setLayout(main_layout);

	// Update ports list
	this->searchPorts();
	QString default_port = "";
	this->updatePortAcq(default_port);
	this->updatePortDir(default_port);

	// Add signal and slot
	QObject::connect(acq_ports, SIGNAL(currentIndexChanged(int)), this, SLOT(selectedAcqPort(int)));
	QObject::connect(dir_ports, SIGNAL(currentIndexChanged(int)), this, SLOT(selectedDirPort(int)));

	// Init the calculator ans acquisitor
	this->calculator = new Calculator(this);
	this->acquisitor = new Acquisitor(this);

	/*test*/
	int pixel = 1333;
	double sigma = 0.7;
	float64 data[MAX_PIXEL];
	for (int i=0; i<MAX_PIXEL; i+=1) {
		data[i] = 5*(1/(sigma*sqrt(2*M_PI)))*exp(-(pow((double)i-pixel+1, 2))/(2*pow(sigma, 2)));
	}
	this->receiveData(data);
	this->receivePixel(pixel);
	
	// Show the window
	this->show();
}

MainWindow::~MainWindow() {
	if (conf_edit_focus != NULL) {
		delete(conf_edit_focus);
		conf_edit_focus = NULL;
	}
	if (conf_edit_gap != NULL) {
		delete(conf_edit_gap);
		conf_edit_gap = NULL;
	}
	if (conf_edit_pixel != NULL) {
		delete(conf_edit_pixel);
		conf_edit_pixel = NULL;
	}
	if (acq_ports != NULL) {
		delete(acq_ports);
		acq_ports = NULL;
	}
	if (dir_ports != NULL) {
		delete(dir_ports);
		dir_ports = NULL;
	}
	if (acq_edit_distance != NULL) {
		delete(acq_edit_distance);
		acq_edit_distance = NULL;
	}
	if (dir_edit_distance != NULL) {
		delete(dir_edit_distance);
		dir_edit_distance = NULL;
	}
	if (plotter != NULL) {
		delete(plotter);
		plotter = NULL;
	}
	if (calculator != NULL) {
		delete(calculator);
		calculator = NULL;
	}
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
	for (int i=0; i<MAX_PIXEL; i+=1) {
		acq_data.append(QPointF(i+1, data[i]));
	}
	this->drawPlotter();
	int pixel = 0;
	QString dist = "NC";
	pixel = this->calculator->getPixel(data);
	dist = this->calculator->getDist(pixel);
  this->updateDistance(MODE_ACQUISITION, dist);
}

void MainWindow::receivePixel(int pixel) {
  QString dist = "NC";
  if (pixel > 0) {
	dist = this->calculator->getDist(pixel);
  }
  this->updateDistance(MODE_DIRECT, dist);
}

float MainWindow::getAxesGap() {
	return this->conf_edit_gap->text().toFloat();
}

float MainWindow::getPixelWidth() {
	return this->conf_edit_pixel->text().toFloat();
}

float MainWindow::getLensFocus() {
	return this->conf_edit_focus->text().toFloat();
}