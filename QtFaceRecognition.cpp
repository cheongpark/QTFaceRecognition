#include "QtFaceRecognition.h"

QtFaceRecognition::QtFaceRecognition(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    
    CameraOptions* camOpt = new CameraOptions(&ui, this);
    Model* model = new Model(); //�׽�Ʈ �ϱ� ���Ѱ�
}

QtFaceRecognition::~QtFaceRecognition() {

}