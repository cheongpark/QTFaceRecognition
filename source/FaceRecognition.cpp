#include "stdafx.h" //��翡 ������ϸ� ������
#include "FaceRecognition.h"

FaceRecognition::FaceRecognition() {
	detector = dlib::get_frontal_face_detector();
}

FaceRecognition::~FaceRecognition() {
}

int FaceRecognition::faceCount(cv::Mat image) {
	dlib::cv_image<dlib::bgr_pixel> cimg(image); //detector�� ã�� �� �ְ� dlib �̹����� ��ȯ�ϴ°� OpenCV�� cap�� �⺻ bgr�̱� ������ bgr_pixel��
	return detector(cimg).size(); //detector�� �� ���� ã�Ƽ� ����
}

int FaceRecognition::faceCount(dlib::cv_image<dlib::bgr_pixel> image) {
	return detector(image).size(); //detector�� �� ���� ã�Ƽ� ����
}