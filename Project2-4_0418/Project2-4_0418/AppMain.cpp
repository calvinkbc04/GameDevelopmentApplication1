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

	//�I�u�W�F�N�g��������
	GameObject* objects[2] = { nullptr, nullptr };
	objects[0] = new GameObject();
	objects[1] = new Player();

	//�I�u�W�F�N�g����������
	for (int i = 0; i < 2; i++)
	{
		objects[i]->Initialize();
	}

	//�`���ʐݒu����
	SetDrawScreen(DX_SCREEN_BACK);

	//���C������
	while (ProcessMessage() != -1)
	{
		InputControl::Update();

		for (int i = 0; i < 2; i++)
		{
			objects[i]->Update();
		}

		//�`���ʏ���������
		ClearDrawScreen();

		//�I�u�W�F�N�g�`�揈��
		for (int i = 0; i < 2; i++)
		{
			objects[i]->Draw();
		}

		//��ʔ��]
		ScreenFlip();

		//ESC�L�[��������I������
		if (InputControl::GetKeyUp(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}


	//�I�u�W�F�N�g���폜���鏈��
	for (int i = 0; i < 2; i++)
	{
		objects[i]->Finalize();
		delete objects[i];
	}

	DxLib_End();	//�I������

	return 0;
}
