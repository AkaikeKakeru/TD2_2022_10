#include "Skydome.h"
#include <cassert>

void Skydome::Initialize(Model* model) {
	//nullチェック
	assert(model);

	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.scale_ = { 200,200,200 };
	worldTransform_.translation_ = { 0,0,0 };
}

void Skydome::Update(){
	Transfer();
}

void Skydome::Draw(ViewProjection viewProjection){
	model_->Draw(worldTransform_, viewProjection);
}

void Skydome::Transfer(){
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

	//転送
	worldTransform_.TransferMatrix();
}