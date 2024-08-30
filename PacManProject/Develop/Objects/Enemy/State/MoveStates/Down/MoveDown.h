#pragma once
#include "../EnemyMoveStateBase.h"

class MoveDownState : public EnemyMoveStateBase
{
public:
	//コンストラクタ
	MoveDownState(class EnemyBase* e);

	//デストラクタ
	virtual ~MoveDownState();

public:
	//初期化処理
	virtual void Initialize() override;

	//終了処理
	virtual void Finalize() override;

	//更新処理
	virtual void Update() override;

	//描画処理
	virtual void Draw() const override;

	//現在のステート情報を取得する
	virtual eEnemyMoveState GetState() const override;
};