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
	//デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	Move();

	Blow();

	//弾更新
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

	Transfer();
}

void Player::Draw(const ViewProjection viewProjection){
	model_->Draw(worldTransform_,viewProjection);

	//弾描画
	for(std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
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
	const float kBulletSpeed = 1.0f;
	Vector3 bulletVelocity_ = Vector3(0, 0, kBulletSpeed);

	Vector3 bulletPosition_ = 
		Vector3(
			worldTransform_.matWorld_.m[3][0],
			worldTransform_.matWorld_.m[3][1],
			worldTransform_.matWorld_.m[3][2]
		);

	if (input_->TriggerKey(DIK_SPACE))
	{
		//速度ベクトルを自機の向きにあわせる
		bulletVelocity_ = myMatrix_.CrossVector(bulletVelocity_, worldTransform_.matWorld_);

		//弾を生成し、初期化
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Intialize(model_,bulletPosition_,bulletVelocity_);

		//弾を登録
		//bullet_ = newBullet;
		/*bullets_.reset(newBullet);*/
		bullets_.push_back(std::move(newBullet));
	}
}
