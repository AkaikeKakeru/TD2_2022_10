#include "RailCamera.h"

void RailCamera::Initialize(
	Vector3 position,
	Vector3 radian){
	//���[���h�g�����X�t�H�[�������ݒ�
	worldTransform_.Initialize();
	worldTransform_.scale_ = Vector3(1, 1, 1);
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = radian;

	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_.Initialize();

	//�V���O���g���C���X�^���X
	debugText_ = DebugText::GetInstance();
}

void RailCamera::Update(){
	Move();

	UpdateWorldTransform();
	UpdateViewProjection();

	debugText_->SetPos(400,100);
	debugText_->Printf(
		"pos:%f,%f,%f",
		worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z
	);

	debugText_->SetPos(400,200);
	debugText_->Printf(
		"eye:%f,%f,%f",
		viewProjection_.eye.x,
		viewProjection_.eye.y,
		viewProjection_.eye.z
		);
}

void RailCamera::Move(){
	worldTransform_.translation_.z++;

	worldTransform_.rotation_.z++;
}

void RailCamera::UpdateWorldTransform(){
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

void RailCamera::UpdateViewProjection(){
	viewProjection_.eye =
		Vector3(
			worldTransform_.matWorld_.m[0][3],
			worldTransform_.matWorld_.m[1][3],
			worldTransform_.matWorld_.m[2][3]
			);

	//���[���h�O���x�N�g��
	Vector3 forward(0,0,1);

	//���[���J�����̉�]�𔽉f
	forward = Vector3Transform(forward,worldTransform_.matWorld_);

	//���_����O���ɓK���ȋ����i�񂾈ꂪ�����_
	viewProjection_.target = viewProjection_.eye + forward;

	//����x�N�g��
	Vector3 up(0,1,0);

	//���[���J�����̉�]�𔽉f (���[���J�����̏���x�N�g��)
	viewProjection_.up = Vector3Transform(up, worldTransform_.matWorld_);

	//�r���[�v���W�F�N�V�������X�V
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
}