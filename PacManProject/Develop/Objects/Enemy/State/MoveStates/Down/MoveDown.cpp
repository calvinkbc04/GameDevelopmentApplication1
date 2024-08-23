#include "MoveDown.h"

#include "DxLib.h"
#include "../../../Blinky.h"

MoveDownState::MoveDownState(class Enemy* e) : EnemyMoveStateBase(e)
{

}

MoveDownState::~MoveDownState()
{

}

void MoveDownState::Initialize()
{

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
	return eEnemyMoveState::DOWN;
}