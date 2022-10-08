#include "RailCamera.h"

void RailCamera::Initialize(
	Vector3 position,
	Vector3 radian){
	//ワールドトランスフォーム初期設定
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = radian;

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void RailCamera::Update(){
}