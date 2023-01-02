#include "getCam.h"

getCam::getCam(QWidget* parent) : QMainWindow(parent) {
    //cap.open(1);
    showCameraOptions();

    //timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(updateFrame()));
    //connect timer���� SIGNAL(timeout()) �� Ÿ�Ӿƿ��� �Ǹ� ����(this)�� �ִ� updateFrame�� �����
    //���� ���� ��� �̰� �ݺ��Ǵ� ��

    //timer->start(30);
}

getCam::~getCam() {

}

void getCam::showCameraOptions() {
    int numCameras = 0;
    //getBackEndName �� �˾ƺ���

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

        if (!cap.isOpened()) //��ķ ã�� ���ϸ�
            ui.statusBar->showMessage(QString("%1 Camera Not Connected..").arg(cameraNum));
    }
}