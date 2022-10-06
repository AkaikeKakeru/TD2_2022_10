#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Input.h"
#include "DebugText.h"

#include "MyMatrix.h"
#include <math.h>

#include "PlayerBullet.h"

class Player {

public: //基本の関数	
	void Initilize(Model* model);
	void Update();
	void Draw(const ViewProjection viewProjection);

public: //固有の関数
	/// <summary>
	/// 座標更新
	/// </summary>
	void Transfer();

	/// <summary>
	/// 横移動
	/// </summary>
	void Move();

	/// <summary>
	/// 吹き飛ばす
	/// </summary>
	void Blow();

private://よく使う変数
	//モデル
	Model* model_ = nullptr;
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	//ViewProjection viewProjection_;
	//インプット
	Input* input_ = nullptr;

	MyMatrix myMatrix_;

	//デバッグテキスト
	DebugText* debugText_ = nullptr;

private: //固有の変数
	//弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;


	//速度ベクトル
	Vector3 speed = { 0,0,0 };
	
	//ブレーキ
	bool ifBrake = false;
};