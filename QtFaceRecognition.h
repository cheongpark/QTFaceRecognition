#pragma once

#include <QMainWindow>
#include "ui_QtFaceRecognition.h"

#include "CameraOptions.h"


class QtFaceRecognition : public QMainWindow {
    Q_OBJECT

public:
    QtFaceRecognition(QWidget *parent = nullptr);
    ~QtFaceRecognition();

private:
    Ui::QtFaceRecognitionClass ui;
};
