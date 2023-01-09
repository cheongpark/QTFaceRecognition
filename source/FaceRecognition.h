#pragma once

class FaceRecognition
{
public:
	FaceRecognition();
	~FaceRecognition();

	int faceCount(cv::Mat Image); //���� ������ ������
	int faceCount(dlib::cv_image<dlib::bgr_pixel> Image); //���� ������ ������

private:
	dlib::frontal_face_detector detector;
};

