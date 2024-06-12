#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Bomb/Bomb.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "stdlib.h"
#include "time.h"

#define D_PIVOT_CENTER

//�R���X�g���N�^
Scene::Scene() : objects(), BackgroundImage(NULL), PLocX(NULL), PLocY(NULL)
{

}

//�f�X�g���N�^
Scene::~Scene()
{
	//�Y��h�~
	Finalize();
}

//����������
void Scene::Initialize()
{
	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 200.0f));

	BackgroundImage = LoadGraph("Resource/images/Background2.png");

	if (BackgroundImage == -1)
	{
		throw("�w�i�̉摜������܂���\n");
	}
}

//�X�V����
void Scene::Update()
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[j]);
		}
	}

	//Z�L�[����������A�G�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		//�����_���̐��l���o��
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

	//�v���C���[�̍��W�擾
	PLocX = objects[0]->GetLocation().x;
	PLocY = objects[0]->GetLocation().y + 65.0f;

	//�X�y�[�X�L�[�������ꂽ��A�{�������������s��
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Bomb>(Vector2D(PLocX, PLocY));
	}
}

//�`�揈��
void Scene::Draw() const
{
	//�w�i�摜��`��
	DrawExtendGraph(0, 0, WINDOW_MAX_WIDTH, WINDOW_MAX_HEIGHT, BackgroundImage, FALSE);

	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//�I��������
void Scene::Finalize()
{
	//���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}

	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//���I�z��̉��
	objects.clear();

	DeleteGraph(BackgroundImage);
}

#ifdef D_PIVOT_CENTER

//�����蔻��`�F�b�N�����i��`�̒��S�œ����蔻������j
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//�����I�u�W�F�N�g���m���m�F
	if (a == b)
	{
		return;
	}
	else
	{
		//�Q�̃I�u�W�F�N�g�̋������擾
		Vector2D diff = a->GetLocation() - b->GetLocation();

		//�Q�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
		Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

		//�������傫�����傫���ꍇ�AHit����Ƃ���
		if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
		{
			//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
			a->OnHitCollision(b);
			b->OnHitCollision(a);
		}
	}
	
	
	/****************************************************************************************************************************/

	////�Q�̃I�u�W�F�N�g�̋������擾
	//Vector2D diff = a->GetLocation() - b->GetLocation();

	////�Q�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	//Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;


	//if (a == b)
	//{
	//	return;
	//}
	//else
	//{
	//	//�������傫�����傫���ꍇ�AHit����Ƃ���
	//	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	//	{
	//		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
	//		a->OnHitCollision(b);
	//		b->OnHitCollision(a);
	//	}
	//}

}

#else

//�����蔻��`�F�b�N�����i���㒸�_�̍��W���瓖���蔻��v�Z���s���j
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//�E�����_���W���擾����
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//��`A�Ƌ�`B�̈ʒu�֌W�𒲂ׂ�
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//�I�u�W�F�N�g�ɑ΂���Hit�����ʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif // D_PIVOT_CENTER