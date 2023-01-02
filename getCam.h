#pragma once
#include <dlib/opencv.h>
#include <opencv2/highgui.hpp>
#include "ui_QtFaceRecognition.h"

#include <QMenubar>
#include <QPixmap>
#include <QImage>
#include <QTimer>

class getCam : public QMainWindow {
	Q_OBJECT

public:
	getCam(QWidget* parent);
	~getCam();

private:
	void showCameraOptions();
	void onCameraActionTriggered();

	Ui::QtFaceRecognitionClass ui;
	cv::VideoCapture cap;

	QTimer* timer;

public slots:
	void updateFrame();
};