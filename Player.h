#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

#include "MyMatrix.h"
#include <math.h>
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

private://よく使う変数
	//モデル
	Model* model_ = nullptr;
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	//ViewProjection viewProjection_;

	MyMatrix myMatrix_;
};