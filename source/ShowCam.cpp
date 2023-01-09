#include "ShowCam.h"

ShowCam::ShowCam(QLabel* label, const int &frameT, QObject* parent) {
	this->label = label;
	this->frameT = frameT;

	timer = new QTimer(this);
	cap = new cv::VideoCapture();
	frame = new cv::Mat();
}

ShowCam::~ShowCam() {
	disconnect(timer, &QTimer::timeout, this, &ShowCam::updateCam);
	cap->release();

	delete label;
	delete cap;
	delete frame;
}

void ShowCam::start(int camNum) {
	cap->open(camNum);

	if (!cap->isOpened())
		qDebug() << "Camera Not Opened";
	else {
		qDebug() << "Camera Opened";

		connect(timer, &QTimer::timeout, this, &ShowCam::updateCam);
		timer->start(frameT);
	}
}

void ShowCam::stop() {
	disconnect(timer, &QTimer::timeout, this, &ShowCam::updateCam);
	cap->release();
}

void ShowCam::updateCam() {
	*cap >> *frame;

	qimg = QImage((const unsigned char*)(frame->data), frame->cols, frame->rows, QImage::Format_RGB888);
	label->setPixmap(QPixmap::fromImage(qimg.rgbSwapped()));
	//label->setScaledContents(true);
}