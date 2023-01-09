#pragma once

class FaceRecognition
{
public:
	FaceRecognition();
	~FaceRecognition();

	int faceCount(cv::Mat Image); //¾ó±¼ÀÇ °³¼ö¸¦ °¡Á®¿È
	int faceCount(dlib::cv_image<dlib::bgr_pixel> Image); //¾ó±¼ÀÇ °³¼ö¸¦ °¡Á®¿È

private:
	dlib::frontal_face_detector detector;
};

