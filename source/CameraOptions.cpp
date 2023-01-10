#include "CameraOptions.h"

CameraOptions::CameraOptions(Ui::QtFaceRecognitionClass* ui, QObject* parent) {
    this->camMenu = ui->menuCamera;
    this->status = ui->statusBar;
    this->camLabel = ui->label;

    cam = new ShowCam(camLabel, 10, this); //����� ��, �� ms ���� ī�޶� ������Ʈ ��ų��, �θ� ��������

    showCameraOptions(); //ī�޶� �ɼ��� �����ְ�
    resetCam(); //ó���� Ű�� ������ 0��° ī�޶�� ��������
}

CameraOptions::~CameraOptions() { //cameraOptions�� ������� ����
    cam->stop(); //�̰� ���ϸ� �޸𸮿� ��� ī�޶� �����־ �������� (�� ����)
    delete cam;

    delete camMenu;
    delete status;
    delete camLabel;
}

void CameraOptions::resetCam() {
    cam->start(0);
}

void CameraOptions::showCameraOptions() {
    int numCameras = 0;
    //getBackEndName �� �˾ƺ���
    //ī�޶� ��ȣ�� �̸����� ����ü�� ����� ���Ϳ� �����ϰ� ǥ���ϴ� �������
    while (cap->open(numCameras)) {
        QAction* action = new QAction(QString("%1 Camera").arg(numCameras), this);
        connect(action, &QAction::triggered, this, &CameraOptions::onCameraActionTriggered); //�޴��� Ʈ����(Ŭ��)�ϸ� onCameraActionTriggered�� ������
        camMenu->addAction(action);
        numCameras++;
    }
    if (numCameras == 0) {
        QAction* noAction = new QAction(QString("Not Found Camera").arg(numCameras), this);
        connect(noAction, &QAction::triggered, this, &CameraOptions::noCameraActionTriggered); //�޴��� Ʈ����(Ŭ��)�ϸ� onCameraActionTriggered�� ������
        camMenu->addAction(noAction);
    }
}

void CameraOptions::onCameraActionTriggered() { 
    QAction* action = qobject_cast<QAction*>(sender());
    if (action) {
        int cameraNum = action->text().remove(" Camera").toInt();
        cap->open(cameraNum);

        if (cap->isOpened()) //��ķ ã����
            status->showMessage(QString("%1 Camera Connected!").arg(cameraNum));
        else
            status->showMessage(QString("%1 Camera Not Connected..").arg(cameraNum));
        
        cam->stop(); //ī�޶� �ٲٸ� ������ ���� �����ϱ� ������ ������ ���� ����

         //ī�޶� ��ȣ ����
        cam->start(cameraNum); //ķ�� �����ؼ� ȭ�鿡 ǥ��
    }
}

void CameraOptions::noCameraActionTriggered() {
    status->showMessage(QString("Camera Not Found"));
}