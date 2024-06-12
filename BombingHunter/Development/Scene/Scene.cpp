#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Bomb/Bomb.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "stdlib.h"
#include "time.h"

#define D_PIVOT_CENTER

//コンストラクタ
Scene::Scene() : objects(), BackgroundImage(NULL), PLocX(NULL), PLocY(NULL)
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

	BackgroundImage = LoadGraph("Resource/images/Background2.png");

	if (BackgroundImage == -1)
	{
		throw("背景の画像がありません\n");
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

	//Zキーを押したら、敵を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		//ランダムの数値を出す
		srand((unsigned int)time(NULL));
		int num = rand() % 4 + 1;

		switch (num)
		{
		case 1:
			CreateObject<Enemy>(Vector2D(100.0f, FLOOR_PATH));
			break;

		case 2:
			CreateObject<Enemy>(Vector2D(100.0f, FLY_PATH_1));
			break;

		case 3:
			CreateObject<Enemy>(Vector2D(100.0f, FLY_PATH_2));
			break;

		case 4:
			CreateObject<Enemy>(Vector2D(100.0f, FLOOR_PATH));
			break;
		}
	}

	//プレイヤーの座標取得
	PLocX = objects[0]->GetLocation().x;
	PLocY = objects[0]->GetLocation().y + 65.0f;

	//スペースキーが押されたら、ボム生成処理を行う
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Bomb>(Vector2D(PLocX, PLocY));
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

#ifdef D_PIVOT_CENTER

//当たり判定チェック処理（矩形の中心で当たり判定を取る）
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//同じオブジェクト同士か確認
	if (a == b)
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
	
	
	/****************************************************************************************************************************/

	////２つのオブジェクトの距離を取得
	//Vector2D diff = a->GetLocation() - b->GetLocation();

	////２つのオブジェクトの当たり判定の大きさを取得
	//Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;


	//if (a == b)
	//{
	//	return;
	//}
	//else
	//{
	//	//距離より大きさが大きい場合、Hit判定とする
	//	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	//	{
	//		//当たったことをオブジェクトに通知する
	//		a->OnHitCollision(b);
	//		b->OnHitCollision(a);
	//	}
	//}

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