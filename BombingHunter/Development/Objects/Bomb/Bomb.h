#pragma once

#include "../GameObject.h"


class Bomb : public GameObject
{
	int animation[4];		//アニメーション画像
	int animation_count;	//アニメーション時間
	int flip_flag;			//反転フラグ
	Vector2D direction;		//進行方向

public:
	Bomb();
	~Bomb();

	virtual void Initialize() override;		//初期化処理
	virtual void Update() override;			//更新処理
	virtual void Draw() const override;		//描画処理
	virtual void Finalize() override;		//終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

	Vector2D SetDirection(Vector2D p_velocity);

private:
	//移動処理
	void Movement();
	//アニメーション制御
	void AnimationControl();

private:

	//すべてのEnemyの画像の読み込み処理
	void LoadImages();
	//すべてのEnemyの画像の削除処理
	void UnloadImages();
};