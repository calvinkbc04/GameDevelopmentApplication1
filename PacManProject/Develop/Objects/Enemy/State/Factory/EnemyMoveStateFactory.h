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
	class MoveDownState* down;
	class MoveLeftState* left;
	class MoveRightState* right;
	class MoveUpState* up;

private:
	void Initialize(class Enemy& enemy);

public:
	static EnemyMoveStateBase* Get(class Enemy& enemy, eEnemyMoveState state);
	static void Finalize();
};