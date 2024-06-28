#include "Bomb.h"
#include "DxLib.h"
#include "../../Utility/InputControl.h"
#include "../../Objects/Player/Player.h"

//�R���X�g���N�^
Bomb::Bomb() : animation_count(0), flip_flag(FALSE)
{
	for (int i = 0; i < 4; i++)
	{
		animation[i] = NULL;
	}
}

//�f�X�g���N�^
Bomb::~Bomb()
{

}

void Bomb::Initialize()
{
	type = 2.0f;

	active_state = true;

	//�摜�ǂݍ���
	LoadImages();

	//�G���[�`�F�b�N
	if (animation[0] == -1)
	{
		throw("Bomb�̉摜������܂���\n");
	}
	
	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];


}

//�X�V����
void Bomb::Update()
{

	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void Bomb::Draw() const
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
	DrawRotaGraphF(location.x, location.y, 1.0, radian, animation[0], TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void Bomb::Finalize()
{
	UnloadImages();
}

//�����蔻��ʒm����
void Bomb::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	active_state = false;
}


Vector2D Bomb::SetDirection(Vector2D p_velocity)
{
	if (p_velocity.x > 0.0)
	{
		direction = Vector2D(5.0f, 0.5f);
	}
	else if (p_velocity.x < 0.0)
	{
		direction = Vector2D(-5.0f, 0.5f);
	}
	else
	{
		direction = Vector2D(0.0f, 2.0f);
	}

	return direction;
}

//�ړ�����
void Bomb::Movement()
{
	if (((location.y + direction.y) < box_size.y) ||
		(680.0f - box_size.y) < (location.y + direction.y))
	{
		direction = 0.0f;
		active_state = false;
	}

	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	direction.y += 0.2f;
	location += direction;
}

//�A�j���[�V��������
void Bomb::AnimationControl()
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
void Bomb::LoadImages()
{
	animation[0] = LoadGraph("Resource/images/Bomb.png");
	animation[1] = LoadGraph("Resource/images/Blast/1.png");
	animation[2] = LoadGraph("Resource/images/Blast/2.png");
	animation[3] = LoadGraph("Resource/images/Blast/3.png");
}

//���ׂẴ{���̉摜�̍폜
void Bomb::UnloadImages()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
}