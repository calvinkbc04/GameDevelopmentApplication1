#include "EnemyMoveStateFactory.h"

#include "../MoveStates/Down/MoveDown.h"
#include "../MoveStates/Left/MoveLeft.h"
#include "../MoveStates/Right/MoveRight.h"
#include "../MoveStates/Up/MoveUp.h"

#include "../../Blinky.h"

EnemyMoveStateFactory* EnemyMoveStateFactory::instance = nullptr;

void EnemyMoveStateFactory::Initialize(class Enemy& enemy)
{
	move_down = new MoveDownState(&enemy);
	move_left = new MoveLeftState(&enemy);
	move_right = new MoveRightState(&enemy);
	move_up = new MoveUpState(&enemy);
}


void EnemyMoveStateFactory::Finalize()
{
	instance->move_down->Finalize();
	instance->move_left->Finalize();
	instance->move_right->Finalize();
	instance->move_up->Finalize();

	delete instance->move_down;
	delete instance->move_left;
	delete instance->move_right;
	delete instance->move_up;
}


EnemyMoveStateBase* EnemyMoveStateFactory::Get(class Enemy& enemy, eEnemyMoveState state)
{
	if (instance == nullptr)
	{
		instance = new EnemyMoveStateFactory();
		instance->Initialize(enemy);
	}

	EnemyMoveStateBase* ret = nullptr;
	switch (state)
	{
	case eEnemyMoveState::MOVE_DOWN:
		instance->move_down->Initialize();
		ret = instance->move_down;
		break;
		
	case eEnemyMoveState::MOVE_LEFT:
		instance->move_left->Initialize();
		ret = instance->move_left;
		break;

	case eEnemyMoveState::MOVE_RIGHT:
		instance->move_right->Initialize();
		ret = instance->move_right;
		break;

	case eEnemyMoveState::MOVE_UP:
		instance->move_up->Initialize();
		ret = instance->move_up;
		break;

	case eEnemyMoveState::NONE:
	default:
		break;
	}

	return ret;
}