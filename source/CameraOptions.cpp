#include "CameraOptions.h"

CameraOptions::CameraOptions(Ui::QtFaceRecognitionClass* ui, QObject* parent) {
    this->camMenu = ui->menuCamera;
    this->status = ui->statusBar;
    this->camLabel = ui->label;

    cam = new ShowCam(camLabel, 10, this); //출력할 라벨, 몇 ms 마다 카메라를 업데이트 시킬지, 부모가 누구인지

    showCameraOptions(); //카메라 옵션을 보여주고
    resetCam(); //처음에 키기 때문에 0번째 카메라로 보여지게
}

CameraOptions::~CameraOptions() { //cameraOptions가 사라지면 실행
    cam->stop(); //이거 안하면 메모리에 계속 카메라가 남아있어서 뒤지나봄 (또 뒤짐)
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
    //getBackEndName 도 알아보기
    //카메라 번호와 이름으로 구조체를 만들고 벡터에 저장하고 표시하는 방식으로
    while (cap->open(numCameras)) {
        QAction* action = new QAction(QString("%1 Camera").arg(numCameras), this);
        connect(action, &QAction::triggered, this, &CameraOptions::onCameraActionTriggered); //메뉴를 트리거(클릭)하면 onCameraActionTriggered를 실행함
        camMenu->addAction(action);
        numCameras++;
    }
    if (numCameras == 0) {
        QAction* noAction = new QAction(QString("Not Found Camera").arg(numCameras), this);
        connect(noAction, &QAction::triggered, this, &CameraOptions::noCameraActionTriggered); //메뉴를 트리거(클릭)하면 onCameraActionTriggered를 실행함
        camMenu->addAction(noAction);
    }
}

void CameraOptions::onCameraActionTriggered() { 
    QAction* action = qobject_cast<QAction*>(sender());
    if (action) {
        int cameraNum = action->text().remove(" Camera").toInt();
        cap->open(cameraNum);

        if (cap->isOpened()) //웹캠 찾으면
            status->showMessage(QString("%1 Camera Connected!").arg(cameraNum));
        else
            status->showMessage(QString("%1 Camera Not Connected..").arg(cameraNum));
        
        cam->stop(); //카메라를 바꾸면 어차피 끄고 실행하기 때문에 무조건 끄고 실행

         //카메라 번호 지정
        cam->start(cameraNum); //캠을 시작해서 화면에 표시
    }
}

void CameraOptions::noCameraActionTriggered() {
    status->showMessage(QString("Camera Not Found"));
}