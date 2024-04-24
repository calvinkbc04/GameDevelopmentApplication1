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

	Player* player = new Player();	//�V�����v���C���[�I�u�W�F�N�g�𐶐�

	SetDrawScreen(DX_SCREEN_BACK);


	//���C�����[�v
	while (ProcessMessage() != -1)
	{
		InputControl::Update();	//���͍X�V

		player->Update();	//�v���C���[�X�V����

		Vector2D tmp = player->GetLocation();

		//��ʊO�ɏo���甽�Α��ɑ��鏈��
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

		player->SetLocation(tmp);	//�v���C���[�̍��W�z�u

		ClearDrawScreen();	//�`���ʏ�����

		player->Draw();	//�v���C���[�̕`��

		ScreenFlip();	//��ʔ��]


		//ESC�L�[��������v���O�������I������
		if (InputControl::GetKeyUp(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}

	delete player;	//�v���C���[�I�u�W�F�N�g���폜����

	DxLib_End();

	return 0;
}