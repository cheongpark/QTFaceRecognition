#include "stdafx.h" //상당에 선언안하면 오류남
#include "FaceRecognition.h"

FaceRecognition::FaceRecognition() {
	detector = dlib::get_frontal_face_detector();
}

FaceRecognition::~FaceRecognition() {
}

int FaceRecognition::faceCount(cv::Mat image) {
	dlib::cv_image<dlib::bgr_pixel> cimg(image); //detector이 찾을 수 있게 dlib 이미지로 변환하는거 OpenCV의 cap이 기본 bgr이기 때문에 bgr_pixel로
	return detector(cimg).size(); //detector로 얼굴 갯수 찾아서 리턴
}

int FaceRecognition::faceCount(dlib::cv_image<dlib::bgr_pixel> image) {
	return detector(image).size(); //detector로 얼굴 갯수 찾아서 리턴
}