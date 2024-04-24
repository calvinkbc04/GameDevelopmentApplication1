#include "DxLib.h"
#include "Utility/InputControl.h"
#include "Objects/Player.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	Player* player = new Player();	//新しいプレイヤーオブジェクトを生成

	SetDrawScreen(DX_SCREEN_BACK);


	//メインループ
	while (ProcessMessage() != -1)
	{
		InputControl::Update();	//入力更新

		player->Update();	//プレイヤー更新処理

		Vector2D tmp = player->GetLocation();

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
			player->SetLocation(tmp);
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

		player->SetLocation(tmp);	//プレイヤーの座標配置

		ClearDrawScreen();	//描画画面初期化

		player->Draw();	//プレイヤーの描画

		ScreenFlip();	//画面反転


		//ESCキー押したらプログラムを終了する
		if (InputControl::GetKeyUp(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}

	delete player;	//プレイヤーオブジェクトを削除する

	DxLib_End();

	return 0;
}