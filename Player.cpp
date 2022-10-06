#include "Player.h"
#include <cassert>

void Player::Initilize(Model* model)
{
	//nullチェック
	assert(model);

	model_ = model;
	worldTransform_.Initialize();
	//viewProjection_.Initialize();
}

void Player::Update()
{
}

void Player::Draw(const ViewProjection viewProjection)
{
	model_->Draw(worldTransform_,viewProjection);
}
