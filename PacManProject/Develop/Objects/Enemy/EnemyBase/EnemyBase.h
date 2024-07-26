#pragma once

#include "../../GameObject.h"
#include "../../Utility/StageData.h"
#include "../../Player/Player.h"

// 状況状態
enum eEnemyState
{
	HOUSE,
	REST,
	CHASE,
	SCARED,
	DIE,
};

class EnemyBase : public GameObject
{
private:
	// 進行方向状態
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};

protected:

	std::vector<int> move_animation;		// 移動のアニメーション
	std::vector<int> dead_animation;		// 死亡のアニメーション
	Vector2D velocity;					// 移動量
	eEnemyState enemy_state;			// 敵の状態
	eDirectionState now_direction;			// 現在進行方向状態
	float animation_time;				// アニメーション時間
	int animation_count;				// アニメーション添字
	int state_time;				// 状態時間
	int state_count;			// 状態添字
	Vector2D turf_location;			// 縄張りの位置
	Player* player_instance;		// プレイヤーの情報を持つ変数

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	eEnemyState GetEnemyState() const;

protected:
	void GetPlayerInstance(Player*);
	Vector2D SetNearTargetPanel();
	void Movement(float);
	virtual void HouseMovement(float);
	virtual void RestMovement(float);
	virtual void ChaseMovement(float);
	virtual void ScaredMovement(float);
	void DeathMovement(float);

	void AnimationControl(float delta_second);
};