#pragma once

#include "../Utility/Vector2D.h"
#include "typeinfo"

#define D_PIVOT_CENTER		//座標の原点を画像の中心にする

//ゲームオブジェクト基底クラス
class GameObject
{
protected:
	Vector2D location;	//位置情報
	Vector2D box_size;		//大きさ
	double radian;		//向き
	int image;			//描画する画像
	int sound;			//再生する画像

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();	//初期化処理
	virtual void Update();		//更新処理
	virtual void Draw() const;	//描画処理
	virtual void Finalize();	//終了時処理


	//////////////////////////////////////////////////////////////////////////////
	void method() {
		//型情報の取得
		const type_info& id = typeid(*this);
		this->subMethod();
	}
	////////////////////////////////////////////////////////////////////////////////

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object);

	//位置所法取得処理
	Vector2D GetLocation() const;
	//位置情報変更処理
	void SetLocation(const Vector2D& location);
	//当たり判定の大きさを取得する
	Vector2D GetBoxSize() const;

	/////////////////////////////////////////////////////////////////////////////
protected:
	virtual void subMethod() = 0;
	/////////////////////////////////////////////////////////////////////////////
};