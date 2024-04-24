#pragma once

#include "../Utility/Vector2D.h"

class GameObject
{
protected:
	unsigned int color;
	Vector2D location;
	Vector2D box_size;

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();	//初期化処理
	virtual void Update();		//更新処理
	virtual void Draw() const;	//描画処理
	virtual void Finalize();	//ディストラクタ

public:
	void SetLocation(Vector2D location);	//座標設置
	Vector2D GetLocation() const;			//座標を返す
	Vector2D GetBoxSize() const;			//大きさを返す
	Vector2D Teleport();
};