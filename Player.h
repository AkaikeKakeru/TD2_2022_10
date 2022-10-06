#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Input.h"
#include "DebugText.h"

#include "MyMatrix.h"
#include <math.h>

#include "PlayerBullet.h"

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

	/// <summary>
	/// ������΂�
	/// </summary>
	void Blow();

private://�悭�g���ϐ�
	//���f��
	Model* model_ = nullptr;
	//���[���h�g�����X�t�H�[��
	WorldTransform worldTransform_;
	//�r���[�v���W�F�N�V����
	//ViewProjection viewProjection_;
	//�C���v�b�g
	Input* input_ = nullptr;

	MyMatrix myMatrix_;

	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;

private: //�ŗL�̕ϐ�
	//�e
	std::list<std::unique_ptr<PlayerBullet>> bullets_;


	//���x�x�N�g��
	Vector3 speed = { 0,0,0 };
	
	//�u���[�L
	bool ifBrake = false;
};