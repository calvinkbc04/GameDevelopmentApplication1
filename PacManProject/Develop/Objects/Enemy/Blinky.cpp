#include "Blinky.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

Blinky::Blinky() : 
	move_animation(),
	dead_animation(),
	velocity(0.0),
	enemy_state(eEnemyState::HOUSE),
	now_direction(eEnemyMoveState::NONE),
	animation_time(0),
	animation_count(0),
	state_time(0),
	state_count(0),
	turf_location(),
	player_instance()
{

}

Blinky::~Blinky()
{

}

void Blinky::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 12, 12, 1, 32, 32);
	dead_animation = rm->GetImages("Resource/Images/eyes.png", 11, 11, 1, 32, 32);

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.hit_object_type.push_back(eObjectType::special);
	collision.radius = (D_OBJECT_SIZE) / 2.0f;

	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;
}

void Blinky::Update(float delta_second)
{

}

void Blinky::Draw(const Vector2D& screen_offset) const
{

}

void Blinky::Finalize()
{

}

void Blinky::OnHitCollision(GameObjectBase* hit_object)
{

}

eEnemyState Blinky::GetEnemyState() const
{
	return enemy_state;
}

void Blinky::GetPlayerInstance(Player* player)
{

}

Vector2D Blinky::SetNearTargetPanel()
{

}

void Blinky::Movement(float delta_second)
{
	switch (now_direction)
	{
	case eEnemyMoveState::UP:
		break;
	case eEnemyMoveState::RIGHT:
		break;
	case eEnemyMoveState::DOWN:
		break;
	case eEnemyMoveState::LEFT:
		break;
	default:
		break;
	}
}

void Blinky::HouseMovement(float delta_second)
{

}

void Blinky::RestMovement(float delta_second)
{

}

void Blinky::ChaseMovement(float delta_second)
{

}

void Blinky::ScaredMovement(float delta_second)
{

}

void Blinky::DeathMovement(float delta_second)
{

}

void Blinky::AnimationControl(float delta_second)
{
	switch (enemy_state)
	{
	case eEnemyState::HOUSE:
		break;
	case eEnemyState::REST:
		break;
	case eEnemyState::CHASE:
		break;
	case eEnemyState::SCARED:
		break;
	case eEnemyState::DIE:
		break;
	default:
		break;
	}
}