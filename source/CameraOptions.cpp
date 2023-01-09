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
}

void CameraOptions::onCameraActionTriggered() { 
    QAction* action = qobject_cast<QAction*>(sender());
    if (action) {
        int cameraNum = action->text().remove(" Camera").toInt();
        status->showMessage(QString("%1 Camera Connected!").arg(cameraNum));
        cap->open(cameraNum);

        if (!cap->isOpened()) //��ķ ã�� ���ϸ�
            status->showMessage(QString("%1 Camera Not Connected..").arg(cameraNum));
        
        cam->stop(); //ī�޶� �ٲٸ� ������ ���� �����ϱ� ������ ������ ���� ����

         //ī�޶� ��ȣ ����
        cam->start(cameraNum); //ķ�� �����ؼ� ȭ�鿡 ǥ��
    }
}