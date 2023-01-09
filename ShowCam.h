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

protected: //���� �����ϴ� ��
	void run(); //QThread�ϰ� run �̰� �ϸ� ���߿� �̰� ������ �� �ڵ����� �����尡 ��������� �� �ȿ��� ���� ó�� ��

private:
	QLabel* label;
	int camNum = 0;	
	bool useCam = false;

	cv::VideoCapture* cap = new cv::VideoCapture();
	cv::Mat* frame = new cv::Mat();
};