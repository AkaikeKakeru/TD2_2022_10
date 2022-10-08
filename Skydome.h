#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "MyMatrix.h"

class Skydome {
public: //基本的なメンバ関数
	void Initialize(Model* model);
	void Update();
	void Draw(const ViewProjection viewProjection);

public: //固有のメンバ関数
		/// <summary>
		/// 座標更新
		/// </summary>
	void Transfer();

private: //よく使うメンバ変数
	//ワールドトランスフォーム
	WorldTransform worldTransform_;

	//モデル
	Model* model_ = nullptr;

	MyMatrix myMatrix_;
};