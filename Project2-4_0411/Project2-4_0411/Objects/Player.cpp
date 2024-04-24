#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Player::Player() : location(), direction(0.0f), radius(15.0f)
{
}

Player::Player(float x, float y) : location(x, y), direction(0.0f), radius(15.0f)
{
}

Player::Player(Vector2D location) : direction(0.0f), radius(15.0f)
{
	this->location = location;
}

Player::~Player()
{

}


//�v���C���[�X�V����
void Player::Update()
{
	Movement();
}


//�v���C���[�`�揈��
void Player::Draw() const
{
	DrawCircleAA(location.x, location.y, radius, 50, GetColor(255, 255, 255), TRUE);
}


//�v���C���[�̍��W�z�u����
void Player::SetLocation(float x, float y)
{
	SetLocation(Vector2D(x, y));
}

void Player::SetLocation(Vector2D location)
{
	this->location = location;
}


//�v���C���[�̍��W��Ԃ�
Vector2D Player::GetLocation() const
{
	return location;
}


//�v���C���[�̑傫����Ԃ�
float Player::GetRadius()
{
	return radius;
}


//�ړ�����
void Player::Movement()
{
	direction.y = 0.0f;
	direction.x = 0.0f;

	if (InputControl::GetKey(KEY_INPUT_UP))
	{
		direction.y = -1.0;
	}
	if (InputControl::GetKey(KEY_INPUT_DOWN))
	{
		direction.y = 1.0;
	}
	if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		direction.x = 1.0;
	}
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		direction.x = -1.0;
	}

	location += direction;

}