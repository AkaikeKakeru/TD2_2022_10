#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model) {
	//null�`�F�b�N
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("mario.jpg");

	worldTransform_.Initialize();
	worldTransform_.translation_.x -= 20;

	//�V���O���g���C���X�^���X
	input_ = Input::GetInstance();
}

void Player::Update() {
	//�f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	//�ړ�
	Move();
	//������΂�
	Blow();

	//�e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

	//�]��
	Transfer();
}

void Player::Draw(const ViewProjection viewProjection) {
	//�����`��
	model_->Draw(worldTransform_, viewProjection,textureHandle_);

	//�e�`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Player::Transfer() {
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

	//�]��
	worldTransform_.TransferMatrix();
}

void Player::Move() {
	//�o�ߎ���(�t���[��)
	static float time = 0.0f;

	//�����ꂽ��u���[�L�t���O
	if (input_->TriggerKey(DIK_SPACE)) {
		ifBrake = true;
	}

	//�u���[�L�t���O�����Ă���ړ���0
	if (ifBrake == true) {
		speed.x = 0.0f;
	}
	//�����ĂȂ��Ȃ獶�E�Ɉړ�
	else {
		//1F�o�ߖ���
		time += 1.0f;

		///�ɋ}�̂��鍶�E�^���ɂ�����
		///�����R�����ł�����Ƃ����Isin�g�������I
		//�c�Ă��Ƃ�X�����̈ړ����x���v�Z
		speed.x = sin(time / 20);

		//�t���[���P�ʂ� �w�莞�� + 1F �o�߂�����
		if (time > 120 + 1) {
			//0�ɖ߂�
			time = 0;
		}
	}

	//��{�̓I�u�W�F�N�g�̍��W���A�ړ��͕��ړ�����
	worldTransform_.translation_
		+= speed;
}

void Player::Blow() {
	//�e���x
	const float kBulletSpeed = 1.0f;
	//���x�x�N�g��
	Vector3 bulletVelocity_ = Vector3(0, 0, kBulletSpeed);
	//���ˈʒu
	Vector3 bulletPosition_ =
		Vector3(
			worldTransform_.matWorld_.m[3][0],
			worldTransform_.matWorld_.m[3][1],
			worldTransform_.matWorld_.m[3][2]
		);

	//������Ă���Ԃ̓u���E�t���O�𗧂Ă�
	if (input_->PushKey(DIK_SPACE)){
		ifBlow = true;
	}

	//�u���E�t���O�������Ă�Ȃ�
	if (ifBlow) {
		//������Ă��Ȃ��Ȃ�(�����ꂽ��)
		if (!input_->PushKey(DIK_SPACE))
		{
			//���x�x�N�g�������@�̌����ɂ��킹��
			bulletVelocity_ = myMatrix_.CrossVector(bulletVelocity_, worldTransform_.matWorld_);

			//�e�𐶐����A������
			std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
			newBullet->Intialize(model_, bulletPosition_, bulletVelocity_);

			//�e��o�^
			//bullet_ = newBullet;
			/*bullets_.reset(newBullet);*/
			bullets_.push_back(std::move(newBullet));

			//�u���[�L�t���O�ƁA�u���E�t���O��������
			ifBlow = false;
			ifBrake = false;
		}
	}
}
