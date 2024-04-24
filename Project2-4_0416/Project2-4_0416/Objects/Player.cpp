#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Player::Player()
{

}

Player::~Player()
{

}


//����������
void Player::Initialize()
{
	location = Vector2D(320.0f, 240.0f);

	box_size = Vector2D(32.0f, 24.0f);

	color = GetColor(255, 0, 0);
}


//�X�V����
void Player::Update()
{
	Teleport();
	Movement();
}


//�`�揈��
void Player::Draw() const
{
	Vector2D tl = this->location - (this->box_size / 2.0f);
	Vector2D br = this->location + (this->box_size / 2.0f);

	DrawBoxAA(tl.x, tl.y, br.x, br.y, color, TRUE);
}


//�f�B�X�g���N�^
void Player::Finalize()
{

}


//�ړ�����
void Player::Movement()
{

	Vector2D direction = Vector2D(0.0f);

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

//��ʊO�ɏo�����ʂ̔��Α��ɍs��
Vector2D Player::Teleport()
{
	Vector2D tmp = this->location;

	//��ʊO�ɏo���甽�Α��ɑ��鏈��
	if (tmp.x < 0.0f || 640.0f < tmp.x)
	{
		if (tmp.x < 0)
		{
			tmp.x = 640.0f;
		}
		else
		{
			tmp.x = 0.0f;
		}
		SetLocation(tmp);
	}

	if (tmp.y < 0.0f || 480.0f < tmp.y)
	{
		if (tmp.y < 0)
		{
			tmp.y = 480.0f;
		}
		else
		{
			tmp.y = 0.0f;
		}
	}

	SetLocation(tmp);

	return this->location;
}