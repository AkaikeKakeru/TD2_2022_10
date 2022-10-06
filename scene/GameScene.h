#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"

#include "directxmath.h"
#include <random>

#include <memory>
#include <list>
using namespace DirectX;

#include "Player.h"
#include "Plane.h"

#define PI = XM_PI

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
  /// <summary>
  /// コンストクラタ
  /// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	//モデル
	Model* model_ = nullptr;

	//ビュープロジェクション
	ViewProjection viewProjection_;

	//カメラ上方向の角度
	float viewAngle = 0.0f;

	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	//デバッグカメラ有効
	bool isDebugCameraActive_ = false;

	//自機
	std::unique_ptr<Player> player_;
	Model* modelPlayer_ = nullptr;

	//物
	//std::unique_ptr<Plane> plane_;
	//Model* modelPlane_ = nullptr;

	std::list<std::unique_ptr<Plane>> planes_;
	Model* modelPlane_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};