#include "Plane.h"

void Plane::Initialize(Model* model,
	const Vector3& position){
	//null�`�F�b�N
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("mario.jpg");

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void Plane::Update(){
	Transfer();
}

void Plane::Draw(const ViewProjection viewProjection){
	//�����`��
	model_->Draw(worldTransform_, viewProjection,textureHandle_);
}

void Plane::Transfer(){
	//matrix
	static Matrix4 scale;
	static  Matrix4 rot;
	static  Matrix4 translation;

	//�s��X�V
	scale = myMatrix_.MatrixScale(worldTransform_.scale_);
	rot = myMatrix_.MatrixRotationZ(worldTransform_.rotation_);
	rot *= myMatrix_.MatrixRotationX(worldTransform_.rotation_);
	rot *= myMatrix_.MatrixRotationY(worldTransform_.rotation_);
	translation = myMatrix_.MatrixTranslation(worldTransform_.translation_);

	worldTransform_.matWorld_ = myMatrix_.MatrixWorld(scale, rot, translation);

	//�]��
	worldTransform_.TransferMatrix();
}

void Plane::Move(){
}