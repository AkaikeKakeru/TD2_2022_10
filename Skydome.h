#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "MyMatrix.h"

class Skydome {
public: //��{�I�ȃ����o�֐�
	void Initialize(Model* model);
	void Update();
	void Draw(const ViewProjection viewProjection);

public: //�ŗL�̃����o�֐�
		/// <summary>
		/// ���W�X�V
		/// </summary>
	void Transfer();

private: //�悭�g�������o�ϐ�
	//���[���h�g�����X�t�H�[��
	WorldTransform worldTransform_;

	//���f��
	Model* model_ = nullptr;

	MyMatrix myMatrix_;
};