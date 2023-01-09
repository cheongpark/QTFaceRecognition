#include "QtFaceRecognition.h"

QtFaceRecognition::QtFaceRecognition(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    
    CameraOptions* camOpt = new CameraOptions(&ui, this); //처음에 실행하면 이걸 실행함. 카메라 옵션 나오게 하는거
    Model* model = new Model(); //테스트 하기 위한거 나중에 지우고 다른 곳에 배치
}

QtFaceRecognition::~QtFaceRecognition() {

}