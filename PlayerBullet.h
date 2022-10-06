#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "MyMatrix.h"
#include "DebugText.h"

///<summary>
///���L�����̒e
/// </summary>
class PlayerBullet{
public://��{�I�Ȋ֐�
	void Intialize(Model* model,
		const Vector3& position,
		const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);

public://�ŗL�̊֐�
	void Transfer();
	bool IsDead() const { return isDead_; }

private://�悭�g���ϐ�
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//���[���h�ϊ��s��
	MyMatrix myMatrix_;

	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;

private://�ŗL�̕ϐ�
	//���x
	Vector3 velocity_;

	//����<frm>
	static const int32_t kLifeTime = 60 * 5;
	//�f�X�^�C�}�[
	int32_t deathtimer_ = kLifeTime;
	//�f�X�t���O
	bool isDead_ = false;
};