#include "stdafx.h"
#include "Model.h"

Model::Model() {
	sp = new dlib::shape_predictor();
	fastsp = new dlib::shape_predictor();
	net = new anet_type();

	//�����ڸ� �ҷ����� ���ϵ��� Ȯ���ϰ� �ҷ��ͼ� �� �� ������ �������
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
	/* Debug ��忡�� �۵������� Release ��忡�� �۵� �ȵ�
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