#pragma once
#include "../Enum/EnemyMoveState.h"

/// <summary>
/// 敵の移動状態のベースクラス
/// </summary>
class EnemyMoveStateBase
{
protected:
	//敵情報
	class EnemyBase* enemy;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="e">敵の情報</param>
	EnemyMoveStateBase(class EnemyBase* e) : enemy(e)
	{
	}

	//デストラクタ
	virtual ~EnemyMoveStateBase() = default;

public:
	//初期化処理関数
	virtual void Initialize() = 0;

	//終了処理関数
	virtual void Finalize() = 0;

	//更新処理関数
	virtual void Update() = 0;

	//描画処理関数
	virtual void Draw() const = 0;

	//移動状態の取得
	virtual eEnemyMoveState GetState() const = 0;
};