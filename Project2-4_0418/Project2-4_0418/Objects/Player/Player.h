#pragma once

#include "../GameObject.h"

class Player : public GameObject
{
private:
	Vector2D velocity;	//移動速度

public:
	Player();
	virtual ~Player();

	virtual void Initialize();	//初期化処理
	virtual void Update();		//更新処理
	virtual void Draw() const;	//描画処理
	virtual void Finalize();	//ディストラクタ


private:
	void Movement();	//移動処理
};