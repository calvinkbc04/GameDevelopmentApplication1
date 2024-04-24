#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Player::Player()
{

}

Player::~Player()
{

}


//初期化処理
void Player::Initialize()
{
	location = Vector2D(320.0f, 240.0f);

	box_size = Vector2D(32.0f, 24.0f);

	color = GetColor(255, 0, 0);
}


//更新処理
void Player::Update()
{
	Teleport();
	Movement();
}


//描画処理
void Player::Draw() const
{
	Vector2D tl = this->location - (this->box_size / 2.0f);
	Vector2D br = this->location + (this->box_size / 2.0f);

	DrawBoxAA(tl.x, tl.y, br.x, br.y, color, TRUE);
}


//ディストラクタ
void Player::Finalize()
{

}


//移動処理
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

//画面外に出たら画面の反対側に行く
Vector2D Player::Teleport()
{
	Vector2D tmp = this->location;

	//画面外に出たら反対側に送る処理
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