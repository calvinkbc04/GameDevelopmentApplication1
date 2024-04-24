#include "Player.h"
#include "../../Utility/InputControl.h"
#include "../../Utility/UserTemplate.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

Player::Player() :
	velocity(0.0f),
	animation_image(),
	animation_state(0),
	animation_count(0)
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	box_size = Vector2D(32.0f);
	location = Vector2D(320.0f, 240.0f);

	ResourceManager* rm = GetResourceManager();
	std::vector<int> tmp;
	tmp = rm->GetImages(Resource / Images / Tri - pilot / 1.png);
	animation_image.push_back(tmp[0]);
	tmp = rm->GetImages(Resource / Images / Tri - pilot / 2.png);
	animation_image.push_back(tmp[0]);

	image = animation_image[0];

	animation_count = 0;
	animation_state = 0;
}

void Player::Update()
{
	Movement();

	AnimationControl();
}

void Player::Draw() const
{
	__super::Draw();
}

void Player::Finalize()
{
	animation_image.clear();
}

void Player::Movement()
{
	float direction = 0.0f;
		if (InputControl::GetKey(KEY_INPUT_LEFT))
		{
			direction = -1.0f;
		}
		else if (InputControl::GetKey(KEY_INPUT_RIGHT))
		{
			direction = 1.0f;
		}

	if (direction != 0.0f)
	{
		float max_speed = Abs<float>((5.0f * 0.5 * direction));
		velocity.x += 0.5 * direction;
		velocity.x = Min<float>(Max<float>(velocity.x, -max_speed), max_speed);
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
	location += velocity;
}

void Player::AnimationControl()
[
	animation_count++;

	if (animation_count >= 30)
	{
		animation_count = 0;

		if (image == animation_image[0])
		{
			image = animation_image[1];
		}
		else
		{
			image = animation_image[0];
		}
	}
]