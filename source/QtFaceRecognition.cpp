#include "QtFaceRecognition.h"

QtFaceRecognition::QtFaceRecognition(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    
    CameraOptions* camOpt = new CameraOptions(&ui, this); //ó���� �����ϸ� �̰� ������. ī�޶� �ɼ� ������ �ϴ°�
    Model* model = new Model(); //�׽�Ʈ �ϱ� ���Ѱ� ���߿� ����� �ٸ� ���� ��ġ
}

QtFaceRecognition::~QtFaceRecognition() {

}