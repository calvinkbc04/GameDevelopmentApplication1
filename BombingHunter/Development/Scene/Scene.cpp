#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Bomb/Bomb.h"
#include "../Objects/Bullet/Bullet.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "stdlib.h"
#include "time.h"

#define D_PIVOT_CENTER

//�R���X�g���N�^
Scene::Scene() : objects(), BackgroundImage(NULL), PLocX(NULL), PLocY(NULL), ELocX(NULL), ELocY(NULL)
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
		int enemy_type = rand() % 4 + 1;
		int spawn_side = rand() % 2 + 1;

		switch (enemy_type)
		{
		case 1:
			if (spawn_side == 1)
			{
				CreateObject<Enemy>(Vector2D(SPAWN_LEFT, FLOOR_PATH));
			}
			else
			{
				CreateObject<Enemy>(Vector2D(SPAWN_RIGHT, FLOOR_PATH));
			}
			break;

		case 2:
			if (spawn_side == 1)
			{
				CreateObject<Enemy>(Vector2D(SPAWN_LEFT, FLY_PATH_1));
			}
			else
			{
				CreateObject<Enemy>(Vector2D(SPAWN_RIGHT, FLY_PATH_1));
			}
			break;

		case 3:
			if (spawn_side == 1)
			{
				CreateObject<Enemy>(Vector2D(SPAWN_LEFT, FLY_PATH_2));
			}
			else
			{
				CreateObject<Enemy>(Vector2D(SPAWN_RIGHT, FLY_PATH_2));
			}
			break;

		case 4:
			if (spawn_side == 1)
			{
				CreateObject<Enemy>(Vector2D(SPAWN_LEFT, FLOOR_PATH));
			}
			else
			{
				CreateObject<Enemy>(Vector2D(SPAWN_RIGHT, FLOOR_PATH));
			}
			break;
		}
	}

	//�v���C���[�̍��W�擾
	PLocX = objects[0]->GetLocation().x;
	PLocY = objects[0]->GetLocation().y + 32.0f; // <----- "+ 32.0f" �͔��e���v���C���[�̉�����o���邽�߂̃I�t�Z�b�g

	//�X�y�[�X�L�[�������ꂽ��A�{�������������s��
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Bomb>(Vector2D(PLocX, PLocY));
	}

	for (int i = 1; i < objects.size(); i++)
	{
		if (objects[i]->GetObjectType() == 1.0)
		{
			ELocX = objects[i]->GetLocation().x;
			ELocY = objects[i]->GetLocation().y;
		}
		else
		{
			return;
		}
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
	/* type: Player = 0.0f, Enemy = 1.0f, Bomb = 2.0f, Bullet = 3.0f  */

	float aType = a->GetObjectType();
	float bType = b->GetObjectType();

	//�����I�u�W�F�N�g���m�ł���Ζ�������
	if (aType == bType)
	{
		return;
	}
	//aType���v���C���[��bType�����e�������ꍇ,��������
	else if (aType == 0.0f && bType == 2.0f || aType == 2.0f && bType == 0.0f)
	{
		return;
	}
	//aType���G��bType���e�������ꍇ,��������
	else if (aType == 1.0f && bType == 3.0f || aType == 3.0f && bType == 1.0f)
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