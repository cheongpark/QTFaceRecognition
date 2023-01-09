#include "CameraOptions.h"

CameraOptions::CameraOptions(Ui::QtFaceRecognitionClass* ui, QObject* parent) {
    this->camMenu = ui->menuCamera;
    this->status = ui->statusBar;
    this->camLabel = ui->label;

    showCameraOptions();
    resetCam();
}

CameraOptions::~CameraOptions() { //cameraOptions�� ������� ����
    stopCam(); //�̰� ���ϸ� �޸𸮿� ��� ī�޶� �����־ �������� (�� ����)
    delete cam;

    delete camMenu;
    delete status;
    delete camLabel;
}

void CameraOptions::stopCam() {
    cam->stop();
    //cam->quit();
    cam->wait();
}

void CameraOptions::resetCam() {
    cam = new ShowCam(camLabel, 0);
    cam->start();
}

void CameraOptions::showCameraOptions() {
    int numCameras = 0;
    //getBackEndName �� �˾ƺ���
    //ī�޶� ��ȣ�� �̸����� ����ü�� ����� ���Ϳ� �����ϰ� ǥ���ϴ� �������
    while (cap->open(numCameras)) {
        QAction* action = new QAction(QString("%1 Camera").arg(numCameras), this);
        connect(action, &QAction::triggered, this, &CameraOptions::onCameraActionTriggered);
        camMenu->addAction(action);
        numCameras++;
    }
}

void CameraOptions::onCameraActionTriggered() { 
    QAction* action = qobject_cast<QAction*>(sender());
    if (action) {
        int cameraNum = action->text().remove(" Camera").toInt();
        status->showMessage(QString("%1 Camera Connected!").arg(cameraNum));
        cap->open(cameraNum);

        if (!cap->isOpened()) //��ķ ã�� ���ϸ�
            status->showMessage(QString("%1 Camera Not Connected..").arg(cameraNum));
    
        if (cam->isRunning()) //�̰� ó���� �ϰ� �ϸ� ������
            stopCam();

        cam = new ShowCam(camLabel, cameraNum); //��� �󺧰� ī�޶� ��ȣ ����
        cam->start(); //ķ�� �����ؼ� ȭ�鿡 ǥ��
    }
}