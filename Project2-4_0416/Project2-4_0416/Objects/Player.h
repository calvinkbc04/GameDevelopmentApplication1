#pragma once

#include "GameObject.h"

class Player : public GameObject
{
private:
	
public:
	Player();
	~Player() override;

	void Initialize() override;	//初期化処理
	void Update() override;		//更新処理
	void Draw() const override;	//描画処理
	void Finalize() override;	//ディストラクタ


private:
	void Movement();	//移動処理
	Vector2D Teleport();
};