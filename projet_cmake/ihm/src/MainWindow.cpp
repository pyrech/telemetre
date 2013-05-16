#include "MainWindow.h"
#include "Calculator.h"
#include "Acquisitor.h"


using namespace std;


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

	// Acquisition - Layout (distance, plotter)
	QVBoxLayout *acq_layout = new QVBoxLayout;
    acq_layout->setAlignment(Qt::AlignTop);
	acq_layout->addLayout(acq_top_dist_layout);
	acq_layout->addStretch();
	acq_layout->addWidget(plotter);
	
	// Acquistion - Group box
	QGroupBox *acq_group_box = new QGroupBox(tr("Carte d'acquisition"));
	acq_group_box->setLayout(acq_layout);

	// Controller - ports
	QLabel *ctrl_label_port = new QLabel(tr("Port :"));
	ctrl_ports = new QComboBox(this);
	ctrl_label_port->setBuddy(ctrl_ports);
	
	// Controller - Top layout (ports)
	QHBoxLayout *ctrl_top_port_layout = new QHBoxLayout;
	ctrl_top_port_layout->addWidget(ctrl_label_port);
	ctrl_top_port_layout->addWidget(ctrl_ports);

	// Controller - pixel
	QLabel *ctrl_label_pixel = new QLabel(tr("Pixel :"));
	ctrl_edit_pixel = new QLineEdit;
	ctrl_edit_pixel->setReadOnly(true);
	ctrl_label_pixel->setBuddy(ctrl_edit_pixel);

	// Controller - Top layout (pixel)
	QHBoxLayout *ctrl_top_pixel_layout = new QHBoxLayout;
	ctrl_top_pixel_layout->addWidget(ctrl_label_pixel);
	ctrl_top_pixel_layout->addWidget(ctrl_edit_pixel);

	// Controller - distance
	QLabel *ctrl_label_distance = new QLabel(tr("Distance :"));
	ctrl_edit_distance = new QLineEdit;
	ctrl_edit_distance->setReadOnly(true);
	ctrl_label_distance->setBuddy(ctrl_edit_distance);

	// Controller - Top layout (distance)
	QHBoxLayout *ctrl_top_dist_layout = new QHBoxLayout;
	ctrl_top_dist_layout->addWidget(ctrl_label_distance);
	ctrl_top_dist_layout->addWidget(ctrl_edit_distance);

	// Controller - Layout (ports, pixel, distance)
	QVBoxLayout *ctrl_layout = new QVBoxLayout;
    ctrl_layout->setAlignment(Qt::AlignTop);
	ctrl_layout->addLayout(ctrl_top_port_layout);
	ctrl_layout->addLayout(ctrl_top_pixel_layout);
	ctrl_layout->addLayout(ctrl_top_dist_layout);
	
	// Controller - Group box
	QGroupBox *ctrl_group_box = new QGroupBox(tr("Microcontroleur"));
	ctrl_group_box->setLayout(ctrl_layout);

	// Mesure layout (acquisition and controller)
	QHBoxLayout *mesure_layout = new QHBoxLayout;
	mesure_layout->addWidget(acq_group_box);
	mesure_layout->addWidget(ctrl_group_box);

	// Log - field
	log_edit = new QTextEdit();
	log_edit->setReadOnly(true);

	// Log - Layout
	QHBoxLayout *log_layout = new QHBoxLayout;
	log_layout->addWidget(log_edit);

	// Log - Group box
	QGroupBox *log_group_box = new QGroupBox(tr("Console"));
	log_group_box->setLayout(log_layout);

	// Main layout (configuration, mesure, log)
	QVBoxLayout *main_layout = new QVBoxLayout;
	main_layout->addWidget(conf_group_box);
	main_layout->addLayout(mesure_layout);
	main_layout->addWidget(log_group_box);
	this->setLayout(main_layout);

	// Update ports list
	this->searchPorts();
	QString default_port = "";
	this->updatePortController(default_port);

	// Add signal and slot
	QObject::connect(ctrl_ports, SIGNAL(currentIndexChanged(int)), this, SLOT(selectedControllerPort(int)));

	// Init the calculator and acquisitor
	this->calculator = new Calculator(this);
	this->acquisitor = new Acquisitor(this);

	this->log("Init the programm");

	/*test*/
	int pixel = 1333;
	double sigma = 20;
	float64 data[MAX_PIXEL];
	for (int i=0; i<MAX_PIXEL; i+=1) {
		data[i] = 100*(1/(sigma*sqrt(2*M_PI)))*exp(-(pow((double)i-pixel+1, 2))/(2*pow(sigma, 2)));
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
	if (ctrl_ports != NULL) {
		delete(ctrl_ports);
		ctrl_ports = NULL;
	}
	if (acq_edit_distance != NULL) {
		delete(acq_edit_distance);
		acq_edit_distance = NULL;
	}
	if (ctrl_edit_distance != NULL) {
		delete(ctrl_edit_distance);
		ctrl_edit_distance = NULL;
	}
	if (log_edit != NULL) {
		delete(log_edit);
		log_edit = NULL;
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

	

	#ifdef __APPLE__

		string ls = Tools::GetStdoutFromCommand("ls /dev/cu.*");

		istringstream iss(ls);
		vector<string> tokens;
		copy(istream_iterator<string>(iss),
	         istream_iterator<string>(),
	         back_inserter<vector<string> >(tokens));

		for (std::vector<string>::iterator it = tokens.begin() ; it != tokens.end(); ++it){

			QString str((*it).c_str()); 
			ports_found.append(str);

		}
	    	

	
 	#else


		ports_found.append("USB1");
		ports_found.append("USB2");
		ports_found.append("USB3");
		ports_found.append("USB4");
		ports_found.append("CD");

	#endif


	// https://groups.google.com/forum/?fromgroups=#!topic/boost-list/0RpVAVSTQXQ

	// http://www.codeguru.com/cpp/w-p/system/hardwareinformation/article.php/c5721/Determining-What-Serial-Ports-Are-Available-on-a-Windows-Machine.htm

	// http://qt-project.org/wiki/QtSerialPort

    /*
    foreach (QextPortInfo info, QextSerialEnumerator::getPorts()) {
		
		ports_found.append(info.portName);

        std::cout << "port name:"       << info.portName.toStdString();
        std::cout << "friendly name:"   << info.friendName.toStdString();
        std::cout << "physical name:"   << info.physName.toStdString();
        std::cout << "enumerator name:" << info.enumName.toStdString();
        std::cout << "vendor ID:"       << info.vendorID;
        std::cout << "product ID:"      << info.productID;
	}
	*/
}

void MainWindow::updatePortController(QString &text) {
	ctrl_ports->clear();
	ctrl_ports->addItem("");
    foreach (QString port, ports_found) {
		ctrl_ports->addItem(port);
	}
	int index = ctrl_ports->findText(text);
	if(index != -1) {
		ctrl_ports->setCurrentIndex(index);
	}
}

void MainWindow::selectedControllerPort(int selected) {
	if (selected == 0) {
		// disable some fields ?
		// disable the qextserialport ?
		this->log("No port selected for microcontroller");
	}
	else {
		// TODO
		this->log("Change port of microcontroller for "+ctrl_ports->itemText(selected));
	}
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
		case MODE_CONTROLLER: {
			this->ctrl_edit_distance->setText(dist);
			break;
		}
	}
}

