#pragma once

#include "../Utility/Vector2D.h"

class Player
{
private:
	Vector2D location;
	Vector2D direction;
	float radius;

public:
	Player();
	Player(float x, float y);
	Player(Vector2D location);
	~Player();

	void Update();		//更新処理
	void Draw() const;	//描画処理

	void SetLocation(float x, float y);		//座標設置
	void SetLocation(Vector2D location);	//座標設置
	Vector2D GetLocation() const;			//座標取得
	float GetRadius();						//大きさ

private:
	void Movement();	//移動処理
};