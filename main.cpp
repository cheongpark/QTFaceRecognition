#include "QtFaceRecognition.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QtFaceRecognition w;
    w.show();
    return a.exec();
}
