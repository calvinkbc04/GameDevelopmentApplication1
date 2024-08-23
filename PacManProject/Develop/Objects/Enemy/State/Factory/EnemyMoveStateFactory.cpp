#include "EnemyMoveStateFactory.h"

#include "../MoveStates/Down/MoveDown.h"
#include "../MoveStates/Left/MoveLeft.h"
#include "../MoveStates/Right/MoveRight.h"
#include "../MoveStates/Up/MoveUp.h"

#include "../../Blinky.h"

EnemyMoveStateFactory* EnemyMoveStateFactory::instance = nullptr;

void EnemyMoveStateFactory::Initialize(class Enemy& enemy)
{
	down = new MoveDownState(&enemy);
	left = new MoveLeftState(&enemy);
	right = new MoveRightState(&enemy);
	up = new MoveUpState(&enemy);
}


void EnemyMoveStateFactory::Finalize()
{
	instance->down->Finalize();
	instance->left->Finalize();
	instance->right->Finalize();
	instance->up->Finalize();

	delete instance->down;
	delete instance->left;
	delete instance->right;
	delete instance->up;
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
	case eEnemyMoveState::DOWN:
		instance->down->Initialize();
		ret = instance->down;
		break;
		
	case eEnemyMoveState::LEFT:
		instance->left->Initialize();
		ret = instance->left;
		break;

	case eEnemyMoveState::RIGHT:
		instance->right->Initialize();
		ret = instance->right;
		break;

	case eEnemyMoveState::UP:
		instance->up->Initialize();
		ret = instance->up;
		break;

	case eEnemyMoveState::NONE:
	default:
		break;
	}

	return ret;
}