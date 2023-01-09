#include "stdafx.h" //��翡 ������ϸ� ������
#include "FaceRecognition.h"

FaceRecognition::FaceRecognition() {
	detector = dlib::get_frontal_face_detector();
}

FaceRecognition::~FaceRecognition() {
}

int FaceRecognition::faceCount(cv::Mat image) {
	dlib::cv_image<dlib::bgr_pixel> cimg(image);
	return detector(cimg).size();
}

int FaceRecognition::faceCount(dlib::cv_image<dlib::bgr_pixel> image) {
	return detector(image).size();
}