#include "stdafx.h"
#include "Model.h"

Model::Model() {
	sp = new dlib::shape_predictor();
	fastsp = new dlib::shape_predictor();
	net = new anet_type();

	//생성자를 불러오면 파일들을 확인하고 불러와서 각 모델 변수에 저장까지
	loadModel();
}

Model::~Model() {
	delete net;
	delete sp;
	delete fastsp;
}

bool Model::modelFileCheck(const std::string path) {
	return std::filesystem::exists(path);
}

void Model::loadModel() {
	/* Debug 모드에선 작동하지만 Release 모드에선 작동 안됨
	try {
		if (modelFileCheck(spPath))
			dlib::deserialize(spPath) >> *sp;

		if (modelFileCheck(fastspPath))
			dlib::deserialize(fastspPath) >> *fastsp;
		
		if (modelFileCheck(ResNetPath))
			dlib::deserialize(ResNetPath) >> *net;
	}
	catch (const std::exception& e) {
		qDebug() << e.what() << "Model Not Found!";
		//exit(-1);
	}
	*/
	
}