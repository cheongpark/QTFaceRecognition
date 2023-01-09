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
	cap->open(camNum); //ī�޶� ��ȣ ����

	if (!cap->isOpened()) //ī�޶� �������� ������
		qDebug() << "Camera Not Opened";
	else {
		qDebug() << "Camera Opened";

		connect(timer, &QTimer::timeout, this, &ShowCam::updateCam); //frameT���� �ð��� �� ������ updateCam�� ������
		timer->start(frameT); //frameT���� ĸ�İ� �̷������ �����ϸ� ��
	}
}

void ShowCam::stop() {
	disconnect(timer, &QTimer::timeout, this, &ShowCam::updateCam); //������ ���� �ٽ� ����
	cap->release(); //cap�� �޸𸮸� �������ִ°��� ���ϸ� ū�ϳ����� ��
}

void ShowCam::updateCam() {
	*cap >> *frame; //cap�� �̹��� ������ frame���� �Ѱ���

	qimg = QImage((const unsigned char*)(frame->data), frame->cols, frame->rows, QImage::Format_RGB888); //QImage�� frame�� �̹��� ������ �ѱ�
	label->setPixmap(QPixmap::fromImage(qimg.rgbSwapped())); //������ �󺧷� �̹����� ������ �����
	//label->setScaledContents(true);

	//ī�޶��� ĸ�� �������� ���� ���簢������ ���� label�� ������ �׳� �ϸ� ©�� �� ������ label->setScaledContents(true); �̰͵� �ϱ�
}