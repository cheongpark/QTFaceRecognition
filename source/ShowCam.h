#pragma once
#include <QLabel>
#include <QTimer>
#include <opencv2/opencv.hpp>

#include <QDebug>
//https://webnautes.tistory.com/1517 �̰� ���� ������ ��� ���ϰ� �ٲٱ�
class ShowCam : public QObject {
	Q_OBJECT
public:
	ShowCam(QLabel* label, const int &frameT, QObject* parent = nullptr);
	~ShowCam();

	void start(int camNum);
	void stop();

private:
	void updateCam();

	QTimer* timer;
	cv::VideoCapture* cap;
	cv::Mat frame;
	QLabel* label;

	QImage qimg;

	int frameT;
};