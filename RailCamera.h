#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"

#include "MyMatrix.h"
#include "DebugText.h"

class RailCamera{
public: //基本メンバ関数
	/// <param name="worldTransform">ワールドトランスフォーム</param>
	void Initialize(
		Vector3 position,
		Vector3 radian);
	void Update();

public: // 固有のメンバ関数

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	/// <summary>
	/// 座標更新
	/// </summary>
	void UpdateWorldTransform();

	/// <summary>
	/// ビュープロジェクション更新
	/// </summary>
	void UpdateViewProjection();

private://よく使うメンバ変数
	//ワールドトランスフォーム
	WorldTransform worldTransform_;

	//ビュープロジェクション
	ViewProjection viewProjection_;

	MyMatrix myMatrix_;

	//デバッグテキスト
	DebugText* debugText_ = nullptr;
};