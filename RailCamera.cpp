#include "RailCamera.h"

void RailCamera::Initialize(
	Vector3 position,
	Vector3 radian){
	//���[���h�g�����X�t�H�[�������ݒ�
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = radian;

	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_.Initialize();
}

void RailCamera::Update(){
}