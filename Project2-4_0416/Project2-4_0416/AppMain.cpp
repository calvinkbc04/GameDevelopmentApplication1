#include "DxLib.h"
#include "Utility/InputControl.h"
#include "Objects/GameObject.h"
#include "Objects/Player.h"
#include <math.h>

//Project1110から参照--------当たり判定確認
bool HitCheck(GameObject* PL, GameObject* OL)
{
	//object1の座標を獲得
	int obj1_x = OL->GetLocation().x;
	int obj1_y = OL->GetLocation().y;

	//object2の座標を獲得
	int obj2_x = PL->GetLocation().x;
	int obj2_y = PL->GetLocation().y;

	//オブジェクトの大きさを獲得
	Vector2D size = OL->GetBoxSize();

	//32.0f, 24.0f
	//powf(obj2_x - obj1_x, 2.0f) <= (obj2_x + 20.0f) && powf(obj2_y - obj1_y, 2.0f) <= (obj2_y - 20.0f)
	if (powf(obj2_x - obj1_x, 2.0f) <= (obj2_x + 60.0f) && powf(obj2_y - obj1_y, 2.0f) <= (obj2_y - 60.0f))
	{
		return TRUE;
	}
	return FALSE;
}


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);
	GameObject* object1 = NULL;	//新しいオブジェクトを生成する準備
	GameObject* object2 = new Player();			//新しいプレイヤーオブジェクトを生成

	object2->Initialize();	//プレイヤーオブジェクトの初期化

	//メインループ
	while (ProcessMessage() != -1)
	{
		InputControl::Update();	//入力更新

		//object1がNULLだった時新しいobject1を作る
		if (object1 == NULL)
		{
			object1 = new GameObject();	//新しいオブジェクトを生成する
			object1->Initialize();	//オブジェクトの初期化
		}

		object2->Update();	//プレイヤーオブジェクトの更新

		ClearDrawScreen();	//描画画面初期化

		//object1がNULLじゃなかった時の処理
		if (object1 != NULL)
		{
			object1->Update();

			//ボールがバーに触れたら消える処理
			if (HitCheck(object2, object1) == TRUE)
			{

				delete object1;
				object1 = NULL;
			}
			else
			{
				object1->Draw();
			}
		}

		object2->Draw();	//プレイヤーオブジェクトの描画

		ScreenFlip();	//画面反転
	}

	delete object1;	//オブジェクトを削除する
	delete object2;	//プレイヤーオブジェクトを削除する

	DxLib_End();	//終了処理

	return 0;
}
