#pragma once

#include "../GameObject.h"

#define ANIM_MIN (2)
#define ANIM_MAX (5)
#define FLOOR_PATH (600.0f)		//床のｙ位置座標
#define FLY_PATH_1 (300.0f)		//飛ぶ敵のｙ位置座標１
#define FLY_PATH_2 (450.0f)		//飛ぶ敵のｙ位置座標２

class Enemy : public GameObject
{
private:
	int animation[5];		//アニメーション画像
	int animation_count;	//アニメーション時間
	int image_num;			//乱数を所持する変数
	Vector2D direction;		//進行方向

	//すべてのEnemyの画像の変数
	int E_Box[ANIM_MIN];
	int E_Fly[ANIM_MIN];
	int E_Metal[ANIM_MAX];
	int Harpy[ANIM_MIN];

public:
	Enemy();
	~Enemy();

	//初期化処理
	virtual void Initialize() override;
	//更新処理
	virtual void Update() override;
	//描画処理
	virtual void Draw() const override;
	//終了処理
	virtual void Finalize() override;
	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//移動処理
	void Movement();
	//アニメーション制御
	void AnimationControl();
	//生成するEnemyを取得する処理
	void GetSpawnEnemy();

public:

	//すべてのEnemyの画像の読み込み処理
	void LoadImages();

	//すべてのEnemyの画像の削除処理
	void UnloadImages();
};