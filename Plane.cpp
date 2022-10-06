#include "Plane.h"

void Plane::Initialize(Model* model){
	//nullチェック
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("mario.jpg");

	worldTransform_.Initialize();
	worldTransform_.translation_.z -= 30;
}

void Plane::Update(){
}

void Plane::Draw(const ViewProjection viewProjection){
	//自分描画
	model_->Draw(worldTransform_, viewProjection,textureHandle_);
}

void Plane::Transfer(){
}

void Plane::Move(){
}