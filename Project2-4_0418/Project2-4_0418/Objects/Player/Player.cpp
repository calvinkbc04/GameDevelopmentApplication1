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
	Movement();
}


//描画処理
void Player::Draw() const
{
	//ボックスの左上の座標
	Vector2D tl = this->location - (box_size / 2.0f);
	//ボックスの右下の座標
	Vector2D br = this->location + (box_size / 2.0f);

	//ボックスを描画
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

	//移動処理-------入力方向に加速
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		direction.x = -0.5f;														//移動方向を決定
		float max_speed = Abs<float>((5.0f * direction.x));							//最高速度
		velocity.x += direction.x;													//速度に加算
		velocity.x = Min<float>(Max<float>(velocity.x, -max_speed), max_speed);		//最高速度を超えないようにする処理
	}
	if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		direction.x = 0.5f;															//移動方向を決定
		float max_speed = Abs<float>((5.0f * direction.x));							//最高速度
		velocity.x += direction.x;													//速度に加算
		velocity.x = Min<float>(Max<float>(velocity.x, -max_speed), max_speed);		//最高速度を超えないようにする処理
	}
	if (InputControl::GetKeyDown(KEY_INPUT_DOWN))
	{
		direction.y = 2.0f;															//移動方向を決定
		float max_speed = Abs<float>((5.0f * direction.y));							//最高速度
		velocity.y += direction.y;													//速度に加算
		velocity.y = Min<float>(Max<float>(velocity.y, -max_speed), max_speed);		//最高速度を超えないようにする処理
	}
	if (InputControl::GetKeyDown(KEY_INPUT_UP))
	{
		direction.y = -7.5f;														//移動方向を決定
		float max_speed = Abs<float>((5.0f * direction.y));							//最高速度
		velocity.y += direction.y;													//速度に加算
		velocity.y = Min<float>(Max<float>(velocity.y, -max_speed), max_speed);		//最高速度を超えないようにする処理
	}
	else
	{
		//ボタンを押していない間減速する処理
		/*　1e-6f　＝　1が6個ある0の後ろに配置　＝　0.0000001	(ゼロに近い１) */
		if (velocity.x > 1e-6f)
		{
			float calc_speed = velocity.x - 0.1f;									//減速する処理
			velocity.x = Min<float>(Max<float>(calc_speed, 0.0f), velocity.x);		//最小速度（０）を下回らないようにする処理
		}
		else if (velocity.x < -1e-6f)
		{
			float calc_speed = velocity.x + 0.1f;									//減速する処理
			velocity.x = Min<float>(Max<float>(calc_speed, velocity.x),0.0f);		//最小速度（０）を下回らないようにする処理
		}

		if (location.y < 448.0f)
		{
			velocity.y += 0.1;
		}

		/*if (velocity.y > 1e-6f)
		{
			float calc_speed = velocity.y - 0.1f;									//減速する処理
			velocity.y = Min<float>(Max<float>(calc_speed, 0.0f), velocity.y);		//最小速度（０）を下回らないようにする処理
			velocity.y += 0.5f;
		}*/

		if (velocity.y < -1e-6f)
		{
			float calc_speed = velocity.y + 0.1f;									//減速する処理
			velocity.y = Min<float>(Max<float>(calc_speed, velocity.y), 0.0f);		//最小速度（０）を下回らないようにする処理
		}
		
	}

	//画面外行かないようにする処理
	if (location.x < (box_size.x / 2.0f))
	{
		velocity.x = 0.0f;
		location.x = box_size.x / 2.0f;		//はみ出ないようにする処理
	}
	else if (location.x > (640.0f - box_size.x / 2.0f))
	{
		velocity.x = 0.0f;
		location.x = 640.0f - box_size.x / 2.0f;	//はみ出ないようにする処理
	}
	if (location.y < (box_size.y / 2.0f))
	{
		velocity.y = 0.0f;
		location.y = box_size.y / 2.0f;		//はみ出ないようにする処理
	}
	else if (location.y > (480.0f - box_size.y / 2.0f))
	{
		velocity.y = 0.0f;
		location.y = 480.0f - box_size.y / 2.0f;	//はみ出ないようにする処理
	}
	

	location += velocity;

}