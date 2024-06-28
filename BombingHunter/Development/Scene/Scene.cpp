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
Scene::Scene() : objects(), BackgroundImage(NULL), BackgroundMusic(NULL), PLocX(NULL), PLocY(NULL), ELocX(NULL), ELocY(NULL), enemy_spawn_rate(0), bullet_spawn_rate(0)
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

	//�w�i�摜
	BackgroundImage = LoadGraph("Resource/images/Background2.png");
	//�w�i���y
	BackgroundMusic = PlaySoundFile("Resource/audio/BGM_arrows.wav", DX_PLAYTYPE_BACK);

	if (BackgroundImage == -1)
	{
		throw("�w�i�̉摜������܂���\n");
	}

	if (CheckSoundFile() == -1)
	{
		throw("�w�i�̉��y������܂���\n");
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

	//�폜����I�u�W�F�N�g�����邩�m�F����
	DeleteObject();

	enemy_spawn_rate++;

	if (enemy_spawn_rate >= 75)	// <----- "enemy_spawn_rate >= ()" �͓G�̐������x
	{
		//�J�E���g�̃��Z�b�g
		enemy_spawn_rate = 0;

		EnemySpawn();
	}

	//�X�y�[�X�L�[�������ꂽ��A�{�������������s��
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		BombSpawn();
	}

	bullet_spawn_rate++;

	if (bullet_spawn_rate == 30)
	{
		bullet_spawn_rate = 0;

		BulletSpawn();
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

//�t���[�g�������_���ɐ�������i0���܂܂��j
int Scene::CreateRandNum(int r_num)
{
	int r_num_holder = GetRand(r_num);
	
	return r_num_holder;
}


//�G�𐶐����鏈��
void Scene::EnemySpawn()
{
	//�����_���̐��l���o��
	srand((unsigned int)time(NULL));
	//��������G�̃^�C�v�����߂�l�������_���ɐ���
	int enemy_type = CreateRandNum(3);
	//��������G�̏������W�����߂�l�������_���ɐ���
	int spawn_side = CreateRandNum(1);

	switch (enemy_type)
	{
	case 0:
		//���G
		if (spawn_side == 0)
		{
			CreateObject<Enemy>(Vector2D(SPAWN_LEFT, FLOOR_PATH));
		}
		else
		{
			CreateObject<Enemy>(Vector2D(SPAWN_RIGHT, FLOOR_PATH));
		}
		break;

	case 1:
		//�H�G
		if (spawn_side == 0)
		{
			CreateObject<Enemy>(Vector2D(SPAWN_LEFT, FLY_PATH_1));
		}
		else
		{
			CreateObject<Enemy>(Vector2D(SPAWN_RIGHT, FLY_PATH_1));
		}
		break;

	case 2:
		//�n�[�s�[
		if (spawn_side == 0)
		{
			CreateObject<Enemy>(Vector2D(SPAWN_LEFT, FLY_PATH_2));
		}
		else
		{
			CreateObject<Enemy>(Vector2D(SPAWN_RIGHT, FLY_PATH_2));
		}
		break;

	case 3:
		//�S�G
		if (spawn_side == 0)
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

//�{���𐶐����鏈��
void Scene::BombSpawn()
{
	//�v���C���[�̍��W�擾
	PLocX = objects[0]->GetLocation().x;
	PLocY = objects[0]->GetLocation().y + 32.0f; // <----- "+ 32.0f" �͔��e���v���C���[�̉�����o�邽�߂̃I�t�Z�b�g

	CreateObject<Bomb>(Vector2D(PLocX, PLocY))->SetDirection(objects[0]->GetDirection());
}

//�e�𐶐����鏈��
void Scene::BulletSpawn()
{
	for (int i = 1; i < objects.size(); i++)
	{
		//�I�u�W�F�N�g�^�C�v���G�ł���Ώ����𑱂���
		if (objects[i]->GetObjectType() == 1.0)
		{
			//�G�̍��W���擾
			ELocX = objects[i]->GetLocation().x;
			ELocY = objects[i]->GetLocation().y;

			//�G���e��ł��ł��Ȃ��������߂�l�������_���ɐ���
			int shot_pcntg = CreateRandNum(15);
			if (shot_pcntg == 0)
			{
				CreateObject<Bullet>(Vector2D(ELocX, ELocY));
			}
		}
	}
}

//�I�u�W�F�N�g���폜���鏈��
void Scene::DeleteObject()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetActive())
		{
			//active_state��true�ł���Ή������Ȃ�
		}
		else
		{
			//�I�u�W�F�N�g���폜����΃��X�g���l�߂�
			objects.erase(objects.begin() + i);
			i--;
		}
	}
}


#ifdef D_PIVOT_CENTER

//�����蔻��`�F�b�N�����i��`�̒��S�œ����蔻������j
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	/********* type: Player = 0.0f, Enemy = 1.0f, Bomb = 2.0f, Bullet = 3.0f  ************/

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
	//aType�����e��bType���e�������ꍇ,��������
	else if (aType == 2.0f && bType == 3.0f || aType == 3.0f && bType == 2.0f)
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