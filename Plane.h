#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DebugText.h"

#include "MyMatrix.h"
#include <math.h>

class Plane {
public: //��{�̊֐�	
	void Initialize(Model* model,
		const Vector3& position);
	void Update();
	void Draw(const ViewProjection viewProjection);

public: //�ŗL�̊֐�
	/// <summary>
	/// ���W�X�V
	/// </summary>
	void Transfer();

	/// <summary>
	/// �ړ�
	/// </summary>
	void Move();

private://�悭�g���ϐ�
		//���f��
	Model* model_ = nullptr;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//���[���h�g�����X�t�H�[��
	WorldTransform worldTransform_;

	MyMatrix myMatrix_;

	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;

private: //�ŗL�̕ϐ�
};