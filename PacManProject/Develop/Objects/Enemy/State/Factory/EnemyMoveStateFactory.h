#pragma once

#include"../MoveStates/EnemyMoveStateBase.h"

class EnemyMoveStateFactory
{
private:
	static EnemyMoveStateFactory* instance;

	//シングルトン用　ここから
private:
	EnemyMoveStateFactory() = default;
	EnemyMoveStateFactory(const EnemyMoveStateFactory&) = default;
	EnemyMoveStateFactory& operator=(const EnemyMoveStateFactory&) = default;
	//シングルトン用　ここまで

private:
	class MoveDownState* move_down;
	class MoveLeftState* move_left;
	class MoveRightState* move_right;
	class MoveUpState* move_up;

private:
	void Initialize(class Enemy& enemy);

public:
	static EnemyMoveStateBase* Get(class Enemy& enemy, eEnemyMoveState state);
	static void Finalize();
};