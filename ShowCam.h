#pragma once
#include <QLabel>
#include <QThread>
#include <opencv2/opencv.hpp>

class ShowCam : public QThread {
	Q_OBJECT
public:
	ShowCam(QLabel* label, int camNum, QThread* parent = nullptr);
	~ShowCam();

	void stop();

protected: //접근 제한하는 거
	void run(); //QThread하고 run 이걸 하면 나중에 이걸 실행할 때 자동으로 스레드가 만들어지고 그 안에서 일을 처리 함

private:
	QLabel* label;
	int camNum = 0;	
	bool useCam = false;

	cv::VideoCapture* cap = new cv::VideoCapture();
	cv::Mat* frame = new cv::Mat();
};