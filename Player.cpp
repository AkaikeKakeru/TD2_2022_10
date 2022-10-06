#include "Player.h"
#include <cassert>

void Player::Initilize(Model* model){
	//nullチェック
	assert(model);

	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_.x -= 20;

	//シングルトンインスタンス
	input_ = Input::GetInstance();
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

	//転送
	worldTransform_.TransferMatrix();
}

void Player::Move(){
	//経過時間(フレーム)
	static float time = 0.0f;

	if (input_->TriggerKey(DIK_SPACE)) {
		ifBrake = true;
	}

	if (ifBrake == true) {
		speed.x = 0.0f;
	}
	else{
		//1F経過毎に
		time += 1.0f;

		///緩急のある左右運動にしたい
		///→自由研究でやったとこだ！sin使おうぜ！
		//…てことでX方向の移動速度を計算
		speed.x = sin(time / 20);

		//フレーム単位で 指定時間 + 1F 経過したら
		if (time > 120 + 1) {
			//0に戻す
			time = 0;
		}
	}

	//オブジェクトの座標を移動
	worldTransform_.translation_
		+= speed;
}

void Player::Blow(){
	if (input_->PushKey(DIK_SPACE)){

	}
}
