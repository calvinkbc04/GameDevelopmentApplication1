#include "EnemyBase.h"
#include "../../../Utility/ResourceManager.h"
#include "DxLib.h"

EnemyBase::EnemyBase() : 
	move_animation(),
	dead_animation(),
	scared_animation(),
	velocity(0.0f),
	enemy_state(eEnemyState::HOUSE),
	now_direction(eEnemyMoveState::MOVE_DOWN),
	animation_time(0.0f),
	animation_count(0),
	state_time(0),
	state_count(0),
	turf_location(0.0f),
	player_instance(NULL)
{
	
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 12, 12, 1, 32, 32);
	dead_animation = rm->GetImages("Resource/Images/eyes.png", 11, 11, 1, 32, 32);

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	mobility = eMobilityType::Movable;
}

void EnemyBase::Update(float delta_second)
{
	// �G�̏�Ԃɂ���āA�����ς���
	switch (enemy_state)
	{
	case eEnemyState::HOUSE:
		HouseMovement(delta_second);
		AnimationControl(delta_second);
		break;

	case eEnemyState::REST:
		RestMovement(delta_second);
		AnimationControl(delta_second);
		break;

	case eEnemyState::CHASE:
		ChaseMovement(delta_second);
		AnimationControl(delta_second);
		break;

	case eEnemyState::SCARED:
		ScaredMovement(delta_second);
		AnimationControl(delta_second);
		break;

	case eEnemyState::DIE:
		DeathMovement(delta_second);
		AnimationControl(delta_second);
		break;
	}
}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

void EnemyBase::Finalize()
{
	move_animation.clear();
	dead_animation.clear();
}

void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	// ���������A�I�u�W�F�N�g���ǂ�������
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// �����蔻������擾���āA�J�v�Z��������ʒu�����߂�
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// �ŋߖT�_�����߂�
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Enemy����near_point�ւ̕����x�N�g�����擾
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// �߂荞�񂾍���
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diff�̕������߂�
		location += dv.Normalize() * diff;


	}
}

eEnemyState EnemyBase::GetEnemyState() const
{
	return enemy_state;
}

void EnemyBase::GetPlayerInstance(Player* player)
{

}

Vector2D EnemyBase::SetNearTargetPanel()
{

}

void EnemyBase::HouseMovement(float delta_second)
{
	switch (now_direction)
	{
	case eEnemyMoveState::MOVE_UP:
		break;
	case eEnemyMoveState::MOVE_RIGHT:
		break;
	case eEnemyMoveState::MOVE_DOWN:
		break;
	case eEnemyMoveState::MOVE_LEFT:
		break;
	default:
		break;
	}
}

void EnemyBase::RestMovement(float delta_second)
{
	switch (now_direction)
	{
	case eEnemyMoveState::MOVE_UP:
		break;
	case eEnemyMoveState::MOVE_RIGHT:
		break;
	case eEnemyMoveState::MOVE_DOWN:
		break;
	case eEnemyMoveState::MOVE_LEFT:
		break;
	default:
		break;
	}
}

void EnemyBase::ChaseMovement(float delta_second)
{
	switch (now_direction)
	{
	case eEnemyMoveState::MOVE_UP:
		break;
	case eEnemyMoveState::MOVE_RIGHT:
		break;
	case eEnemyMoveState::MOVE_DOWN:
		break;
	case eEnemyMoveState::MOVE_LEFT:
		break;
	default:
		break;
	}
}

void EnemyBase::ScaredMovement(float delta_second)
{
	switch (now_direction)
	{
	case eEnemyMoveState::MOVE_UP:
		break;
	case eEnemyMoveState::MOVE_RIGHT:
		break;
	case eEnemyMoveState::MOVE_DOWN:
		break;
	case eEnemyMoveState::MOVE_LEFT:
		break;
	default:
		break;
	}
}

void EnemyBase::DeathMovement(float delta_second)
{
	switch (now_direction)
	{
	case eEnemyMoveState::MOVE_UP:
		break;
	case eEnemyMoveState::MOVE_RIGHT:
		break;
	case eEnemyMoveState::MOVE_DOWN:
		break;
	case eEnemyMoveState::MOVE_LEFT:
		break;
	default:
		break;
	}
}

void EnemyBase::AnimationControl(float delta_second)
{
	switch (enemy_state)
	{
	case eEnemyState::HOUSE:
	case eEnemyState::REST:
	case eEnemyState::CHASE:

		break;

	case eEnemyState::SCARED:

		break;

	case eEnemyState::HOUSE:DIE:

		break;
	}
}