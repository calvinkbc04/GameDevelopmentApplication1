#include "Enemy.h"
#include "DxLib.h"
#include "stdlib.h"
#include "time.h"

Enemy::Enemy() : animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation[4] = NULL;

	for (int i = 0; i < ANIM_MIN; i++)
	{
		E_Box[i] = NULL;
		E_Fly[i] = NULL;
		E_Harpy[i] = NULL;
	}
	for (int i = 0; i < ANIM_MAX; i++)
	{
		E_Metal[i] = NULL;
	}
}

Enemy::~Enemy()
{

}

//����������
void Enemy::Initialize()
{
	//�摜�̓ǂݍ��ݏ���
	LoadImages();

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�G�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(1.0f, -0.0f);
}

//�X�V����
void Enemy::Update()
{

	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void Enemy::Draw() const
{
	//�摜���]�t���O
	int flip_flag = FALSE;

	//�i�s�����ɂ���āA���]��Ԃ����肷��
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//������Ƀn�R�G�摜��`�悷��
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void Enemy::Finalize()
{
	UnloadImages();
}

//�����蔻��ʒm����
void Enemy::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	direction = 0.0f;

	
}

//�ړ�����
void Enemy::Movement()
{
	//��ʒ[�ɓ��B������A�i�s�����𔽓]����
	if (((location.x + direction.x) < box_size.x) ||
		(640.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}

	if (((location.y + direction.y) < box_size.y) ||
		(480.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}

	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}

//�A�j���[�V��������
void Enemy::AnimationControl()
{
	//�A�j���[�V�����J�E���g�����Z����
	animation_count++;

	//30�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		//�摜�̐ؑ�
		if (animation[2] = NULL)
		{
			if (image == animation[0])
			{
				image = animation[1];
			}
			else
			{
				image = animation[0];
			}
		}
		else
		{
			/////////////
		}
		
	}
}


//��������Enemy���擾���鏈��
void Enemy::GetSpawnEnemy()
{
	srand((unsigned int)time(NULL));
	int num = rand() % 4 + 1;

	switch (num)
	{
	case 1:
		animation[0] = E_Box[0];
		animation[1] = E_Box[1];

	case 2:
		animation[0] = E_Fly[0];
		animation[1] = E_Fly[1];

	case 3:
		animation[0] = E_Harpy[0];
		animation[1] = E_Harpy[0];

	case 4:
		animation[0] = E_Metal[0];
		animation[1] = E_Metal[1];
		animation[2] = E_Metal[2];
		animation[3] = E_Metal[3];
		animation[4] = E_Metal[4];
	}

	if (num < 4)
	{
		animation[2] = NULL;
		animation[3] = NULL;
		animation[4] = NULL;
	}
	
}


//���ׂĂ�Enemy�̉摜�̓ǂݍ���
void Enemy::LoadImages()
{
	//�n�R�e�L
	E_Box[0] = LoadGraph("Resource/images/E_Box/1.png");
	E_Box[1] = LoadGraph("Resource/images/E_Box/2.png");
	//�n�l�e�L
	E_Fly[0] = LoadGraph("Resource/images/E_Fly/1.png");
	E_Fly[1] = LoadGraph("Resource/images/E_Fly/1.png");
	//���̃e�L
	E_Metal[0] = LoadGraph("Resource/images/E_Metal/1.png");
	E_Metal[1] = LoadGraph("Resource/images/E_Metal/2.png");
	E_Metal[2] = LoadGraph("Resource/images/E_Metal/3.png");
	E_Metal[3] = LoadGraph("Resource/images/E_Metal/4.png");
	E_Metal[4] = LoadGraph("Resource/images/E_Metal/5.png");
	//�n�[�s�[
	E_Harpy[0] = LoadGraph("Resource/images/E_Harpy/1.png");
	E_Harpy[1] = LoadGraph("Resource/images/E_Harpy/1.png");
}


//���ׂĂ�Enemy�̉摜�̍폜
void Enemy::UnloadImages()
{
	for (int i = 0; i < ANIM_MIN; i++)
	{
		DeleteGraph(E_Box[i]);
		DeleteGraph(E_Fly[i]);
		DeleteGraph(E_Harpy[i]);
	}
	for (int i = 0; i < ANIM_MAX; i++)
	{
		DeleteGraph(E_Metal[i]);
	}
}