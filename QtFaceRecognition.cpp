#include "QtFaceRecognition.h"

QtFaceRecognition::QtFaceRecognition(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);

    getCam* cam = new getCam(this);
}

QtFaceRecognition::~QtFaceRecognition() {

}