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
	color = GetColor(255, 0, 0);

	box_size = Vector2D(32.0f);

	location = box_size;
}


//�X�V����
void GameObject::Update()
{
	location.x += 1.0f;

	if (location.x >= 672.0f)
	{
		location.x = -32.0f;
	}
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