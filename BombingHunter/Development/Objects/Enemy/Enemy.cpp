#include "Enemy.h"
#include "DxLib.h"
#include "stdlib.h"
#include "time.h"


Enemy::Enemy() : animation_count(0), image_num(0), direction(0.0f)
{
	//animation配列とE_Metal配列の初期化
	for (int i = 0; i < ANIM_MAX; i++)
	{
		animation[i] = NULL;
		E_Metal[i] = NULL;
	}
	//列が２ある配列の初期化
	for (int i = 0; i < ANIM_MIN; i++)
	{
		E_Box[i] = NULL;
		E_Fly[i] = NULL;
		Harpy[i] = NULL;
	}
}

Enemy::~Enemy()
{

}

//初期化処理
void Enemy::Initialize()
{

	//画像の読み込み処理
	LoadImages();

	type = 1.0f;

	active_state = true;

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("敵の画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	box_size = 64.0f;

	GetSpawnEnemy();

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	if (location.x > 450.0f)
	{
		direction = Vector2D(-1.0f, -0.0f);
	}
	else
	{
		direction = Vector2D(1.0f, -0.0f);
	}
	
}

//更新処理
void Enemy::Update()
{

	//移動処理
	Movement();

	//アニメーション制御
	AnimationControl();
}

//描画処理
void Enemy::Draw() const
{
	//画像反転フラグ
	int flip_flag = FALSE;

	//進行方向によって、反転状態を決定する
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//情報を基に敵画像を描画する
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void Enemy::Finalize()
{
	UnloadImages();
}

//当たり判定通知処理
void Enemy::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	active_state = false;
}

//移動処理
void Enemy::Movement()
{
	//画面端に到達したら、進行方向を反転する
	if (((location.x + direction.x) < box_size.x) ||
		(940.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}

	if (((location.y + direction.y) < box_size.y) ||
		(720.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}

	//進行方向に向かって、位置座標を変更する
	location += direction;
}


//アニメーション制御
void Enemy::AnimationControl()
{
	//アニメーションカウントを加算する
	animation_count++;

	//30フレーム目に到達したら
	if (animation_count >= 30)
	{
		//カウントのリセット
		animation_count = 0;

		//画像の切替
		//画像が2枚しかない場合
		if (animation[2] == NULL)
		{
			if (image == animation[0])
			{
				image = animation[1];
			}
			else
			{
				image = animation[0];
			}
		}
		else
		{
			image_num++;
			
			if (image_num > 4)
			{
				image_num = 0;
			}
			else
			{
				image = animation[image_num];
			}
		}	
	}
}


//生成するEnemyを取得する処理
void Enemy::GetSpawnEnemy()
{
	animation[2] = NULL;
	animation[3] = NULL;
	animation[4] = NULL;

	if (this->location.y == FLY_PATH_1)
	{
		animation[0] = E_Fly[0];
		animation[1] = E_Fly[1];
	}
	else if (this->location.y == FLY_PATH_2)
	{
		animation[0] = Harpy[0];
		animation[1] = Harpy[1];
	}
	else
	{
		srand((unsigned int)time(NULL));
		int num = rand() % 2 + 1;

		switch (num)
		{
		case 1:
			animation[0] = E_Box[0];
			animation[1] = E_Box[1];
			break;

		case 2:
			animation[0] = E_Metal[0];
			animation[1] = E_Metal[1];
			animation[2] = E_Metal[2];
			animation[3] = E_Metal[3];
			animation[4] = E_Metal[4];
			break;
		}
	}
}

//すべてのEnemyの画像の読み込み
void Enemy::LoadImages()
{
	//ハコテキ
	E_Box[0] = LoadGraph("Resource/images/E_Box/1.png");
	E_Box[1] = LoadGraph("Resource/images/E_Box/2.png");
	//ハネテキ
	E_Fly[0] = LoadGraph("Resource/images/E_Fly/1.png");
	E_Fly[1] = LoadGraph("Resource/images/E_Fly/2.png");
	//金のテキ
	E_Metal[0] = LoadGraph("Resource/images/E_Metal/1.png");
	E_Metal[1] = LoadGraph("Resource/images/E_Metal/2.png");
	E_Metal[2] = LoadGraph("Resource/images/E_Metal/3.png");
	E_Metal[3] = LoadGraph("Resource/images/E_Metal/4.png");
	E_Metal[4] = LoadGraph("Resource/images/E_Metal/5.png");
	//ハーピー
	Harpy[0] = LoadGraph("Resource/images/Harpy/1.png");
	Harpy[1] = LoadGraph("Resource/images/Harpy/2.png");
}


//すべてのEnemyの画像の削除
void Enemy::UnloadImages()
{
	for (int i = 0; i < ANIM_MIN; i++)
	{
		DeleteGraph(E_Box[i]);
		DeleteGraph(E_Fly[i]);
		DeleteGraph(Harpy[i]);
	}
	for (int i = 0; i < ANIM_MAX; i++)
	{
		DeleteGraph(E_Metal[i]);
	}
}