#include "MoveUp.h"

#include "DxLib.h"
#include "../../../Blinky.h"

MoveUpState::MoveUpState(class Enemy* e) : EnemyMoveStateBase(e)
{

}

MoveUpState::~MoveUpState()
{

}

void MoveUpState::Initialize()
{

}

void MoveUpState::Finalize()
{

}

void MoveUpState::Update()
{

}

void MoveUpState::Draw() const
{

}

eEnemyMoveState MoveUpState::GetState() const
{
	return eEnemyMoveState::DOWN;
}