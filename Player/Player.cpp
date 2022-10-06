#include "Player.h"
#include <cassert>

Player::Player()
{
}

Player::~Player()
{

}

///<summary>
///������
///<summary>
void Player::Intialize(Model* model) {
	//null�`�F�b�N
	assert(model);

	//�����o�ϐ��ɋL�^
	model_ = model;
	textureHandle_ = TextureManager::Load("mario.jpg");

	//�V���O���g���C���X�^���X
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();
}

///<summary>
///�X�V
///<summary>
void Player::Update() {

#ifdef  _DEBUG
#endif //  _DEBUG

	//�f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	Rotate();
	
	Move();

	Attack();

	//�e�X�V
	for(std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

	Transfer(worldTransform_,myMatrix_);

	//���L�����f�o�b�O�p�\��
	debugText_->SetPos(50, 150);
	debugText_->Printf(
		"PlaTrans:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);

	debugText_->SetPos(50, 180);
	debugText_->Printf(
		"PlaRota:(%f,%f,%f)", worldTransform_.rotation_.x, worldTransform_.rotation_.y, worldTransform_.rotation_.z);
}

///<summary>
///�`��
///<summary>
void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//�e�`��
	for(std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

///<summary>
///�ړ�
///<summary>
void Player::Move()
{
	//�L�����N�^�[�ړ�����
	//���E�_
	const float kMoveLimitX = 35.5f;
	const float kMoveLimitY = 18.5f;

	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,0 };

	if (input_->PushKey(DIK_LEFT)) {
		move.x -= 0.2f;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += 0.2f;
	}

	if (input_->PushKey(DIK_UP)) {
		move.y += 0.2f;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= 0.2f;
	}

	//�ړ��x�N�g�������Z
	worldTransform_.translation_ += move;

	//�ړ����̌��E�_�𒴂����Ȃ�����
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);

	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
}

///<summary>
///����
///<summary>
void Player::Rotate()
{
#pragma region ���g��]
	//�㔼�g��]
	if (input_->PushKey(DIK_U))
	{
		worldTransform_.rotation_.y -= 0.05f;
	}
	else if (input_->PushKey(DIK_I))
	{
		worldTransform_.rotation_.y += 0.05f;
	}

	//�����g��]
	if (input_->PushKey(DIK_J))
	{
		worldTransform_.rotation_.y -= 0.05f;
	}
	else if (input_->PushKey(DIK_K))
	{
		worldTransform_.rotation_.y += 0.05f;
	}
#pragma endregion
}

///<summary>
///�]��
///<summary>
void Player::Transfer(WorldTransform worldTransform,MyMatrix myMatrix)
{
	//matrix
	static Matrix4 scale;
	static  Matrix4 rota;
	static  Matrix4 translation;

	scale = myMatrix.MatrixScale(worldTransform.scale_);
	rota = myMatrix.MatrixRotationZ(worldTransform.rotation_);
	rota *= myMatrix.MatrixRotationX(worldTransform.rotation_);
	rota *= myMatrix.MatrixRotationY(worldTransform.rotation_);
	translation = myMatrix.MatrixTranslation(worldTransform.translation_);

	worldTransform_.matWorld_ = myMatrix.MatrixWorld(scale, rota, translation);

	//�]��
	worldTransform.TransferMatrix();
}

///<summary>
///�U��
///<summary>
void Player::Attack(){
	const float kBulletSpeed = 0.1f;
	Vector3 bulletVelocity_ = Vector3(0, 0, kBulletSpeed);

	if (input_->TriggerKey(DIK_SPACE))
	{
		//���x�x�N�g�������@�̌����ɂ��킹��
		bulletVelocity_ = myMatrix_.CrossVector(bulletVelocity_, worldTransform_.matWorld_);

		//�e�𐶐����A������
 		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Intialize(model_,worldTransform_.translation_,bulletVelocity_);

		//�e��o�^
		//bullet_ = newBullet;
		/*bullets_.reset(newBullet);*/
		bullets_.push_back(std::move(newBullet));
	}
}