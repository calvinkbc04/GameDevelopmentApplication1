#include "GameObject.h"
#include "DxLib.h"

GameObject::GameObject() : color(0x0), location(), box_size()
{

}

GameObject::~GameObject()
{

}


//初期化処理
void GameObject::Initialize()
{
	location = Vector2D(32.0f, 24.0f);

	box_size = Vector2D(32.0f, 24.0f);

	color = GetColor(0, 255, 0);
}


//更新処理
void GameObject::Update()
{
	Teleport();

	location += 0.7f;
}


//描画処理
void GameObject::Draw() const
{
	Vector2D tl = this->location - (this->box_size / 2.0f);
	Vector2D br = this->location + (this->box_size / 2.0f);

	DrawBoxAA(tl.x, tl.y, br.x, br.y, color, TRUE);
}


//ディストラクタ？？？？？
void GameObject::Finalize()
{

}


//座標設置処理
void GameObject::SetLocation(Vector2D location)
{
	this->location = location;
}


//座標を返す
Vector2D GameObject::GetLocation() const
{
	return this->location;
}


//大きさを返す
Vector2D GameObject::GetBoxSize() const
{
	return this->box_size;
}


//画面外に出たら画面の反対側に行く
Vector2D GameObject::Teleport()
{
	Vector2D tmp = this->location;

	//画面外に出たら反対側に送る処理
	if (tmp.x < 0.0f || 640.0f < tmp.x)
	{
		if (tmp.x < 0)
		{
			tmp.x = 640.0f;
		}
		else
		{
			tmp.x = 0.0f;
		}
		SetLocation(tmp);
	}

	if (tmp.y < 0.0f || 480.0f < tmp.y)
	{
		if (tmp.y < 0)
		{
			tmp.y = 480.0f;
		}
		else
		{
			tmp.y = 0.0f;
		}
	}

	SetLocation(tmp);

	return this->location;
}