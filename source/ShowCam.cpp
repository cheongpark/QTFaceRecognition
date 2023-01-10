#include "ShowCam.h"

ShowCam::ShowCam(QLabel* label, const int &frameT, QObject* parent) {
	this->label = label;
	this->frameT = frameT;

	timer = new QTimer(this);
	cap = new cv::VideoCapture();
}

ShowCam::~ShowCam() {
	disconnect(timer, &QTimer::timeout, this, &ShowCam::updateCam);
	cap->release();

	delete label;
	delete cap;
}

void ShowCam::start(int camNum) {
	cap->open(camNum); //카메라 번호 설정

	if (!cap->isOpened()); //카메라가 열려있지 않은지
		//qDebug() << "Camera Not Opened";
	else {
		//qDebug() << "Camera Opened";

		connect(timer, &QTimer::timeout, this, &ShowCam::updateCam); //frameT마다 시간이 다 지나면 updateCam을 실행함
		timer->start(frameT); //frameT마다 캡쳐가 이루어진다 생각하면 됨
	}
}

void ShowCam::stop() {
	disconnect(timer, &QTimer::timeout, this, &ShowCam::updateCam); //정지를 위해 다시 해제
	cap->release(); //cap의 메모리를 해제해주는거임 안하면 큰일날지도 모름
}

void ShowCam::updateCam() {
	*cap >> frame; //cap의 이미지 정보를 frame으로 넘겨줌
	//cols = 가로 , rows = 세로
	if (frame.cols >= frame.rows) { // 가로가 더 크면 같으면
		//가로가 더 김
		frame = frame(cv::Range(0, frame.rows), cv::Range((frame.cols - frame.rows) / 2, (frame.cols - frame.rows) / 2 + frame.rows));
	}
	else {
		//세로가 더 김
		//세로에서 긴것 부터 작은 것을 빼서 거기에서 / 2를 해서 처음부터 끝까지 뭐 암튼 그런거
		frame = frame(cv::Range((frame.rows - frame.cols) / 2, (frame.rows - frame.cols) / 2 + frame.cols), cv::Range(0, frame.cols));
	}

	//4를 더하지 않으면 화면이 약간 이상하게 안맞아서 깨지거나 색이 이상해짐
	cv::resize(frame, frame, cv::Size(frame.cols + 4, frame.rows + 4));

	//qDebug() << frame.cols << " " << frame.rows;
	qimg = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888); //QImage로 frame의 이미지 정보를 넘김
	label->setPixmap(QPixmap::fromImage(qimg.rgbSwapped())); //지정한 라벨로 이미지를 보내서 등록함
	label->setScaledContents(true);

	//카메라의 캡쳐 사이즈의 따라 정사각형으로 만들어서 label로 보내고 그냥 하면 짤릴 수 있으니 label->setScaledContents(true); 이것도 하기
}