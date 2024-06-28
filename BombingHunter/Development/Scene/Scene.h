#pragma once

#include <vector>
#include <string>
#include "../Objects/GameObject.h"

#define WINDOW_MAX_WIDTH (960)	//横画面サイズ
#define WINDOW_MAX_HEIGHT (720)	//縦画面サイズ

class Scene
{
private:
	std::vector<GameObject*> objects;
	int BackgroundImage;	//背景画像
	int BackgroundMusic;	//背景音楽
	float PLocX;	//プレイヤーのx座標を取得する変数
	float PLocY;	//プレイヤーのy座標を取得する変数
	float ELocX;	//敵のx座標を取得する変数
	float ELocY;	//敵のy座標を取得する変数
	int enemy_spawn_rate;	//敵が生成するまでのフレームを数える変数
	int bullet_spawn_rate;	//弾が生成するまでのフレームを数える変数

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

	//ランダムな数値を生成する処理
	int CreateRandNum(int r_num);

	//敵を生成する処理
	void EnemySpawn();
	//ボムを生成する処理
	void BombSpawn();
	//弾を生成する処理
	void BulletSpawn();
	//オブジェクトを削除する処理
	void DeleteObject();
	

private:
	//当たり判定チェック処理
	void HitCheckObject(GameObject* a, GameObject* b);

	//オブジェクト生成処理
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		//指定したクラスを生成する
		T* new_instance = new T();
		//GameObjectクラスを継承しているか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("ゲームオブジェクトが生成されませんでした");
		}

		//初期情報の設定
		new_object->SetLocation(location);
		
		//初期化処理
		new_object->Initialize();
		

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}
};