#include "Player.h"
#include "../../Utility/InputControl.h"
#include "../../Utility/UserTemplate.h"
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
	color = GetColor(255, 255, 255);

	box_size = Vector2D(32.0f);
	
	location = Vector2D(320.0f, 240.0f);
}


//�X�V����
void Player::Update()
{
	Movement();
}


//�`�揈��
void Player::Draw() const
{
	//�{�b�N�X�̍���̍��W
	Vector2D tl = this->location - (box_size / 2.0f);
	//�{�b�N�X�̉E���̍��W
	Vector2D br = this->location + (box_size / 2.0f);

	//�{�b�N�X��`��
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

	//�ړ�����-------���͕����ɉ���
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		direction.x = -0.5f;														//�ړ�����������
		float max_speed = Abs<float>((5.0f * direction.x));							//�ō����x
		velocity.x += direction.x;													//���x�ɉ��Z
		velocity.x = Min<float>(Max<float>(velocity.x, -max_speed), max_speed);		//�ō����x�𒴂��Ȃ��悤�ɂ��鏈��
	}
	if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		direction.x = 0.5f;															//�ړ�����������
		float max_speed = Abs<float>((5.0f * direction.x));							//�ō����x
		velocity.x += direction.x;													//���x�ɉ��Z
		velocity.x = Min<float>(Max<float>(velocity.x, -max_speed), max_speed);		//�ō����x�𒴂��Ȃ��悤�ɂ��鏈��
	}
	if (InputControl::GetKeyDown(KEY_INPUT_DOWN))
	{
		direction.y = 2.0f;															//�ړ�����������
		float max_speed = Abs<float>((5.0f * direction.y));							//�ō����x
		velocity.y += direction.y;													//���x�ɉ��Z
		velocity.y = Min<float>(Max<float>(velocity.y, -max_speed), max_speed);		//�ō����x�𒴂��Ȃ��悤�ɂ��鏈��
	}
	if (InputControl::GetKeyDown(KEY_INPUT_UP))
	{
		direction.y = -7.5f;														//�ړ�����������
		float max_speed = Abs<float>((5.0f * direction.y));							//�ō����x
		velocity.y += direction.y;													//���x�ɉ��Z
		velocity.y = Min<float>(Max<float>(velocity.y, -max_speed), max_speed);		//�ō����x�𒴂��Ȃ��悤�ɂ��鏈��
	}
	else
	{
		//�{�^���������Ă��Ȃ��Ԍ������鏈��
		/*�@1e-6f�@���@1��6����0�̌��ɔz�u�@���@0.0000001	(�[���ɋ߂��P) */
		if (velocity.x > 1e-6f)
		{
			float calc_speed = velocity.x - 0.1f;									//�������鏈��
			velocity.x = Min<float>(Max<float>(calc_speed, 0.0f), velocity.x);		//�ŏ����x�i�O�j�������Ȃ��悤�ɂ��鏈��
		}
		else if (velocity.x < -1e-6f)
		{
			float calc_speed = velocity.x + 0.1f;									//�������鏈��
			velocity.x = Min<float>(Max<float>(calc_speed, velocity.x),0.0f);		//�ŏ����x�i�O�j�������Ȃ��悤�ɂ��鏈��
		}

		if (location.y < 448.0f)
		{
			velocity.y += 0.1;
		}

		/*if (velocity.y > 1e-6f)
		{
			float calc_speed = velocity.y - 0.1f;									//�������鏈��
			velocity.y = Min<float>(Max<float>(calc_speed, 0.0f), velocity.y);		//�ŏ����x�i�O�j�������Ȃ��悤�ɂ��鏈��
			velocity.y += 0.5f;
		}*/

		if (velocity.y < -1e-6f)
		{
			float calc_speed = velocity.y + 0.1f;									//�������鏈��
			velocity.y = Min<float>(Max<float>(calc_speed, velocity.y), 0.0f);		//�ŏ����x�i�O�j�������Ȃ��悤�ɂ��鏈��
		}
		
	}

	//��ʊO�s���Ȃ��悤�ɂ��鏈��
	if (location.x < (box_size.x / 2.0f))
	{
		velocity.x = 0.0f;
		location.x = box_size.x / 2.0f;		//�͂ݏo�Ȃ��悤�ɂ��鏈��
	}
	else if (location.x > (640.0f - box_size.x / 2.0f))
	{
		velocity.x = 0.0f;
		location.x = 640.0f - box_size.x / 2.0f;	//�͂ݏo�Ȃ��悤�ɂ��鏈��
	}
	if (location.y < (box_size.y / 2.0f))
	{
		velocity.y = 0.0f;
		location.y = box_size.y / 2.0f;		//�͂ݏo�Ȃ��悤�ɂ��鏈��
	}
	else if (location.y > (480.0f - box_size.y / 2.0f))
	{
		velocity.y = 0.0f;
		location.y = 480.0f - box_size.y / 2.0f;	//�͂ݏo�Ȃ��悤�ɂ��鏈��
	}
	

	location += velocity;

}