#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"

class RailCamera{
public: //��{�����o�֐�
	/// <param name="worldTransform">���[���h�g�����X�t�H�[��</param>
	void Initialize(
		Vector3 position,
		Vector3 radian);
	void Update();

private://�悭�g�������o�ϐ�
	//���[���h�g�����X�t�H�[��
	WorldTransform worldTransform_;

	//�r���[�v���W�F�N�V����
	ViewProjection viewProjection_;
};