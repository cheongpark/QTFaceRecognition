#pragma once
#include "stdafx.h"

class FaceRecognition
{
public:
	FaceRecognition();
	~FaceRecognition();

	int faceCount(cv::Mat Image); //���� ������ ������

private:
	dlib::frontal_face_detector detector;
};

