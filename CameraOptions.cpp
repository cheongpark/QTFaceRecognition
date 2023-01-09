#include "CameraOptions.h"

CameraOptions::CameraOptions(Ui::QtFaceRecognitionClass* ui, QObject* parent) {
    this->camMenu = ui->menuCamera;
    this->status = ui->statusBar;
    this->camLabel = ui->label;

    showCameraOptions();
    resetCam();
}

CameraOptions::~CameraOptions() { //cameraOptions가 사라지면 실행
    stopCam(); //이거 안하면 메모리에 계속 카메라가 남아있어서 뒤지나봄 (또 뒤짐)
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
    //getBackEndName 도 알아보기
    //카메라 번호와 이름으로 구조체를 만들고 벡터에 저장하고 표시하는 방식으로
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

        if (!cap->isOpened()) //웹캠 찾지 못하면
            status->showMessage(QString("%1 Camera Not Connected..").arg(cameraNum));
    
        if (cam->isRunning()) //이거 처음에 하게 하면 오류남
            stopCam();

        cam = new ShowCam(camLabel, cameraNum); //띄울 라벨과 카메라 번호 지정
        cam->start(); //캠을 시작해서 화면에 표시
    }
}