void MainWindow::receiveData(float64* data) {
	#ifdef VERBOSE
	this->log("Acquisition : receive data");
	#endif
	acq_data.erase(acq_data.begin(), acq_data.end());
	plotter->clearCurve(PLOTTER_CURVE_ID);
	for (int i=0; i<MAX_PIXEL; i+=1) {
		acq_data.append(QPointF(i+1, data[i]));
	}
	this->drawPlotter();
	int pixel = 0;
	QString dist = "NC";
	pixel = this->calculator->getPixel(data);
	#ifdef VERBOSE
	this->log("Acquisition : pixel calculated ("+QString::number(pixel)+")");
	#endif
	dist = this->calculator->getDist(pixel);
	this->updateDistance(MODE_ACQUISITION, dist);
}

void MainWindow::receivePixel(int pixel) {
	#ifdef VERBOSE
	this->log("Microcontroller : receive pixel ("+QString::number(pixel)+")");
	#endif
	QString dist = "NC";
	this->ctrl_edit_pixel->clear();
	if (pixel > 0) {
		this->ctrl_edit_pixel->setText(QString::number(pixel));
		dist = this->calculator->getDist(pixel);
	}
	this->updateDistance(MODE_CONTROLLER, dist);
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

void MainWindow::log(QString str) {
	this->log_edit->append(QTime::currentTime().toString("HH:mm:ss:zzz")+" - "+str);
}