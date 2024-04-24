#include "DxLib.h"
#include "Utility/InputControl.h"
#include "Objects/GameObject.h"
#include "Objects/Player.h"
#include <math.h>

//Project1110����Q��--------�����蔻��m�F
bool HitCheck(GameObject* PL, GameObject* OL)
{
	//object1�̍��W���l��
	int obj1_x = OL->GetLocation().x;
	int obj1_y = OL->GetLocation().y;

	//object2�̍��W���l��
	int obj2_x = PL->GetLocation().x;
	int obj2_y = PL->GetLocation().y;

	//�I�u�W�F�N�g�̑傫�����l��
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
	GameObject* object1 = NULL;	//�V�����I�u�W�F�N�g�𐶐����鏀��
	GameObject* object2 = new Player();			//�V�����v���C���[�I�u�W�F�N�g�𐶐�

	object2->Initialize();	//�v���C���[�I�u�W�F�N�g�̏�����

	//���C�����[�v
	while (ProcessMessage() != -1)
	{
		InputControl::Update();	//���͍X�V

		//object1��NULL���������V����object1�����
		if (object1 == NULL)
		{
			object1 = new GameObject();	//�V�����I�u�W�F�N�g�𐶐�����
			object1->Initialize();	//�I�u�W�F�N�g�̏�����
		}

		object2->Update();	//�v���C���[�I�u�W�F�N�g�̍X�V

		ClearDrawScreen();	//�`���ʏ�����

		//object1��NULL����Ȃ��������̏���
		if (object1 != NULL)
		{
			object1->Update();

			//�{�[�����o�[�ɐG�ꂽ������鏈��
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

		object2->Draw();	//�v���C���[�I�u�W�F�N�g�̕`��

		ScreenFlip();	//��ʔ��]
	}

	delete object1;	//�I�u�W�F�N�g���폜����
	delete object2;	//�v���C���[�I�u�W�F�N�g���폜����

	DxLib_End();	//�I������

	return 0;
}
