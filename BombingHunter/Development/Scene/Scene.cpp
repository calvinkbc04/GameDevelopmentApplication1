#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Bomb/Bomb.h"
#include "../Objects/Bullet/Bullet.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "stdlib.h"
#include "time.h"

#define D_PIVOT_CENTER

//コンストラクタ
Scene::Scene() : objects(), BackgroundImage(NULL), BackgroundMusic(NULL), PLocX(NULL), PLocY(NULL), ELocX(NULL), ELocY(NULL), enemy_spawn_rate(0), bullet_spawn_rate(0)
{

}

//デストラクタ
Scene::~Scene()
{
	//忘れ防止
	Finalize();
}

//初期化処理
void Scene::Initialize()
{
	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(320.0f, 200.0f));

	//背景画像
	BackgroundImage = LoadGraph("Resource/images/Background2.png");
	//背景音楽
	BackgroundMusic = PlaySoundFile("Resource/audio/BGM_arrows.wav", DX_PLAYTYPE_BACK);

	if (BackgroundImage == -1)
	{
		throw("背景の画像がありません\n");
	}

	if (CheckSoundFile() == -1)
	{
		throw("背景の音楽がありません\n");
	}
}

//更新処理
void Scene::Update()
{
	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//オブジェクト同士の当たり判定チェック
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//当たり判定チェック処理
			HitCheckObject(objects[i], objects[j]);
		}
	}

	//削除するオブジェクトがあるか確認する
	DeleteObject();

	enemy_spawn_rate++;

	if (enemy_spawn_rate >= 75)	// <----- "enemy_spawn_rate >= ()" は敵の生成速度
	{
		//カウントのリセット
		enemy_spawn_rate = 0;

		EnemySpawn();
	}

	//スペースキーが押されたら、ボム生成処理を行う
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		BombSpawn();
	}

	bullet_spawn_rate++;

	if (bullet_spawn_rate == 30)
	{
		bullet_spawn_rate = 0;

		BulletSpawn();
	}
}

//描画処理
void Scene::Draw() const
{
	//背景画像を描画
	DrawExtendGraph(0, 0, WINDOW_MAX_WIDTH, WINDOW_MAX_HEIGHT, BackgroundImage, FALSE);

	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//終了時処理
void Scene::Finalize()
{
	//動的配列が空なら処理を終了する
	if (objects.empty())
	{
		return;
	}

	//各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//動的配列の解放
	objects.clear();

	DeleteGraph(BackgroundImage);
}

//フロートをランダムに生成する（0も含まれる）
int Scene::CreateRandNum(int r_num)
{
	int r_num_holder = GetRand(r_num);
	
	return r_num_holder;
}


//敵を生成する処理
void Scene::EnemySpawn()
{
	//ランダムの数値を出す
	srand((unsigned int)time(NULL));
	//生成する敵のタイプを決める値をランダムに生成
	int enemy_type = CreateRandNum(3);
	//生成する敵の初期座標を決める値をランダムに生成
	int spawn_side = CreateRandNum(1);

	switch (enemy_type)
	{
	case 0:
		//箱敵
		if (spawn_side == 0)
		{
			CreateObject<Enemy>(Vector2D(SPAWN_LEFT, FLOOR_PATH));
		}
		else
		{
			CreateObject<Enemy>(Vector2D(SPAWN_RIGHT, FLOOR_PATH));
		}
		break;

	case 1:
		//羽敵
		if (spawn_side == 0)
		{
			CreateObject<Enemy>(Vector2D(SPAWN_LEFT, FLY_PATH_1));
		}
		else
		{
			CreateObject<Enemy>(Vector2D(SPAWN_RIGHT, FLY_PATH_1));
		}
		break;

	case 2:
		//ハーピー
		if (spawn_side == 0)
		{
			CreateObject<Enemy>(Vector2D(SPAWN_LEFT, FLY_PATH_2));
		}
		else
		{
			CreateObject<Enemy>(Vector2D(SPAWN_RIGHT, FLY_PATH_2));
		}
		break;

	case 3:
		//鉄敵
		if (spawn_side == 0)
		{
			CreateObject<Enemy>(Vector2D(SPAWN_LEFT, FLOOR_PATH));
		}
		else
		{
			CreateObject<Enemy>(Vector2D(SPAWN_RIGHT, FLOOR_PATH));
		}
		break;
	}
}

//ボムを生成する処理
void Scene::BombSpawn()
{
	//プレイヤーの座標取得
	PLocX = objects[0]->GetLocation().x;
	PLocY = objects[0]->GetLocation().y + 32.0f; // <----- "+ 32.0f" は爆弾がプレイヤーの下から出るためのオフセット

	CreateObject<Bomb>(Vector2D(PLocX, PLocY))->SetDirection(objects[0]->GetDirection());
}

//弾を生成する処理
void Scene::BulletSpawn()
{
	for (int i = 1; i < objects.size(); i++)
	{
		//オブジェクトタイプが敵であれば処理を続ける
		if (objects[i]->GetObjectType() == 1.0)
		{
			//敵の座標を取得
			ELocX = objects[i]->GetLocation().x;
			ELocY = objects[i]->GetLocation().y;

			//敵が弾を打つか打たないかを決める値をランダムに生成
			int shot_pcntg = CreateRandNum(15);
			if (shot_pcntg == 0)
			{
				CreateObject<Bullet>(Vector2D(ELocX, ELocY));
			}
		}
	}
}

//オブジェクトを削除する処理
void Scene::DeleteObject()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetActive())
		{
			//active_stateがtrueであれば何もしない
		}
		else
		{
			//オブジェクトを削除すればリストを詰める
			objects.erase(objects.begin() + i);
			i--;
		}
	}
}


#ifdef D_PIVOT_CENTER

//当たり判定チェック処理（矩形の中心で当たり判定を取る）
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	/********* type: Player = 0.0f, Enemy = 1.0f, Bomb = 2.0f, Bullet = 3.0f  ************/

	float aType = a->GetObjectType();
	float bType = b->GetObjectType();

	//同じオブジェクト同士であれば無視する
	if (aType == bType)
	{
		return;
	}
	//aTypeがプレイヤーでbTypeが爆弾だった場合,無視する
	else if (aType == 0.0f && bType == 2.0f || aType == 2.0f && bType == 0.0f)
	{
		return;
	}
	//aTypeが敵でbTypeが弾だった場合,無視する
	else if (aType == 1.0f && bType == 3.0f || aType == 3.0f && bType == 1.0f)
	{
		return;
	}
	//aTypeが爆弾でbTypeが弾だった場合,無視する
	else if (aType == 2.0f && bType == 3.0f || aType == 3.0f && bType == 2.0f)
	{
		return;
	}
	else
	{
		//２つのオブジェクトの距離を取得
		Vector2D diff = a->GetLocation() - b->GetLocation();

		//２つのオブジェクトの当たり判定の大きさを取得
		Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

		//距離より大きさが大きい場合、Hit判定とする
		if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
		{
			//当たったことをオブジェクトに通知する
			a->OnHitCollision(b);
			b->OnHitCollision(a);
		}
	}
}

#else

//当たり判定チェック処理（左上頂点の座標から当たり判定計算を行う）
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//右下頂点座標を取得する
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//矩形Aと矩形Bの位置関係を調べる
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//オブジェクトに対してHit判定を通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif // D_PIVOT_CENTER