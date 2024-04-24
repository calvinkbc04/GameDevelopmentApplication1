#include "DxLib.h"
#include "Utility/InputControl.h"
#include "Objects/Player/Player.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//オブジェクト生成処理
	GameObject* objects[2] = { nullptr, nullptr };
	objects[0] = new GameObject();
	objects[1] = new Player();

	//オブジェクト初期化処理
	for (int i = 0; i < 2; i++)
	{
		objects[i]->Initialize();
	}

	//描画画面設置処理
	SetDrawScreen(DX_SCREEN_BACK);

	//メイン処理
	while (ProcessMessage() != -1)
	{
		InputControl::Update();

		for (int i = 0; i < 2; i++)
		{
			objects[i]->Update();
		}

		//描画画面初期化処理
		ClearDrawScreen();

		//オブジェクト描画処理
		for (int i = 0; i < 2; i++)
		{
			objects[i]->Draw();
		}

		//画面反転
		ScreenFlip();

		//ESCキー押したら終了処理
		if (InputControl::GetKeyUp(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}


	//オブジェクトを削除する処理
	for (int i = 0; i < 2; i++)
	{
		objects[i]->Finalize();
		delete objects[i];
	}

	DxLib_End();	//終了処理

	return 0;
}
