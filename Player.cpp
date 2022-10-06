#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model) {
	//nullチェック
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("mario.jpg");

	worldTransform_.Initialize();
	worldTransform_.translation_.x -= 20;

	//シングルトンインスタンス
	input_ = Input::GetInstance();
}

void Player::Update() {
	//デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	//移動
	Move();
	//吹き飛ばし
	Blow();

	//弾更新
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

	//転送
	Transfer();
}

void Player::Draw(const ViewProjection viewProjection) {
	//自分描画
	model_->Draw(worldTransform_, viewProjection,textureHandle_);

	//弾描画
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Player::Transfer() {
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

void Player::Move() {
	//経過時間(フレーム)
	static float time = 0.0f;

	//押されたらブレーキフラグ
	if (input_->TriggerKey(DIK_SPACE)) {
		ifBrake = true;
	}

	//ブレーキフラグ立ってたら移動力0
	if (ifBrake == true) {
		speed.x = 0.0f;
	}
	//立ってないなら左右に移動
	else {
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

	//基本はオブジェクトの座標を、移動力分移動する
	worldTransform_.translation_
		+= speed;
}

void Player::Blow() {
	//弾速度
	const float kBulletSpeed = 1.0f;
	//速度ベクトル
	Vector3 bulletVelocity_ = Vector3(0, 0, kBulletSpeed);
	//発射位置
	Vector3 bulletPosition_ =
		Vector3(
			worldTransform_.matWorld_.m[3][0],
			worldTransform_.matWorld_.m[3][1],
			worldTransform_.matWorld_.m[3][2]
		);

	//押されている間はブロウフラグを立てる
	if (input_->PushKey(DIK_SPACE)){
		ifBlow = true;
	}

	//ブロウフラグが立ってるなら
	if (ifBlow) {
		//押されていないなら(離されたら)
		if (!input_->PushKey(DIK_SPACE))
		{
			//速度ベクトルを自機の向きにあわせる
			bulletVelocity_ = myMatrix_.CrossVector(bulletVelocity_, worldTransform_.matWorld_);

			//弾を生成し、初期化
			std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
			newBullet->Intialize(model_, bulletPosition_, bulletVelocity_);

			//弾を登録
			//bullet_ = newBullet;
			/*bullets_.reset(newBullet);*/
			bullets_.push_back(std::move(newBullet));

			//ブレーキフラグと、ブロウフラグを下げる
			ifBlow = false;
			ifBrake = false;
		}
	}
}
