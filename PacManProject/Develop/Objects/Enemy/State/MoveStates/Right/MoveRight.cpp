#include "MoveRight.h"

#include "DxLib.h"
#include "../../../Blinky.h"

MoveRightState::MoveRightState(class Enemy* e) : EnemyMoveStateBase(e)
{

}

MoveRightState::~MoveRightState()
{

}

void MoveRightState::Initialize()
{

}

void MoveRightState::Finalize()
{

}

void MoveRightState::Update()
{

}

void MoveRightState::Draw() const
{

}

eEnemyMoveState MoveRightState::GetState() const
{
	return eEnemyMoveState::RIGHT;
}