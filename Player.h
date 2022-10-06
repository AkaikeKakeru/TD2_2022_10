#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Player {

public: //基本の関数	
	void Initilize(Model* model);
	void Update();
	void Draw(const ViewProjection viewProjection);

private://よく使う変数
	//モデル
	Model* model_ = nullptr;
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	//ViewProjection viewProjection_;
};