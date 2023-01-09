#include "stdafx.h" //상당에 선언안하면 오류남
#include "FaceRecognition.h"

FaceRecognition::FaceRecognition() {
	detector = dlib::get_frontal_face_detector();
}

FaceRecognition::~FaceRecognition() {
}

int FaceRecognition::faceCount(cv::Mat Image) {
	dlib::cv_image<dlib::bgr_pixel> cimg(Image);
	return detector(cimg).size();
}

int faceCount(dlib::cv_image<dlib::bgr_pixel> Image) {
	return detector(Image).size();
}