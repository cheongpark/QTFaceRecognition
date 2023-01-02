#pragma once

#include <QtWidgets/QMainWindow>

#include <string>
#include "ui_QtFaceRecognition.h"

#include <dlib/opencv.h>
#include <opencv2/highgui.hpp>

#include "getCam.h"

class QtFaceRecognition : public QMainWindow {
    Q_OBJECT

public:
    QtFaceRecognition(QWidget *parent = nullptr);
    ~QtFaceRecognition();

private:
    Ui::QtFaceRecognitionClass ui;
};
