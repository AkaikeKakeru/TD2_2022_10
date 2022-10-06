#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

#include "MyMatrix.h"
#include <math.h>
class Player {

public: //��{�̊֐�	
	void Initilize(Model* model);
	void Update();
	void Draw(const ViewProjection viewProjection);

public: //�ŗL�̊֐�
	/// <summary>
	/// ���W�X�V
	/// </summary>
	void Transfer();

	/// <summary>
	/// ���ړ�
	/// </summary>
	void Move();

private://�悭�g���ϐ�
	//���f��
	Model* model_ = nullptr;
	//���[���h�g�����X�t�H�[��
	WorldTransform worldTransform_;
	//�r���[�v���W�F�N�V����
	//ViewProjection viewProjection_;

	MyMatrix myMatrix_;
};