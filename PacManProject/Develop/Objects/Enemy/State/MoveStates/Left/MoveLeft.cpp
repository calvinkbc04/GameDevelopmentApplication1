#include "MoveLeft.h"

#include "DxLib.h"
#include "../../../Blinky.h"

MoveLeftState::MoveLeftState(class Enemy* e) : EnemyMoveStateBase(e)
{

}

MoveLeftState::~MoveLeftState()
{

}

void MoveLeftState::Initialize()
{

}

void MoveLeftState::Finalize()
{

}

void MoveLeftState::Update()
{

}

void MoveLeftState::Draw() const
{

}

eEnemyMoveState MoveLeftState::GetState() const
{
	return eEnemyMoveState::MOVE_LEFT;
}