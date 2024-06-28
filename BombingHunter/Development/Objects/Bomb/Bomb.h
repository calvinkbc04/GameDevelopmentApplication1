#pragma once

#include "../GameObject.h"


class Bomb : public GameObject
{
	int animation[4];		//�A�j���[�V�����摜
	int animation_count;	//�A�j���[�V��������
	int flip_flag;			//���]�t���O
	Vector2D direction;		//�i�s����

public:
	Bomb();
	~Bomb();

	virtual void Initialize() override;		//����������
	virtual void Update() override;			//�X�V����
	virtual void Draw() const override;		//�`�揈��
	virtual void Finalize() override;		//�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

	Vector2D SetDirection(Vector2D p_velocity);

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimationControl();

private:

	//���ׂĂ�Enemy�̉摜�̓ǂݍ��ݏ���
	void LoadImages();
	//���ׂĂ�Enemy�̉摜�̍폜����
	void UnloadImages();
};