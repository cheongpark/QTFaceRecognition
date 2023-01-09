#include "QtFaceRecognition.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("Image/icon.jpg"));
    QtFaceRecognition w;
    w.show();
    return a.exec();
}

//스레드가 종료되었습니다. 문구가 엄청 많이 뜨는 이유 찾기