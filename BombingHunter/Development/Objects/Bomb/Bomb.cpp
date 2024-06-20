#include "Bomb.h"
#include "DxLib.h"
#include "../../Utility/InputControl.h"
#include "../../Objects/Player/Player.h"

//コンストラクタ
Bomb::Bomb() : animation_count(0), flip_flag(FALSE)
{
	for (int i = 0; i < 4; i++)
	{
		animation[i] = NULL;
	}
}

//デストラクタ
Bomb::~Bomb()
{

}

void Bomb::Initialize()
{
	type = 2.0f;

	//画像読み込み
	LoadImages();

	//エラーチェック
	if (animation[0] == -1)
	{
		throw("Bombの画像がありません\n");
	}
	
	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	box_size = 64.0f;

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(0.0f, 1.0f);
}

//更新処理
void Bomb::Update()
{

	//移動処理
	Movement();

	//アニメーション制御
	AnimationControl();
}

//描画処理
void Bomb::Draw() const
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

	//情報を基に画像を描画する
	DrawRotaGraphF(location.x, location.y, 1.0, radian, animation[0], TRUE, flip_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void Bomb::Finalize()
{
	UnloadImages();
}

//当たり判定通知処理
void Bomb::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	direction = 0.0f;
}

//オブジェクトタイプを取得する処理
float Bomb::GetObjectType()
{
	return type;
}

//移動処理
void Bomb::Movement()
{
	if (((location.y + direction.y) < box_size.y) ||
		(680.0f - box_size.y) < (location.y + direction.y))
	{
		direction = 0.0f;
	}

	//進行方向に向かって、位置座標を変更する
	location += direction;
}

//アニメーション制御
void Bomb::AnimationControl()
{
	//アニメーションカウントを加算する
	animation_count++;

	//30フレーム目に到達したら
	if (animation_count >= 30)
	{
		//カウントのリセット
		animation_count = 0;

		//画像の切替
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}


//すべてのボムの画像の読み込み
void Bomb::LoadImages()
{
	animation[0] = LoadGraph("Resource/images/Bomb.png");
	animation[1] = LoadGraph("Resource/images/Blast/1.png");
	animation[2] = LoadGraph("Resource/images/Blast/2.png");
	animation[3] = LoadGraph("Resource/images/Blast/3.png");
}

//すべてのボムの画像の削除
void Bomb::UnloadImages()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
}