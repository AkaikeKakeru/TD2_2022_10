#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"

#include "MyMatrix.h"
#include "DebugText.h"

class RailCamera{
public: //��{�����o�֐�
	/// <param name="worldTransform">���[���h�g�����X�t�H�[��</param>
	void Initialize(
		Vector3 position,
		Vector3 radian);
	void Update();

public: // �ŗL�̃����o�֐�

	/// <summary>
	/// �ړ�
	/// </summary>
	void Move();

	/// <summary>
	/// ���W�X�V
	/// </summary>
	void UpdateWorldTransform();

	/// <summary>
	/// �r���[�v���W�F�N�V�����X�V
	/// </summary>
	void UpdateViewProjection();

private://�悭�g�������o�ϐ�
	//���[���h�g�����X�t�H�[��
	WorldTransform worldTransform_;

	//�r���[�v���W�F�N�V����
	ViewProjection viewProjection_;

	MyMatrix myMatrix_;

	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;
};