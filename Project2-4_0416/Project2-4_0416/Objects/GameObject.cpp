#include "GameObject.h"
#include "DxLib.h"

GameObject::GameObject() : color(0x0), location(), box_size()
{

}

GameObject::~GameObject()
{

}


//����������
void GameObject::Initialize()
{
	location = Vector2D(32.0f, 24.0f);

	box_size = Vector2D(32.0f, 24.0f);

	color = GetColor(0, 255, 0);
}


//�X�V����
void GameObject::Update()
{
	Teleport();

	location += 0.7f;
}


//�`�揈��
void GameObject::Draw() const
{
	Vector2D tl = this->location - (this->box_size / 2.0f);
	Vector2D br = this->location + (this->box_size / 2.0f);

	DrawBoxAA(tl.x, tl.y, br.x, br.y, color, TRUE);
}


//�f�B�X�g���N�^�H�H�H�H�H
void GameObject::Finalize()
{

}


//���W�ݒu����
void GameObject::SetLocation(Vector2D location)
{
	this->location = location;
}


//���W��Ԃ�
Vector2D GameObject::GetLocation() const
{
	return this->location;
}


//�傫����Ԃ�
Vector2D GameObject::GetBoxSize() const
{
	return this->box_size;
}


//��ʊO�ɏo�����ʂ̔��Α��ɍs��
Vector2D GameObject::Teleport()
{
	Vector2D tmp = this->location;

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
		SetLocation(tmp);
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

	SetLocation(tmp);

	return this->location;
}