#include "QtFaceRecognition.h"

QtFaceRecognition::QtFaceRecognition(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    
    CameraOptions* camOpt = new CameraOptions(&ui, this);
    Model* model = new Model(); //테스트 하기 위한거
}

QtFaceRecognition::~QtFaceRecognition() {

}