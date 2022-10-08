#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"

class RailCamera{
public: //基本メンバ関数
	/// <param name="worldTransform">ワールドトランスフォーム</param>
	void Initialize(
		Vector3 position,
		Vector3 radian);
	void Update();

private://よく使うメンバ変数
	//ワールドトランスフォーム
	WorldTransform worldTransform_;

	//ビュープロジェクション
	ViewProjection viewProjection_;
};