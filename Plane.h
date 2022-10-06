#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DebugText.h"

#include "MyMatrix.h"
#include <math.h>

class Plane {
public: //基本の関数	
	void Initialize(Model* model,
		const Vector3& position);
	void Update();
	void Draw(const ViewProjection viewProjection);

public: //固有の関数
	/// <summary>
	/// 座標更新
	/// </summary>
	void Transfer();

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

private://よく使う変数
		//モデル
	Model* model_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//ワールドトランスフォーム
	WorldTransform worldTransform_;

	MyMatrix myMatrix_;

	//デバッグテキスト
	DebugText* debugText_ = nullptr;

private: //固有の変数
};