#include "RailCamera.h"

void RailCamera::Initialize(
	Vector3 position,
	Vector3 radian){
	//ワールドトランスフォーム初期設定
	worldTransform_.Initialize();
	worldTransform_.scale_ = Vector3(1, 1, 1);
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ =
		Vector3(
			XMConvertToRadians(radian.x),
			XMConvertToRadians(radian.y),
			XMConvertToRadians(radian.z));

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//シングルトンインスタンス
	debugText_ = DebugText::GetInstance();
}

void RailCamera::Update(){
	Move();

	UpdateWorldTransform();
	UpdateViewProjection();

	debugText_->SetPos(400,100);
	debugText_->Printf(
		"pos:%f,%f,%f",
		worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z
	);

	debugText_->SetPos(400,200);
	debugText_->Printf(
		"eye:%f,%f,%f",
		viewProjection_.eye.x,
		viewProjection_.eye.y,
		viewProjection_.eye.z
		);

	debugText_->SetPos(400,220);
	debugText_->Printf(
		"target:%f,%f,%f",
		viewProjection_.target.x,
		viewProjection_.target.y,
		viewProjection_.target.z
	);

	debugText_->SetPos(400,240);
	debugText_->Printf(
		"up:%f,%f,%f",
		viewProjection_.up.x,
		viewProjection_.up.y,
		viewProjection_.up.z
	);
}

void RailCamera::Move(){
	worldTransform_.translation_.z--;

	worldTransform_.rotation_.z += 0.1f;

	XMConvertToRadians(worldTransform_.rotation_.x);
	XMConvertToRadians(worldTransform_.rotation_.y);
	XMConvertToRadians(worldTransform_.rotation_.z);
}

void RailCamera::UpdateWorldTransform(){
	//matrix
	static Matrix4 scale;
	static  Matrix4 rota;
	static  Matrix4 translation;

	scale = myMatrix_.MatrixScale(worldTransform_.scale_);
	rota = myMatrix_.MatrixRotationZ(worldTransform_.rotation_);
	rota *= myMatrix_.MatrixRotationX(worldTransform_.rotation_);
	rota *= myMatrix_.MatrixRotationY(worldTransform_.rotation_);
	translation = myMatrix_.MatrixTranslation(worldTransform_.translation_);

	worldTransform_.matWorld_ = myMatrix_.MatrixWorld(scale, rota, translation);

	//転送
	worldTransform_.TransferMatrix();
}

void RailCamera::UpdateViewProjection(){

	viewProjection_.eye =
		Vector3(
			worldTransform_.matWorld_.m[0][3],
			worldTransform_.matWorld_.m[1][3],
			worldTransform_.matWorld_.m[2][3]
			);

	//ワールド前方ベクトル
	Vector3 forward(0,0,1);

	//レールカメラの回転を反映
	forward = Vector3Transform(forward,worldTransform_.matWorld_);

	//視点から前方に適当な距離進んだ位置が注視点
	viewProjection_.target = viewProjection_.eye + forward;


	//上方ベクトル
	Vector3 up(0,1,0);

	//レールカメラの回転を反映 (レールカメラの上方ベクトル)
	viewProjection_.up = Vector3Transform(up, worldTransform_.matWorld_);

	//ビュープロジェクションを更新
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
}