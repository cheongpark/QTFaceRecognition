#pragma once
#include <QMainWindow>
#include <QMenu>
#include <vector>
#include "ui_QtFaceRecognition.h"

#include <dlib/opencv.h>
#include <opencv2/highgui.hpp>

#include "ShowCam.h"
//#include <QDebug>

class CameraOptions : public QObject {
	Q_OBJECT
public:
	CameraOptions(Ui::QtFaceRecognitionClass* ui, QObject* parent = nullptr);
	~CameraOptions();

private:
	void resetCam();

	void showCameraOptions();
	void onCameraActionTriggered();
	void noCameraActionTriggered();

	QMenu* camMenu;
	QStatusBar* status;
	QLabel* camLabel;

	ShowCam* cam;
	cv::VideoCapture* cap = new cv::VideoCapture();
	
	/*
	struct CameraInfo {
		QString name;
		int camNum;
	};

	std::vector<CameraInfo> camera;
	*/
};