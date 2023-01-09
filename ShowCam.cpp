#include "ShowCam.h"

ShowCam::ShowCam(QLabel* label, int camNum, QThread* parent) {
	this->label = label;
	this->camNum = camNum;
}

ShowCam::~ShowCam() {
	delete label;
	delete cap;
	delete frame;
}

void ShowCam::run() {
	cap->open(camNum);

	if (!cap->isOpened()) //이거 잘 모르겠음
		return;
	
	QImage qimg;

	useCam = true;

	while (useCam) {
		*cap >> *frame;
		if (frame->empty())
			break;

		qimg = QImage((const unsigned char*)(frame->data), frame->cols, frame->rows, QImage::Format_RGB888);
		label->setPixmap(QPixmap::fromImage(qimg.rgbSwapped()));
		label->setScaledContents(true);
	}
}

void ShowCam::stop() {
	useCam = false;
}
