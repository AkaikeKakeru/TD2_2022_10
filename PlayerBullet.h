#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "MyMatrix.h"
#include "DebugText.h"

///<summary>
///自キャラの弾
/// </summary>
class PlayerBullet{
public://基本的な関数
	void Intialize(Model* model,
		const Vector3& position,
		const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);

public://固有の関数
	void Transfer();
	bool IsDead() const { return isDead_; }

private://よく使う変数
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//ワールド変換行列
	MyMatrix myMatrix_;

	//デバッグテキスト
	DebugText* debugText_ = nullptr;

private://固有の変数
	//速度
	Vector3 velocity_;

	//寿命<frm>
	static const int32_t kLifeTime = 60 * 5;
	//デスタイマー
	int32_t deathtimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;
};