#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Skydome {
public: //基本的なメンバ関数
	void Initialize();
	void Update();
	void Draw();

private: //よく使うメンバ変数
	//ワールドトランスフォーム
	WorldTransform worldTransform_;

	//モデル
	Model* model_ = nullptr;
};