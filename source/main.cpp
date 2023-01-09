#include "QtFaceRecognition.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("Image/icon.jpg")); //아이콘 지정
    QtFaceRecognition w;
    w.show();
    return a.exec();
}