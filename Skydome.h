#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Skydome {
public: //��{�I�ȃ����o�֐�
	void Initialize();
	void Update();
	void Draw();

private: //�悭�g�������o�ϐ�
	//���[���h�g�����X�t�H�[��
	WorldTransform worldTransform_;

	//���f��
	Model* model_ = nullptr;
};