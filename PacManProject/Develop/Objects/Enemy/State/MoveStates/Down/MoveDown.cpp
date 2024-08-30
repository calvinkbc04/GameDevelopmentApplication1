#include "MoveDown.h"

#include "DxLib.h"
#include "../../../Blinky.h"

MoveDownState::MoveDownState(class EnemyBase* e) : 
	EnemyMoveStateBase(e)
{

}

MoveDownState::~MoveDownState()
{

}

void MoveDownState::Initialize()
{
	this->enemy->velocity.y -= 15.0f;
}

void MoveDownState::Finalize()
{

}

void MoveDownState::Update()
{

}

void MoveDownState::Draw() const
{

}

eEnemyMoveState MoveDownState::GetState() const
{
	return eEnemyMoveState::MOVE_DOWN;
}