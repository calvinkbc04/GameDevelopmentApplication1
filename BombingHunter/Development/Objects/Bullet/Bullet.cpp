#include "Bullet.h"
#include "DxLib.h"

//�R���X�g���N�^
Bullet::Bullet() : animation_count(0), bullet_rate(0), flip_flag(FALSE)
{
	for (int i = 0; i < 4; i++)
	{
		animation[i] = NULL;
	}
}

//�f�X�g���N�^
Bullet::~Bullet()
{

}

void Bullet::Initialize()
{
	type = 3.0f;

	//�摜�ǂݍ���
	LoadImages();

	//�G���[�`�F�b�N
	if (animation[0] == -1)
	{
		throw("Bullet�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	direction = Vector2D(0.0f, -1.0f);
}

//�X�V����
void Bullet::Update()
{

	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimationControl();

	CheckTypeAndFrameCnt();
}

//�`�揈��
void Bullet::Draw() const
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

	//������ɉ摜��`�悷��
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void Bullet::Finalize()
{
	UnloadImages();
}

//�����蔻��ʒm����
void Bullet::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	direction = 0.0f;
}

//�I�u�W�F�N�g�^�C�v���擾���鏈��
float Bullet::GetObjectType()
{
	return type;
}

//�ړ�����
void Bullet::Movement()
{
	//��ʒ[�ɓ��B������A�i�s�����𔽓]����
	if (((location.x + direction.x) < box_size.x) ||
		(940.0f - box_size.x) < (location.x + direction.x))
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
void Bullet::AnimationControl()
{
	//�A�j���[�V�����J�E���g�����Z����
	animation_count++;

	//30�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		//�摜�̐ؑ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}


//���ׂẴ{���̉摜�̓ǂݍ���
void Bullet::LoadImages()
{
	animation[0] = LoadGraph("Resource/images/Bullet/1.png");
	animation[1] = LoadGraph("Resource/images/Bullet/eff1.png");
	animation[2] = LoadGraph("Resource/images/Bullet/eff2.png");
	animation[3] = LoadGraph("Resource/images/Bullet/png3.png");
}

//���ׂẴ{���̉摜�̍폜
void Bullet::UnloadImages()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
}

bool Bullet::CheckTypeAndFrameCnt()
{
	bullet_rate++;

	if (bullet_rate >= 60)
	{
		bullet_rate = 0;

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}