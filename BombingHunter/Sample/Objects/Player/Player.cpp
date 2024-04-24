#include "Player.h"
#include "../../Utility/InputControl.h"
#include "../../Utility/UserTemplate.h"
#include "DxLib.h"

//コンストラクタ
Player::Player() : velocity(0.0f)
{
}

//デストラクタ
Player::~Player()
{

}

//初期化処理
void Player::Initialize()
{

	color = GetColor(255, 255, 255);

	box_size = Vector2D(32.0f);

	location = Vector2D(320.0f, 240.0f);
}

//更新処理
void Player::Update()
{
	//移動処理
	Movement();
}

//描画処理
void Player::Draw() const
{
	__super::Draw();
}

//終了時処理
void Player::Finalize()
{
	
}


//移動処理
void Player::Movement()
{
	float direction = 0.0f;

	//左右移動
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		direction += -1.0f;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		direction += 1.0f;
	}
	if (direction != 0.0f)
	{
		float max_speed = Abs<float>((5.0f * 0.5 * direction));
		velocity.x += 0.5 * direction;
		velocity.x = Min<float>(Max<float>(velocity.x, -max_speed),
			max_speed);
	}
	else
	{
		if (velocity.x < -1e-6f)
		{
			float calc_speed = velocity.x + 0.1;
			velocity.x = Min<float>(calc_speed, 0.0f);
		}
		else if (1e-6f < velocity.x)
		{
			float calc_speed = velocity.x - 0.1f;
			velocity.x = Max<float>(calc_speed, 0.0f);
		}
	}

	if (location.x < (box_size.x / 2.0f))
	{

		velocity.x = 0.0f;
		location.x = box_size.x / 2.0f;
	}
	else if ((640.0f - (box_size.x / 2.0f)) < location.x)
	{
		velocity.x = 0.0f;
		location.x = 640.0f - (box_size.x / 2.0f);
	}

	//現在の位置座標に速さを加算する
	location += velocity;
}
