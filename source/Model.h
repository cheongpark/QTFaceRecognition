#pragma once
#include "stdafx.h"
#include <filesystem>
#include <string>

#include <QDebug>

class Model
{
public:
	Model();
	~Model();

private:
	const std::string spPath = "Dlib_Model/shape_predictor_68_face_landmarks_GTX.dat";
	const std::string fastspPath = "Dlib_Model/shape_predictor_5_face_landmarks.dat";
	const std::string ResNetPath = "Dlib_Model/dlib_face_recognition_resnet_model_v1.dat";

	template <template <int, template<typename>class, int, typename> class block, int n, template<typename>class bn, typename subnet>
	using residual = dlib::add_prev1<block<n, bn, 1, dlib::tag1<subnet>>>;

	template <template <int, template<typename>class, int, typename> class block, int n, template<typename>class bn, typename subnet>
	using residual_down = dlib::add_prev2<dlib::avg_pool<2, 2, 2, 2, dlib::skip1<dlib::tag2<block<n, bn, 2, dlib::tag1<subnet>>>>>>;

	template <int n, template <typename> class bn, int stride, typename subnet>
	using block = bn<dlib::con<n, 3, 3, 1, 1, dlib::relu<bn<dlib::con<n, 3, 3, stride, stride, subnet>>>>>;

	template <int n, typename subnet> using ares = dlib::relu<residual<block, n, dlib::affine, subnet>>;
	template <int n, typename subnet> using ares_down = dlib::relu<residual_down<block, n, dlib::affine, subnet>>;

	template <typename subnet> using alevel0 = ares_down<256, subnet>;
	template <typename subnet> using alevel1 = ares<256, ares<256, ares_down<256, subnet>>>;
	template <typename subnet> using alevel2 = ares<128, ares<128, ares_down<128, subnet>>>;
	template <typename subnet> using alevel3 = ares<64, ares<64, ares<64, ares_down<64, subnet>>>>;
	template <typename subnet> using alevel4 = ares<32, ares<32, ares<32, subnet>>>;

	using anet_type = dlib::loss_metric< dlib::fc_no_bias<128, dlib::avg_pool_everything<
		alevel0<
		alevel1<
		alevel2<
		alevel3<
		alevel4<
		dlib::max_pool<3, 3, 2, 2, dlib::relu<dlib::affine<dlib::con<32, 7, 7, 2, 2,
		dlib::input_rgb_image_sized<150>
		>>>>>>>>>>>>;

	dlib::shape_predictor* sp; //68점 찍는거
	dlib::shape_predictor* fastsp; //5점 찍는거 더 빠름
	anet_type* net; //벡터로 변환해주는거

	//Model의 파일이 있는지 확인
	bool modelFileCheck(const std::string path);
	//모델을 로드하는 것
	void loadModel();
};

