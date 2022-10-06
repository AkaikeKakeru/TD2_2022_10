#include "Player.h"
#include <cassert>

void Player::Initilize(Model* model){
	//null�`�F�b�N
	assert(model);

	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_.x -= 20;
	//viewProjection_.Initialize();
}

void Player::Update(){
	Move();
	Transfer();
}

void Player::Draw(const ViewProjection viewProjection){
	model_->Draw(worldTransform_,viewProjection);
}

void Player::Transfer(){
	//matrix
	static Matrix4 scale;
	static  Matrix4 rota;
	static  Matrix4 translation;

	scale = myMatrix_.MatrixScale(worldTransform_.scale_);
	rota = myMatrix_.MatrixRotationZ(worldTransform_.rotation_);
	rota *= myMatrix_.MatrixRotationX(worldTransform_.rotation_);
	rota *= myMatrix_.MatrixRotationY(worldTransform_.rotation_);
	translation = myMatrix_.MatrixTranslation(worldTransform_.translation_);

	worldTransform_.matWorld_ = myMatrix_.MatrixWorld(scale, rota, translation);

	//�]��
	worldTransform_.TransferMatrix();
}

void Player::Move(){
	//���x�x�N�g��
	Vector3 speed = { 0,0,0 };
	//�o�ߎ���(�t���[��)
	static float time = 0.0f;

	//1F�o�ߖ���
	time += 1.0f;

	///�ɋ}�̂��鍶�E�^���ɂ�����
	///��sin�g�������I
	//�\�[���Ƃ�X�����̈ړ����x���v�Z
	speed.x = sin(time / 20);

	//�I�u�W�F�N�g�̍��W���ړ�
	worldTransform_.translation_
		+= speed;

	//�t���[���P�ʂ� �w�莞�� + 1F �o�߂�����
	if (time > 120 + 1) {
		//0�ɖ߂�
		time = 0;
	}
}
