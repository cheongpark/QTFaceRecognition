#include "getCam.h"

getCam::getCam(QWidget* parent) : QMainWindow(parent) {
    //cap.open(1);
    showCameraOptions();

    //timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(updateFrame()));
    //connect timer에서 SIGNAL(timeout()) 즉 타임아웃이 되면 여기(this)에 있는 updateFrame이 실행됨
    //저거 쓰면 계속 이게 반복되는 듯

    //timer->start(30);
}

getCam::~getCam() {

}

void getCam::showCameraOptions() {
    int numCameras = 0;
    //getBackEndName 도 알아보기

    while (cap.open(numCameras)) {
        QAction* action = new QAction(QString("%1 Camera").arg(numCameras), this);
        connect(action, &QAction::triggered, this, &getCam::onCameraActionTriggered);
        ui.menuCamera->addAction(action);
        numCameras++;
    }
}

void getCam::updateFrame() {
    cv::Mat frame;
    cap >> frame;
    if (frame.empty()) {
        std::cerr << "ERROR: Could not get frame from webcam." << std::endl;
        //return;
    }

    QImage qt_image = QImage((const uchar*)frame.data, frame.cols, frame.rows, QImage::Format_RGB888).rgbSwapped();
    ui.label->setPixmap(QPixmap::fromImage(qt_image));
}

void getCam::onCameraActionTriggered() {
    QAction* action = qobject_cast<QAction*>(sender());
    if (action) {
        int cameraNum = action->text().remove(" Camera").toInt();
        ui.statusBar->showMessage(QString("%1 Camera Connected!").arg(cameraNum));
        cap.open(cameraNum);

        if (!cap.isOpened()) //웹캠 찾지 못하면
            ui.statusBar->showMessage(QString("%1 Camera Not Connected..").arg(cameraNum));
    }
}