#include "QtFaceRecognition.h"

QtFaceRecognition::QtFaceRecognition(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    
    CameraOptions* camOpt = new CameraOptions(&ui);
}

QtFaceRecognition::~QtFaceRecognition() {

}